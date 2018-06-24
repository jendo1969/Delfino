//###########################################################################
// FILE:   Example_2837xSSci_FFDLB_int.c
// TITLE:  SCI Digital Echo Back with Interrupts.
//###########################################################################

#include "F28x_Project.h"     // Device Headerfile and Examples Include File

// Prototype statements for functions found within this file.
interrupt void scibTxFifoIsr(void);
interrupt void scibRxFifoIsr(void);
void scib_fifo_init(void);

// Global variables
#define BUFFMAX 64
char Txbuff[BUFFMAX];
int Tx_r_idx;
int Tx_w_idx;
char Rxbuff[BUFFMAX];
int Rx_r_idx;
int Rx_w_idx;


void main(void)
{
   Uint16 i;

   Tx_r_idx = 0;
   Tx_w_idx = 0;
   Rx_r_idx = 0;
   Rx_w_idx = 0;

// Step 1. Initialize System Control:
// PLL, WatchDog, enable Peripheral Clocks
// This example function is found in the F2837xS_SysCtrl.c file.
   InitSysCtrl();

// Step 2. Initialize GPIO:
// This example function is found in the F2837xS_Gpio.c file and
// illustrates how to set the GPIO to it's default state.
   InitGpio();

   // For this example, only init the pins for the SCI-B port.
   EALLOW;
   GpioCtrlRegs.GPCMUX2.bit.GPIO86 = 1;
   GpioCtrlRegs.GPCMUX2.bit.GPIO87 = 1;
   GpioCtrlRegs.GPCGMUX2.bit.GPIO86 = 1;
   GpioCtrlRegs.GPCGMUX2.bit.GPIO87 = 1;
   EDIS;

// Step 3. Clear all interrupts and initialize PIE vector table:
// Disable CPU interrupts
   DINT;

// Initialize PIE control registers to their default state.
// The default state is all PIE interrupts disabled and flags
// are cleared.
// This function is found in the F2837xS_PieCtrl.c file.
   InitPieCtrl();

// Disable CPU interrupts and clear all CPU interrupt flags:
   IER = 0x0000;
   IFR = 0x0000;

// Initialize the PIE vector table with pointers to the shell Interrupt
// Service Routines (ISR).
// This will populate the entire table, even if the interrupt
// is not used in this example.  This is useful for debug purposes.
// The shell ISR routines are found in F2837xS_DefaultIsr.c.
// This function is found in F2837xS_PieVect.c.
   InitPieVectTable();

// Interrupts that are used in this example are re-mapped to
// ISR functions found within this file.
   EALLOW;  // This is needed to write to EALLOW protected registers
   PieVectTable.SCIB_RX_INT = &scibRxFifoIsr;
   PieVectTable.SCIB_TX_INT = &scibTxFifoIsr;
   EDIS;   // This is needed to disable write to EALLOW protected registers

// Step 4. Initialize the Device Peripherals:
   scib_fifo_init();  // Init SCI-B

// Step 5. User specific code, enable interrupts:
   DELAY_US(3000000); // 3SEC wait

// Enable interrupts required for this example
   PieCtrlRegs.PIECTRL.bit.ENPIE = 1;   // Enable the PIE block
   PieCtrlRegs.PIEIER9.bit.INTx3=1;     // PIE Group 9, INT3 SCIB_RX
   PieCtrlRegs.PIEIER9.bit.INTx4=0;     // PIE Group 9, INT4 SCIB_TX
   IER = 0x100; // Enable CPU INT
   EINT;

// Step 6. IDLE loop. Just sit and loop forever (optional):
    for(;;)
    {
        while(Rx_w_idx != Rx_r_idx)
        {
            Txbuff[Tx_w_idx++] = Rxbuff[Rx_r_idx++];
            if(Rx_r_idx >= BUFFMAX)
            {
                Rx_r_idx = 0;
            }
            if(Tx_w_idx >= BUFFMAX)
            {
                Tx_w_idx = 0;
            }
            if(Tx_w_idx == Tx_r_idx)
            {
                Tx_w_idx--;
                if(Tx_w_idx < 0)
                {
                    Tx_w_idx = BUFFMAX;
                }
                break;
            }
        }
        if(Tx_w_idx != Tx_r_idx)
        {
            Uint16 fifo_st = 16 - ScibRegs.SCIFFTX.bit.TXFFST;
            for(i = 0; i<fifo_st; i++)
            {
                ScibRegs.SCITXBUF.all = Txbuff[Tx_r_idx++];
                PieCtrlRegs.PIEIER9.bit.INTx4=1;     // PIE Group 9, INT4 SCIB_TX
                if(Tx_r_idx >= BUFFMAX)
                {
                    Tx_r_idx = 0;
                }
                if(Tx_w_idx == Tx_r_idx)
                {
                    break;
                }
            }
        }
    }
}


interrupt void scibTxFifoIsr(void)
{
    Uint16 i;
    if(Tx_w_idx != Tx_r_idx)
    {
        Uint16 fifo_st = 16 - ScibRegs.SCIFFTX.bit.TXFFST;
        for(i = 0; i<fifo_st; i++)
        {
            ScibRegs.SCITXBUF.all = Txbuff[Tx_r_idx++];
            if(Tx_r_idx >= BUFFMAX)
            {
                Tx_r_idx = 0;
            }
            if(Tx_w_idx == Tx_r_idx)
            {
                break;
            }
        }
    }
    else
    {
        PieCtrlRegs.PIEIER9.bit.INTx4=0;     // PIE Group 9, INT4 SCIB_TX
    }

    ScibRegs.SCIFFTX.bit.TXFFINTCLR=1;  // Clear SCI Interrupt flag
    PieCtrlRegs.PIEACK.all|=0x100;      // Issue PIE ACK
}

interrupt void scibRxFifoIsr(void)
{
    Uint16 i;
    Uint16 fifo_st = ScibRegs.SCIFFRX.bit.RXFFST;

    for(i=0;i<fifo_st;i++)
    {
        Rxbuff[Rx_w_idx++]=ScibRegs.SCIRXBUF.all;  // Read data
        if(Rx_w_idx >= BUFFMAX)
        {
            Rx_w_idx = 0;
        }
        if(Rx_w_idx == Rx_r_idx)
        {
            Rx_w_idx--;
            if(Rx_w_idx < 0)
            {
                Rx_w_idx = BUFFMAX;
            }
            break;
        }
    }

    ScibRegs.SCIFFRX.bit.RXFFOVRCLR=1;   // Clear Overflow flag
    ScibRegs.SCIFFRX.bit.RXFFINTCLR=1;   // Clear Interrupt flag

    PieCtrlRegs.PIEACK.all|=0x100;       // Issue PIE ack
}

void scib_fifo_init()
{
   ScibRegs.SCICCR.all =0x0007;   // 1 stop bit,  No loopback
                                  // No parity,8 char bits,
                                  // async mode, idle-line protocol
   ScibRegs.SCICTL1.all =0x0003;  // enable TX, RX, internal SCICLK,
                                  // Disable RX ERR, SLEEP, TXWAKE
   ScibRegs.SCICTL2.bit.TXINTENA =1;
   ScibRegs.SCICTL2.bit.RXBKINTENA =1;

   // SCIC at115200 baud
   ScibRegs.SCIHBAUD.all = 0x0000;
   ScibRegs.SCILBAUD.all = 53;
   ScibRegs.SCIFFTX.all=0xC020; // EMPTY INT
   ScibRegs.SCIFFRX.all=0x0021; // one char INT
   ScibRegs.SCIFFCT.all=0x00;

   ScibRegs.SCICTL1.all =0x0023;     // Relinquish SCI from Reset
   ScibRegs.SCIFFTX.bit.TXFIFORESET=1;
   ScibRegs.SCIFFRX.bit.RXFIFORESET=1;

}

//===========================================================================
// No more.
//===========================================================================

