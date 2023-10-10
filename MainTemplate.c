//MainTemplate.c
/*********************************************************************

Author: Hamza Hashmi
Date: June 18, 2021

This program reads two colour sensor inputs
 - If both sensors read 0, the robot will stop moving
 - If both sensors read 0 and the counter (doubleblack) is 1, the robot will turnaround
 - If input 0 reads 1 and input 1 reads 0, the robot will turn right
 - If input 0 reads 0 and input 1 reads 1, the robot will turn left

Notes:
PIC used - PIC2432KA302 operating at 8MHz
 
Outputs:
 - RB0:RB1
 - RB6:RB15
 
Inputs:
 - RA0 colour sensor input
 - RA1 colour sensor input

********************************************************************/

/*******************************************************************
    Include Files
********************************************************************/
#include "p24f32ka302.h"
#include "configBits.h"
#include "delay.h"

/*******************************************************************
    Symbolic Constants used by main()
********************************************************************/
    #define ON_DELAY 20
    #define OFF_DELAY 5

/*******************************************************************
        Local Function Prototypes
********************************************************************/
void initTimer (void);
void delay (unsigned long milli);
void right(void);
void left(void);
void forward(void);
void turnaround(void);

/*******************************************************************
    Global Variable Declarations
********************************************************************/
//declare variable used in loops
int doubleblack = 0;

/*******************************************************************
    main() function
********************************************************************/
int main ()
{
//initialize peripherals
 initTimer();
 //teach all PORTB to be outputs
 TRISB=0;
 //initialize all PORTB
 LATB=0;
 //Set PORTA to all digital inputs
 TRISA=0xffff;
 //initialize all PORTA
 ANSA=0;
 
//continuously scanning for sensor inputs
while (1)
 {
    //if input 0 is high
    if(PORTAbits.RA0 == 1)
        {
        /*and if input 1 is also high, then
         have the robot move forward */
            if(PORTAbits.RA1 == 1)
                forward();
            /*otherwise, the robot will turn right */
            else
                right();
        }
    /*instead, if input 1 is high and input 0 is low, then
     have the robot turn left*/
        else if(PORTAbits.RA1 == 1)
            left();
    /*otherwise, if both input 0 and 1 are low*/
        else
        {
            /*and if doubleblack is equal to 1, then
             the robot will perform a turn around*/
            if(doubleblack == 1)
            {
                turnaround();
                doubleblack++;
            }
            /*otherwise if doubleblack does not equal one*/
            else
            {
                /*and when input 0 and 1 are both low, then
                 the robot will stop moving*/
                while(PORTAbits.RA0 == 0 && PORTAbits.RA1 == 0)
                {
                    LATB = 0x0000;
                }
                doubleblack++;
            }
        }
    }
} //end of MainTemplate.c

/*******************************************************************
    List of Functions
********************************************************************/

//the robot moves forward
void forward (void)
{
    LATBbits.LATB13 = 1;
    LATBbits.LATB12 = 1;
    LATBbits.LATB1 = 0;
    LATBbits.LATB2 = 1;
    LATBbits.LATB14 = 0;
    LATBbits.LATB15 = 1;
    delay (ON_DELAY);
    LATBbits.LATB13 = 0;
    LATBbits.LATB12 = 0;
    LATBbits.LATB1 = 0;
    LATBbits.LATB2 = 0;
    LATBbits.LATB14 = 0;
    LATBbits.LATB15 = 0;
    delay (OFF_DELAY);
}

//the robot makes a left
void left (void)
{
    LATBbits.LATB11 = 1;
    LATBbits.LATB10 = 1;
    LATBbits.LATB15 = 1;
    LATBbits.LATB14 = 0;
    LATBbits.LATB2 = 0;
    LATBbits.LATB1 = 1;
    delay (ON_DELAY);
    LATBbits.LATB11 = 0;
    LATBbits.LATB10 = 0;
    LATBbits.LATB15 = 0;
    LATBbits.LATB14 = 0;
    LATBbits.LATB2 = 0;
    LATBbits.LATB1 = 0;
    delay (OFF_DELAY);
}

//the robot makes a right
void right(void)
{
    LATBbits.LATB9 = 1;
    LATBbits.LATB8 = 1;
    LATBbits.LATB15 = 0;
    LATBbits.LATB14 = 1;
    LATBbits.LATB2 = 1;
    LATBbits.LATB1 = 0;
    delay (ON_DELAY);
    LATBbits.LATB9 = 0;
    LATBbits.LATB8 = 0;
    LATBbits.LATB15 = 0;
    LATBbits.LATB14 = 0;
    LATBbits.LATB2 = 0;
    LATBbits.LATB1 = 0;
    delay (OFF_DELAY);
}

//the robot does a turn around
void turnaround (void)
{
    LATBbits.LATB7 = 1;
    LATBbits.LATB6 = 1;
    LATBbits.LATB1 = 1;
    LATBbits.LATB2 = 0;
    LATBbits.LATB14 = 0;
    LATBbits.LATB15 = 1;
    delay (1400);
}
