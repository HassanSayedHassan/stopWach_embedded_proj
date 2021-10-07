#include"STD_TYPES.h"
#include "MDIO_Interface.h"
#include"LCD_Interface.h"
#include<avr/delay.h>
#include "HKPD_Interface.h"

#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include <stdbool.h>
#include "stack.h"

#define hourLeftMode 0
#define hourRightMode 1
#define minuteLeftMode 2
#define minuteRightMode 3
#define secondLeftMode 4
#define secondRightMode 5

u8 hourLeft=0;
u8 hourRight=0;
u8 minuteLeft=0;
u8 minuteRight=0;
u8 secondLeft=0;
u8 secondRight=0;

u8 currentMode=hourLeftMode;

void initSystem(void);
void updateSystemCount(void);
void incrementCurrent(void);
void decrementCurrent(void);
void  goToNext(void);
void goToPrevious(void);
void startCount(void);

u8 arrowShape[]={4, 14, 21, 4, 4, 4, 4, 4};

int main (void)
{

	u8 localPressedKey;
	LCD_VoidInit();
	HKPD_voidInitializeKeypad();
	LCD_VoidGoToXY(0, 0);
    LCD_VoidWriteSpecialCharacter(arrowShape,0);
    MDIO_VoidSetPinDirection(PORTD,PIN3,OUTPUT_PIN);
    initSystem();
	while(1)
	 {

		 localPressedKey=HKPD_u8GetPressedKey();
		 if(localPressedKey=='1')   /// up
		 {
		     incrementCurrent();

             while(HKPD_u8GetPressedKey()==localPressedKey)
             {

             }
             _delay_ms(20); // Delay To Over Come The Pouncing Problems
		 }
		 else if(localPressedKey=='4')  /// down
         {

             decrementCurrent();


             while(HKPD_u8GetPressedKey()==localPressedKey)
             {

             }
             _delay_ms(20); // Delay To Over Come The Pouncing Problems
         }
         else if(localPressedKey=='2')  /// Next
         {

             goToNext();


             while(HKPD_u8GetPressedKey()==localPressedKey)
             {

             }
             _delay_ms(20); // Delay To Over Come The Pouncing Problems
         }
         else if(localPressedKey=='3')  /// previous
         {

             goToPrevious();


             while(HKPD_u8GetPressedKey()==localPressedKey)
             {

             }
             _delay_ms(20); // Delay To Over Come The Pouncing Problems
         }
         else if(localPressedKey=='5')  /// Start
         {


        	 startCount();

             while(HKPD_u8GetPressedKey()==localPressedKey)
             {

             }
             _delay_ms(20); // Delay To Over Come The Pouncing Problems
         }
	 }
	 return 0;
}

void initSystem(void)
{
    LCD_VoidClearScreen();
    LCD_VoidSendNum(hourLeft);
    LCD_VoidSendNum(hourRight);
    LCD_VoidSendChar(':');
    LCD_VoidSendNum(minuteLeft);
    LCD_VoidSendNum(minuteRight);
    LCD_VoidSendChar(':');
    LCD_VoidSendNum(secondLeft);
    LCD_VoidSendNum(secondRight);
    /// get Current arrow Index
    u8 currentModeIndex=0;
    if(currentMode==0||currentMode==1)  currentModeIndex=currentMode;
    if(currentMode==2||currentMode==3)  currentModeIndex=currentMode+1;
    if(currentMode==4||currentMode==5)  currentModeIndex=currentMode+2;
    
    LCD_VoidDisplaySpecialCharacter(0,1,currentModeIndex);

}
void updateSystemCount(void)
{
    LCD_VoidClearScreen();
    LCD_VoidSendNum(hourLeft);
    LCD_VoidSendNum(hourRight);
    LCD_VoidSendChar(':');
    LCD_VoidSendNum(minuteLeft);
    LCD_VoidSendNum(minuteRight);
    LCD_VoidSendChar(':');
    LCD_VoidSendNum(secondLeft);
    LCD_VoidSendNum(secondRight);

    LCD_VoidGoToXY(1, 0);
    LCD_VoidSendString("Counting...");

}
void incrementCurrent(void)
{
    if(currentMode==hourLeftMode)                hourLeft==6?hourLeft=0: hourLeft++;
    else if(currentMode==hourRightMode)          hourRight==6?hourRight=0: hourRight++;
    else if(currentMode==minuteLeftMode)         minuteLeft==6?minuteLeft=0: minuteLeft++;
    else if(currentMode==minuteRightMode)        minuteRight==6?minuteRight=0: minuteRight++;
    else if(currentMode==secondLeftMode)         secondLeft==6?secondLeft=0: secondLeft++;
    else if(currentMode==secondRightMode)        secondRight==6?secondRight=0: secondRight++;


    initSystem();

}
void decrementCurrent(void)
{
    if(currentMode==hourLeftMode)                hourLeft==0?hourLeft=6: hourLeft--;
    else if(currentMode==hourRightMode)          hourRight==0?hourRight=6: hourRight--;
    else if(currentMode==minuteLeftMode)         minuteLeft==0?minuteLeft=6: minuteLeft--;
    else if(currentMode==minuteRightMode)        minuteRight==0?minuteRight=6: minuteRight--;
    else if(currentMode==secondLeftMode)         secondLeft==0?secondLeft=6: secondLeft--;
    else if(currentMode==secondRightMode)        secondRight==0?secondRight=6: secondRight--;

    initSystem();
}
void  goToNext(void)
{
   if(currentMode<=secondRightMode) currentMode++;
    initSystem();
}
void goToPrevious(void)
{
    if(currentMode>=0) currentMode--;
    initSystem();
}
void startCount(void)
{

    while (secondRight||secondLeft||minuteLeft||minuteRight||hourLeft||hourRight)
    {


        if(secondRight>0) 
        {
            secondRight--;
            updateSystemCount();
            _delay_ms(1000);
        }
        else if(secondLeft>0)
        {
            secondLeft--;
            secondRight=9;
            updateSystemCount();
            _delay_ms(1000);
        }
        else if(minuteRight>0)
        {
            minuteRight--;
            secondLeft=6;
            updateSystemCount();
            _delay_ms(1000);
        }
        else if(minuteLeft>0)
        {
            minuteLeft--;
            minuteRight=9;
            updateSystemCount();
            _delay_ms(1000);
        }
        else if(hourRight>0)
        {
            hourRight--;
            minuteLeft=6;
            updateSystemCount();
            _delay_ms(1000);
        }
        else if(hourLeft>0)
        {
            hourLeft--;
            hourRight=9;
            updateSystemCount();
            _delay_ms(1000);
        }


    }
    while(1)
    {
       u8 localPressedKey=HKPD_u8GetPressedKey();
        if(localPressedKey=='c')
        {
            MDIO_VoidSetPinValue(PORTD,PIN3,LOW);
            return;
        }
        MDIO_VoidSetPinValue(PORTD,PIN3,HIGH);
        _delay_ms(500);
        MDIO_VoidSetPinValue(PORTD,PIN3,LOW);
        _delay_ms(250);
        LCD_VoidClearScreen();
        LCD_VoidSendString("Count Finish");
    }



}
