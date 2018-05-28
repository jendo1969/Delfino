//###########################################################################
// FILE:    Example_2837xSSci_FFDLB.c
// TITLE:   SCI FIFO Digital Loop Back Test.
//
//! \addtogroup cpu01_example_list
//! <h1>SCI FIFO Digital Loop Back Test (sci_looback)</h1>
//!
//!  This program uses the internal loop back test mode of the peripheral.
//!  Other then boot mode pin configuration, no other hardware configuration
//!  is required.
//!
//!  This test uses the loopback test mode of the SCI module to send
//!  characters starting with 0x00 through 0xFF.  The test will send
//!  a character and then check the receive buffer for a correct match.
//!
//!  \b Watch \b Variables \n
//!  - \b LoopCount - Number of characters sent
//!  - \b ErrorCount - Number of errors detected
//!  - \b SendChar - Character sent
//!  - \b ReceivedChar - Character received
//
//###########################################################################
// $TI Release: F2837xS Support Library v180 $
// $Release Date: Fri Nov  6 16:27:58 CST 2015 $
// $Copyright: Copyright (C) 2014-2015 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

#include "F28x_Project.h"     // Device Headerfile and Examples Include File

// Prototype statements for functions found within this file.
void scic_loopback_init(void);
void scic_fifo_init(void);
void scic_xmit(int a);
void error();

// Global counts used in this example
Uint16 LoopCount;
Uint16 ErrorCount;

void main(void)
{
    Uint16 SendChar;
    Uint16 ReceivedChar;

// Step 1. Initialize System Control registers, PLL, WatchDog, Clocks to default state:
// This function is found in the F2837xS_SysCtrl.c file.
	InitSysCtrl();

// Step 2. Initialize GPIO:
// This example function is found in the F2837xS_Gpio.c file and
// illustrates how to set the GPIO to it's default state.
   InitGpio();

// For this example, only init the pins for the SCI-C port.
//  GPIO_SetupPinMux() - Sets the GPxMUX1/2 and GPyMUX1/2 register bits
//  GPIO_SetupPinOptions() - Sets the direction and configuration of the GPIOS
// These functions are found in the F2837xS_Gpio.c file.
//   GPIO_SetupPinMux(90, GPIO_MUX_CPU1, 1);
 //  GPIO_SetupPinOptions(90, GPIO_INPUT, GPIO_PUSHPULL);
 //  GPIO_SetupPinMux(89, GPIO_MUX_CPU1, 1);
 //  GPIO_SetupPinOptions(89, GPIO_OUTPUT, GPIO_ASYNC);

   // For this example, only init the pins for the SCI-C port.
   EALLOW;
   GpioCtrlRegs.GPCMUX2.bit.GPIO90 = 1;
   GpioCtrlRegs.GPCMUX2.bit.GPIO89 = 1;
   GpioCtrlRegs.GPCGMUX2.bit.GPIO90 = 1;
   GpioCtrlRegs.GPCGMUX2.bit.GPIO89 = 1;
   EDIS;

// Step 3. Initialize PIE vector table:
// The PIE vector table is initialized with pointers to shell Interrupt
// Service Routines (ISR).  The shell routines are found in F2837xS_DefaultIsr.c.
// Insert user specific ISR code in the appropriate shell ISR routine in
// the F2837xS_DefaultIsr.c file.

// Disable and clear all CPU __interrupts:
	DINT;
	IER = 0x0000;
	IFR = 0x0000;

// Initialize Pie Control Registers To Default State:
// This function is found in the F2837xS_PieCtrl.c file.
// InitPieCtrl();  PIE is not used for this example

// Initialize the PIE Vector Table To a Known State:
// This function is found in F2837xS_PieVect.c.
// This function populates the PIE vector table with pointers
// to the shell ISR functions found in F2837xS_DefaultIsr.c.
	InitPieVectTable();

// Enable CPU and PIE __interrupts
// This example function is found in the F2837xS_PieCtrl.c file.
	EnableInterrupts();

// Step 4. User specific functions, Reassign vectors (optional), Enable Interrupts:

    LoopCount = 0;
    ErrorCount = 0;

    scic_fifo_init();	   // Initialize the SCI FIFO
    scic_loopback_init();  // Initialize SCI for digital loop back

    // Note: Autobaud lock is not required for this example

    // Send a character starting with 0
    SendChar = 0;

// Step 5. Send Characters forever starting with 0x00 and going through
// 0xFF.  After sending each, check the receive buffer for the correct value

	for(;;)
    {
       scic_xmit(SendChar);
       while(ScicRegs.SCIFFRX.bit.RXFFST == 0) { } // wait for RRDY/RXFFST =1 for 1 data available in FIFO

       // Check received character
       ReceivedChar = ScicRegs.SCIRXBUF.all;
       if(ReceivedChar != SendChar) error();

       // Move to the next character and repeat the test
       SendChar++;
       // Limit the character to 8-bits
       SendChar &= 0x00FF;
       LoopCount++;
    }

}


// Step 6. Insert all local Interrupt Service Routines (ISRs) and functions here:

void error()
{

      ErrorCount++;
//   asm("     ESTOP0");  // Uncomment to stop the test here
//    for (;;);

}

// Test 1,SCIAC  DLB, 8-bit word, baud rate , default, 1 STOP bit, no parity
void scic_loopback_init()
{
    // Note: Clocks were turned on to the SCIC peripheral
    // in the InitSysCtrl() function

 	ScicRegs.SCICCR.all =0x0007;   // 1 stop bit,  No loopback
                                   // No parity,8 char bits,
                                   // async mode, idle-line protocol
	ScicRegs.SCICTL1.all =0x0003;  // enable TX, RX, internal SCICLK,
                                   // Disable RX ERR, SLEEP, TXWAKE
//	ScicRegs.SCICTL2.all =0x0003;
	ScicRegs.SCICTL2.bit.TXINTENA =1;
	ScicRegs.SCICTL2.bit.RXBKINTENA =1;
    //ScicRegs.SCIHBAUD.all    =0x0000;
    //ScicRegs.SCILBAUD.all    =0x000F;
    ScicRegs.SCIHBAUD.all    =0x0000;  // 115200 baud @LSPCLK = 22.5MHz (90 MHz SYSCLK).
    ScicRegs.SCILBAUD.all    =53;

	ScicRegs.SCICCR.bit.LOOPBKENA =1; // Enable loop back
	ScicRegs.SCICTL1.all =0x0023;     // Relinquish SCI from Reset
}

// Transmit a character from the SCI'
void scic_xmit(int a)
{
    ScicRegs.SCITXBUF.all=a;
}

// Initialize the SCI FIFO
void scic_fifo_init()
{
    ScicRegs.SCIFFTX.all=0xE040;
    ScicRegs.SCIFFRX.all=0x2044;
    ScicRegs.SCIFFCT.all=0x0;
}






//===========================================================================
// No more.
//===========================================================================

