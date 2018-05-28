//###########################################################################
// FILE:   Example_2837xSSci_FFDLB_int.c
// TITLE:  SCI Digital Loop Back with Interrupts.
//
//! \addtogroup cpu01_example_list
//! <h1>SCI Digital Loop Back with Interrupts (sci_loopback_interrupts)</h1>
//!
//!  This program uses the internal loop back test mode of the peripheral.
//!  Other then boot mode pin configuration, no other hardware configuration
//!  is required. Both interrupts and the SCI FIFOs are used.
//!
//!  A stream of data is sent and then compared to the received stream.
//!  The SCI-A sent data looks like this: \n
//!  00 01 \n
//!  01 02 \n
//!  02 03 \n
//!  .... \n
//!  FE FF \n
//!  FF 00 \n
//!  etc.. \n
//!  The pattern is repeated forever.
//!
//!  \b Watch \b Variables \n
//!  - \b sdataA - Data being sent
//!  - \b rdataA - Data received
//!  - \b rdata_pointA - Keep track of where we are in the data stream.
//!    This is used to check the incoming data
//
//###########################################################################
// $TI Release: F2837xS Support Library v180 $
// $Release Date: Fri Nov  6 16:27:58 CST 2015 $
// $Copyright: Copyright (C) 2014-2015 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

#include "F28x_Project.h"     // Device Headerfile and Examples Include File

//#define CPU_FREQ    60E6
//#define LSPCLK_FREQ CPU_FREQ/4
//#define SCI_FREQ    100E3
//#define SCI_PRD     (LSPCLK_FREQ/(SCI_FREQ*8))-1

// Prototype statements for functions found within this file.
interrupt void scibTxFifoIsr(void);
interrupt void scibRxFifoIsr(void);
void scib_fifo_init(void);

// Global variables
Uint16 sdataB[2];    // Send data for SCI-B
Uint16 rdataB[2];    // Received data for SCI-B
Uint16 rdata_pointB; // Used for checking the received data

char Txbuff[64]:
char Rxbuff[64]:


void main(void)
{
   Uint16 i;
   char *msg;

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

   msg = "\r\n\n\nHello World!\0";
   scib_msg(msg);

   msg = "\r\nYou will enter a character, and the DSP will echo it back! \n\0";
   scib_msg(msg);

// Init send data.  After each transmission this data
// will be updated for the next transmission
   for(i = 0; i<2; i++)
   {
      sdataB[i] = i;
   }

   rdata_pointB = sdataB[0];
// Enable interrupts required for this example
   PieCtrlRegs.PIECTRL.bit.ENPIE = 1;   // Enable the PIE block
   PieCtrlRegs.PIEIER9.bit.INTx3=1;     // PIE Group 9, INT3
   PieCtrlRegs.PIEIER9.bit.INTx4=1;     // PIE Group 9, INT4
   IER = 0x100; // Enable CPU INT
   EINT;

// Step 6. IDLE loop. Just sit and loop forever (optional):
    for(;;);

}


interrupt void scibTxFifoIsr(void)
{
    Uint16 i;
    for(i=0; i< 2; i++)
    {
       ScibRegs.SCITXBUF.all=sdataB[i];     // Send data
    }

    for(i=0; i< 2; i++)                 //Increment send data for next cycle
    {
       sdataB[i] = (sdataB[i]+1) & 0x00FF;
    }

    ScibRegs.SCIFFTX.bit.TXFFINTCLR=1;  // Clear SCI Interrupt flag
    PieCtrlRegs.PIEACK.all|=0x100;      // Issue PIE ACK
}

interrupt void scibRxFifoIsr(void)
{
    Uint16 i;
    for(i=0;i<2;i++)
    {
       rdataB[i]=ScibRegs.SCIRXBUF.all;  // Read data
    }
    for(i=0;i<2;i++)                     // Check received data
    {
       if(rdataB[i] != ( (rdata_pointB+i) & 0x00FF) ) error();
    }
    rdata_pointB = (rdata_pointB+1) & 0x00FF;

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
   ScibRegs.SCIFFTX.all=0xC022;
   ScibRegs.SCIFFRX.all=0x0022;
   ScibRegs.SCIFFCT.all=0x00;

   ScibRegs.SCICTL1.all =0x0023;     // Relinquish SCI from Reset
   ScibRegs.SCIFFTX.bit.TXFIFORESET=1;
   ScibRegs.SCIFFRX.bit.RXFIFORESET=1;

}

//===========================================================================
// No more.
//===========================================================================

