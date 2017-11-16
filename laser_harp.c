                                                                                  /*
************************************************************************
 ECE 362 - Mini-Project C Source File - Spring 2015
***********************************************************************
                                                                                                    
 Team ID: < ? >

 Project Name: < ? >

 Team Members:

   - Team/Doc Leader: < ? >      Signature: ______________________
   
   - Software Leader: < ? >      Signature: ______________________

   - Interface Leader: < ? >     Signature: ______________________

   - Peripheral Leader: < ? >    Signature: ______________________


 Academic Honesty Statement:  In signing above, we hereby certify that we 
 are the individuals who created this HC(S)12 source file and that we have
 not copied the work of any other student (past or present) while completing 
 it. We understand that if we fail to honor this agreement, we will receive 
 a grade of ZERO and be subject to possible disciplinary action.

***********************************************************************

 The objective of this Mini-Project is to .... < ? >


***********************************************************************

 List of project-specific success criteria (functionality that will be
 demonstrated):

 1.

 2.

 3.

 4.

 5.

***********************************************************************

  Date code started: < ? >

  Update history (add an entry every time a significant change is made):

  Date: < ? >  Name: < ? >   Update: < ? >

  Date: < ? >  Name: < ? >   Update: < ? >

  Date: < ? >  Name: < ? >   Update: < ? >


***********************************************************************
*/

#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include <mc9s12c32.h>

/* All functions after main should be initialized here */
char inchar(void);
void outchar(char x);

// LCD function
void shiftout(char);    // LCD drivers (written previously)
void lcdwait(void);
void send_byte(char);
void send_i(char);
void chgline(char);
void print_c(char);
void pmsglcd(char[]);

/* Variable declarations */
int switches = 10;
int increment = 0;                                                                                      
unsigned char sinewave[255] ={0x80,0x83,0x86,0x89,0x8c,0x8f,0x92,0x95,0x98,0x9c,0x9f,0xa2,0xa5,0xa8,0xab,0xae,0xb0,0xb3,0xb6,0xb9,0xbc,0xbf,0xc1,0xc4,0xc7,0xc9,0xcc,0xce,0xd1,0xd3,0xd5,0xd8,0xda,0xdc,0xde,0xe0,0xe2,0xe4,0xe6,0xe8,0xea,0xeb,0xed,0xef,0xf0,0xf2,0xf3,0xf4,0xf6,0xf7,0xf8,0xf9,0xfa,0xfb,0xfb,0xfc,0xfd,0xfd,0xfe,0xfe,0xfe,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfe,0xfe,0xfd,0xfd,0xfc,0xfc,0xfb,0xfa,0xf9,0xf8,0xf7,0xf6,0xf5,0xf4,0xf2,0xf1,0xef,0xee,0xec,0xeb,0xe9,0xe7,0xe5,0xe3,0xe1,0xdf,0xdd,0xdb,0xd9,0xd7,0xd4,0xd2,0xcf,0xcd,0xca,0xc8,0xc5,0xc3,0xc0,0xbd,0xba,0xb8,0xb5,0xb2,0xaf,0xac,0xa9,0xa6,0xa3,0xa0,0x9d,0x9a,0x97,0x94,0x91,0x8e,0x8a,0x87,0x84,0x81,0x7e,0x7b,0x78,0x75,0x71,0x6e,0x6b,0x68,0x65,0x62,0x5f,0x5c,0x59,0x56,0x53,0x50,0x4d,0x4a,0x47,0x45,0x42,0x3f,0x3c,0x3a,0x37,0x35,0x32,0x30,0x2d,0x2b,0x28,0x26,0x24,0x22,0x20,0x1e,0x1c,0x1a,0x18,0x16,0x14,0x13,0x11,0x10,0xe,0xd,0xb,0xa,0x9,0x8,0x7,0x6,0x5,0x4,0x3,0x3,0x2,0x2,0x1,0x1,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1,0x1,0x1,0x2,0x2,0x3,0x4,0x4,0x5,0x6,0x7,0x8,0x9,0xb,0xc,0xd,0xf,0x10,0x12,0x14,0x15,0x17,0x19,0x1b,0x1d,0x1f,0x21,0x23,0x25,0x27,0x2a,0x2c,0x2e,0x31,0x33,0x36,0x38,0x3b,0x3e,0x40,0x43,0x46,0x49,0x4c,0x4f,0x51,0x54,0x57,0x5a,0x5d,0x60,0x63,0x67,0x6a,0x6d,0x70,0x73,0x76,0x79,0x7c};
int ind = 0;
int increment_count = 0;
int mode = 2;
int pre = 0;
int pbflag = 0;

int major_c[5] = {607,382,191,96,48};
int major_d[5] = {573,341,171,85,43};
int major_e[5] = {511,303,152,76,38};
int major_f[5] = {455,286,143,72,36};
int major_g[5] = {511,255,128,64,32};
int major_a[5] = {455,227,114,57,28};
int major_b[5] = {405,202,101,51,25};
int printflag = 0;
void majordis(void);
void notedis(void);

  
/* Special ASCII characters */
#define CR 0x0D         // ASCII return 
#define LF 0x0A         // ASCII new line 

/* LCD COMMUNICATION BIT MASKS (note - different than previous labs) */
#define RS 0x10         // RS pin 8mask (PTT[4])
#define RW 0x20         // R/W pin mask (PTT[5])
#define LCDCLK 0x40     // LCD EN/CLK pin mask (PTT[6])

/* LCD INSTRUCTION CHARACTERS */
#define LCDON 0x0F      // LCD initialization command
#define LCDCLR 0x01     // LCD clear display command
#define TWOLINE 0x38    // LCD 2-line enable command
#define CURMOV 0xFE     // LCD cursor move instruction
#define LINE1 = 0x80    // LCD line 1 cursor position
#define LINE2 = 0xC0    // LCD line 2 cursor position

/*                          
***********************************************************************
Initializations
***********************************************************************
*/

void  initializations(void) {

/* Set the PLL speed (bus clock = 24 MHz) */
  CLKSEL = CLKSEL & 0x80; // disengage PLL from system
  PLLCTL = PLLCTL | 0x40; // turn on PLL
  SYNR = 0x02;            // set PLL multiplier
  REFDV = 0;              // set PLL divider
  while (!(CRGFLG & 0x08)){  }
  CLKSEL = CLKSEL | 0x80; // engage PLL

/* Disable watchdog timer (COPCTL register) */
  COPCTL = 0x40   ; // COP off; RTI and COP stopped in BDM-mode

/* Initialize asynchronous serial port (SCI) for 9600 baud, interrupts off initially */
  SCIBDH =  0x00; //set baud rate to 9600
  SCIBDL =  0x9C; //24,000,000 / 16 / 156 = 9600 (approx)  
  SCICR1 =  0x00; //$9C = 156
  SCICR2 =  0x0C; //initialize SCI for program-driven operation
  DDRB   =  0x10; //set PB4 for output mode
  PORTB  =  0x10; //assert DTR pin on COM port
         
         
/* 
   Initialize TIM Ch 7 (TC7) for periodic interrupts every 10.0 ms  
    - Enable timer subsystem                         
    - Set channel 7 for output compare
    - Set appropriate pre-scale factor and enable counter reset after OC7
    - Set up channel 7 to generate 10 ms interrupt rate
    - Initially disable TIM Ch 7 interrupts                                                                                                 
*/                                                                                                  

      TSCR1 = 0x80;
  //    TSCR2 = 0x08;
      TSCR2 = 0X0C;
      TIOS = 0x80;
      TIE = 0x80;
  //    TC7 = 179;
      TC7 = 15;

               

/*
 Initialize the PWM unit to produce a signal with the following
 characteristics on PWM output channel 3:
   - sampling frequency of approximately 100 Hz
   - left-aligned, negative polarity
   - period register = $FF (yielding a duty cycle range of 0% to 100%,
     for duty cycle register values of $00 to $FF 
   - duty register = $00 (motor initially stopped)
                         
 IMPORTANT: Need to set MODRR so that PWM Ch 3 is routed to port pin PT3
*/                                                                                                 
    MODRR = 0x01;
    PWME = 0x01;
    PWMPOL = 0x01;
    PWMCTL = 0x00;
    PWMCAE = 0x00;
    PWMPER0 = 0xff;
    PWMDTY0 = 0x00;
    PWMCLK  = 0x00;
    PWMPRCLK = 0x00;
    //PWMSCLA  =4;


/* 
 Initialize the ATD to sample a D.C. input voltage (range: 0 to 5V)
 on Channel 0 (connected to a 10K-ohm potentiometer). The ATD should
 be operated in a program-driven (i.e., non-interrupt driven), normal
 flag clear mode using nominal sample time/clock prescaler values,
 8-bit, unsigned, non-FIFO mode.
                         
 Note: Vrh (the ATD reference high voltage) is connected to 5 VDC and
       Vrl (the reference low voltage) is connected to GND on the 
       9S12C32 kit.  An input of 0v will produce output code $00,
       while an input of 5.00 volts will produce output code $FF
*/                                                                                                  
      ATDCTL2_ADPU = 1;
      ATDCTL2_AFFC = 0;
      ATDCTL2_ASCIE = 0;
      
      ATDCTL3_FIFO = 0;
      ATDCTL3 = ATDCTL3 | 0x40;  // CHECK !!!!
      
      ATDCTL4_SRES8   = 1;
      ATDCTL4_SMP = 0 ;
      ATDCTL4_PRS = 0x5 ;
      
      ATDCTL5_DJM = 0;
      ATDCTL5_DSGN = 0;
      ATDCTL5_SCAN = 0;
      ATDCTL5_MULT = 1;  
/* 
  Initialize the pulse accumulator (PA) for event counting mode,
  and to increment on negative edges (no PA interrupts will be utilized,
  since overflow should not occur under normal operating conditions)
*/                   

/*
  Initialize the RTI for an 2.048 ms interrupt rate
*/
      RTICTL = 0x1F;
      CRGINT = CRGINT | 0x80;  
/*
  Initialize SPI for baud rate of 6 Mbs, MSB first
  (note that R/S, R/W', and LCD clk are on different PTT pins)
*/  
 SPICR1 = 0X50;
    SPICR2 = 0X00;
    
    SPIBR_SPR0 = 1;
    SPIBR_SPR1 = 0;
    SPIBR_SPR2 = 0;
    SPIBR_SPPR0 = 0;
    SPIBR_SPPR1 = 0;
    SPIBR_SPPR2 = 0;  


/* Initialize digital I/O port pins */
       DDRAD = 0x00;   // port AD as input pin              
       DDRT = 0xFD;  // port T as output pin 
       DDRM  = 0xFF; // port M as output pin
       ATDDIEN = 0x00;    // port AD bit used as analog input

/* 
   Initialize the LCD
     - pull LCDCLK high (idle)
     - pull R/W' low (write state)
     - turn on LCD (LCDON instruction)
     - enable two-line mode (TWOLINE instruction)
     - clear LCD (LCDCLR instruction)
     - wait for 2ms so that the LCD can wake up     
*/  
   PTT_PTT6 = 1;
    PTT_PTT5 = 0;
    send_i(LCDON)  ;
    send_i(TWOLINE)  ;
    send_i(LCDCLR) ;
    lcdwait();
                                                                                                    
              
}


void main(void) {
         DisableInterrupts
        initializations();                                                                     
        EnableInterrupts;


 
 for(;;) {

      ATDCTL5 &= 0xF0;  //start conversion
      
    while(ATDSTAT0_SCF  == 0) {}
  
    if (ATDDR0H * 12 > 255){
     switches = 0; 
    } else if (ATDDR1H * 12 > 255){
     switches = 1; 
    } else if (ATDDR2H * 12 > 255){
     switches = 2; 
    } else if (ATDDR3H * 12 > 255){
     switches = 3; 
    } else if (ATDDR4H * 12 > 255){
     switches = 4; 
    } else if (ATDDR5H * 12 > 255){
     switches = 5; 
    }else{
     switches = 10; 
    }
    if(pbflag == 1){
    mode = (mode + 1)%5;
    pbflag = 0; 
    } 
    notedis();
    majordis();

     
}
   
} 
//ADDITIONAL FUNCTIONS

void majordis(){ 
  // display message to LCD
    if(switches == 0 ){
    chgline(0x80);
    pmsglcd("Do              ");
  }else if(switches == 1){
    chgline(0x80);
    pmsglcd("Re              ");
  }else if(switches == 2){
    chgline(0x80);
    pmsglcd("Mi              ");
  }else if(switches == 3){
    chgline(0x80);
    pmsglcd("Fa              ");
  }else if(switches == 4){
    chgline(0x80);
    pmsglcd("So              ");
  }else if(switches == 5){
    chgline(0x80);
    pmsglcd("La              ");
  }else if(switches == 6){
    chgline(0x80);
    pmsglcd("Ti              ");
  }/*else{
    chgline(0x80);
    pmsglcd("Dream Melody");
  } */
    
}  

void notedis(){
  // display message to LCD
   if(mode == 0 ){
    chgline(0xc0);
    pmsglcd("Bass            ");
  }else if(mode == 1){
    chgline(0xc0);
    pmsglcd("Baritone        ");
  }else if(mode == 2){
    chgline(0xc0);
    pmsglcd("Tenor           ");
  }else if(mode == 3){
    chgline(0xc0);
    pmsglcd("Alto            ");
  }else if(mode == 4){
    chgline(0xc0);
    pmsglcd("Soprano          ");
  }/*else{
    chgline(0x80);
    pmsglcd("Dream Melody");
  } */
    
}


/*
***********************************************************************                       
 RTI interrupt service routine: RTI_ISR
************************************************************************
*/

interrupt 7 void RTI_ISR(void)
{
         // clear RTI interrupt flagt 
         CRGFLG = CRGFLG | 0x80; 
    if(PTT_PTT1 == 0 && pre == 1){
      pbflag =1;
      pre = 0; 
    }else if(PTT_PTT1 == 1){
     pre = 1; 
    }
}

/*
***********************************************************************                       
  TIM interrupt service routine                   
***********************************************************************
*/

interrupt 15 void TIM_ISR(void)
{
         // clear TIM CH 7 interrupt flag 
         TFLG1 = TFLG1 | 0x80;     
         
// generate square wave signal  
   // c
    
  if(switches == 0){
   
     increment_count = major_c[mode];      
     if(increment < increment_count ){
        PWMDTY0 = 0x00;
     }else{
        PWMDTY0 = 0xff;
     }
     increment = (increment + 1) %(increment_count * 2 );          
          }
          // d
         if(switches == 1){ 
            increment_count = major_d[mode];
                     
     if(increment < increment_count){
        PWMDTY0 = 0x00;
     }else{
        PWMDTY0 = 0xff;
     }
     increment = (increment + 1) % (increment_count*2);   
          }
          //e
  if(switches == 2){       
     increment_count = major_e[mode];      
     if(increment < increment_count ){
        PWMDTY0 = 0x00;
     }else{
        PWMDTY0 = 0xff;
     }
     increment = (increment + 1) %(increment_count * 2 );          
          }
          //f
  if(switches == 3){       
     increment_count = major_f[mode];      
     if(increment < increment_count ){
        PWMDTY0 = 0x00;
     }else{
        PWMDTY0 = 0xff;
     }
     increment = (increment + 1) %(increment_count * 2 );          
          }
          //g
         if(switches == 4){         
     increment_count = major_g[mode];      
     if(increment < increment_count ){
        PWMDTY0 = 0x00;
     }else{
        PWMDTY0 = 0xff;
     }
     increment = (increment + 1) %(increment_count * 2 );          
          }
          //a
         if(switches == 5){         
     increment_count = major_a[mode];      
     if(increment < increment_count ){
        PWMDTY0 = 0x00;
     }else{
        PWMDTY0 = 0xff;
     }
     increment = (increment + 1) %(increment_count * 2 );          
          } 
  
}
          
/*        //b
         if(switches == 6){         
     increment_count = major_b[mode];      
     if(increment < increment_count ){
        PWMDTY0 = 0x00;
     }else{
        PWMDTY0 = 0xff;
     }
     increment = (increment + 1) %(increment_count * 2 );          
          }          
            increment = (increment + 1) %228; 
          }      

     if(switches == 0){
        PWMDTY0 = sinewave[ind];
           ind = (ind + 1) % 255;
     } 
   */
  

/*
***********************************************************************                       
  SCI interrupt service routine                                     
***********************************************************************
*/

interrupt 20 void SCI_ISR(void)
{
 


}

void shiftout(char x)

{

  while(! SPISR_SPTEF){
    
   }
   SPIDR =~ x;

lcdwait() ;


}


 void lcdwait()
{
       asm{
       pshx
       psha
       ldaa #2
loopo:       ldx #7996
loopi:       dbne x,loopi
       dbne a,loopo
       pula
       pulx
  }
}



void send_byte(char x)
{
     // shift out character
     // pulse LCD clock line low->high->low
     // wait 2 ms for LCD to process data
     shiftout(x);
     PTT_PTT6 = 1;
     PTT_PTT6 = 0;
     PTT_PTT6 = 1;
     lcdwait();
}



void send_i(char x)
{
        // set the register select line low (instruction data)
        // send byte
  PTT_PTT4 = 0;
  send_byte(x);  
}



void chgline(char x)
{
   send_i(CURMOV);
   send_i(x);
}


 
void print_c(char x)
{
   PTT_PTT4 = 1;
   send_byte(x);
}


void pmsglcd(char str[])
{
  char count = 0;
 while (str[count] != 0x00){
    print_c(str[count]);
    count++;      
  }
}