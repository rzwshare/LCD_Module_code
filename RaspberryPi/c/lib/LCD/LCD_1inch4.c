/*****************************************************************************
* | File      	:	LCD_1IN_Driver.c
* | Author      :   Waveshare team
* | Function    :   LCD driver
* | Info        :
*----------------
* |	This version:   V1.0
* | Date        :   2020-07-29
* | Info        :   
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documnetation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to  whom the Software is
# furished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS OR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#
******************************************************************************/
#include "LCD_1inch4.h"
#include <string.h>
#include <stdlib.h>		//itoa()
/*******************************************************************************
function:
	Hardware reset
*******************************************************************************/
static void LCD_1IN4_Reset(void)
{
	DEV_Digital_Write(LCD_CS, 1);
	DEV_Delay_ms(100);
	DEV_Digital_Write(LCD_RST, 0);
	DEV_Delay_ms(100);
	DEV_Digital_Write(LCD_RST, 1);
	DEV_Delay_ms(100);
}

/*******************************************************************************
function:
		Write data and commands
*******************************************************************************/
static void LCD_1IN4_Write_Command(UBYTE data)	 
{	
	DEV_Digital_Write(LCD_CS, 0);
	DEV_Digital_Write(LCD_DC, 0);
	DEV_SPI_WriteByte(data);
}

static void LCD_1IN4_WriteData_Byte(UBYTE data) 
{	
	DEV_Digital_Write(LCD_CS, 0);
	DEV_Digital_Write(LCD_DC, 1);
	DEV_SPI_WriteByte(data);  
	DEV_Digital_Write(LCD_CS,1);
}  

void LCD_1IN4_WriteData_Word(UWORD data)
{
	DEV_Digital_Write(LCD_CS, 0);
	DEV_Digital_Write(LCD_DC, 1);
	DEV_SPI_WriteByte((data>>8) & 0xff);
	DEV_SPI_WriteByte(data);
	DEV_Digital_Write(LCD_CS, 1);
}	  


/******************************************************************************
function:	
		Common register initialization
******************************************************************************/
void LCD_1IN4_Init(void)
{
	LCD_1IN4_Reset();

	 LCD_1IN4_Write_Command(0x11);
    DEV_Delay_ms(120);

    LCD_1IN4_Write_Command(0x36);
    LCD_1IN4_WriteData_Byte(0x00);//08

    LCD_1IN4_Write_Command(0x3A);
    LCD_1IN4_WriteData_Byte(0x05);


		/*
	LCD_1IN4_Write_Command( 0xDF);     
	LCD_1IN4_WriteData_Byte( 0x5A);   
	LCD_1IN4_WriteData_Byte( 0x69);   
	LCD_1IN4_WriteData_Byte( 0x02);   
	LCD_1IN4_WriteData_Byte( 0x01);   
	*/
	/////////////////////////////////////////////////////
	LCD_1IN4_Write_Command( 0x2A);     
	LCD_1IN4_WriteData_Byte( 0x00);   
	LCD_1IN4_WriteData_Byte( 0x00);   
	LCD_1IN4_WriteData_Byte( 0x00);   
	LCD_1IN4_WriteData_Byte( 0xEF);   
	  
	LCD_1IN4_Write_Command( 0x2B);     
	LCD_1IN4_WriteData_Byte( 0x00);   
	LCD_1IN4_WriteData_Byte( 0x00);   
	LCD_1IN4_WriteData_Byte( 0x00);   
	LCD_1IN4_WriteData_Byte( 0xEF);   
	//////////////////////////////////////////////////
	LCD_1IN4_Write_Command( 0xB2);     
	LCD_1IN4_WriteData_Byte( 0x0C);   
	LCD_1IN4_WriteData_Byte( 0x0C);   
	LCD_1IN4_WriteData_Byte( 0x00);   
	LCD_1IN4_WriteData_Byte( 0x33);   
	LCD_1IN4_WriteData_Byte( 0x33);   

	LCD_1IN4_Write_Command(0xb7);
	LCD_1IN4_WriteData_Byte(0x00);//VGH\VGL

	LCD_1IN4_Write_Command( 0xBB);     //VCOM  
	LCD_1IN4_WriteData_Byte( 0x36);   

	//LCD_1IN4_Write_Command( 0xC0);     
	//LCD_1IN4_WriteData_Byte( 0x2C);   

	LCD_1IN4_Write_Command( 0xC2);     
	LCD_1IN4_WriteData_Byte( 0x01);   

	LCD_1IN4_Write_Command( 0xC3);     //GVDD  
	LCD_1IN4_WriteData_Byte( 0x13);   //13-4.5V  //00-3.5V,09-4V  05-3.8V

	LCD_1IN4_Write_Command( 0xC4);     
	LCD_1IN4_WriteData_Byte( 0x20);   

	LCD_1IN4_Write_Command( 0xC6);     
	LCD_1IN4_WriteData_Byte( 0x0F);   //Dot INV, 60Hz  

	LCD_1IN4_Write_Command( 0xD6);     
	LCD_1IN4_WriteData_Byte( 0xA1);   

	LCD_1IN4_Write_Command( 0xD0);     
	LCD_1IN4_WriteData_Byte( 0xA4);   
	LCD_1IN4_WriteData_Byte( 0xA1);   

	LCD_1IN4_Write_Command( 0xE0);     
	LCD_1IN4_WriteData_Byte( 0xF0);   
	LCD_1IN4_WriteData_Byte( 0x08);   
	LCD_1IN4_WriteData_Byte( 0x0E);   
	LCD_1IN4_WriteData_Byte( 0x09);   
	LCD_1IN4_WriteData_Byte( 0x08);   
	LCD_1IN4_WriteData_Byte( 0x04);   
	LCD_1IN4_WriteData_Byte( 0x2F);   
	LCD_1IN4_WriteData_Byte( 0x33);   
	LCD_1IN4_WriteData_Byte( 0x45);   
	LCD_1IN4_WriteData_Byte( 0x36);   
	LCD_1IN4_WriteData_Byte( 0x13);   
	LCD_1IN4_WriteData_Byte( 0x12);   
	LCD_1IN4_WriteData_Byte( 0x2A);   
	LCD_1IN4_WriteData_Byte( 0x2D);   

	LCD_1IN4_Write_Command( 0xE1);     
	LCD_1IN4_WriteData_Byte( 0xF0);   
	LCD_1IN4_WriteData_Byte( 0x0E);   
	LCD_1IN4_WriteData_Byte( 0x12);   
	LCD_1IN4_WriteData_Byte( 0x0C);   
	LCD_1IN4_WriteData_Byte( 0x0A);   
	LCD_1IN4_WriteData_Byte( 0x15);   
	LCD_1IN4_WriteData_Byte( 0x2E);   
	LCD_1IN4_WriteData_Byte( 0x32);   
	LCD_1IN4_WriteData_Byte( 0x44);   
	LCD_1IN4_WriteData_Byte( 0x39);   
	LCD_1IN4_WriteData_Byte( 0x17);   
	LCD_1IN4_WriteData_Byte( 0x18);   
	LCD_1IN4_WriteData_Byte( 0x2B);   
	LCD_1IN4_WriteData_Byte( 0x2F); 

	 


    LCD_1IN4_Write_Command(0x21);
    DEV_Delay_ms(120);
    LCD_1IN4_Write_Command(0x29);
}

/******************************************************************************
function:	Set the cursor position
parameter	:
	  Xstart: 	Start UWORD x coordinate
	  Ystart:	Start UWORD y coordinate
	  Xend  :	End UWORD coordinates
	  Yend  :	End UWORD coordinatesen
******************************************************************************/
void LCD_1IN4_SetWindow(UWORD Xstart, UWORD Ystart, UWORD Xend, UWORD  Yend)
{ 
	LCD_1IN4_Write_Command(0x2a);
	LCD_1IN4_WriteData_Byte(Xstart >>8);
	LCD_1IN4_WriteData_Byte(Xstart & 0xff);
	LCD_1IN4_WriteData_Byte((Xend - 1) >> 8);
	LCD_1IN4_WriteData_Byte((Xend - 1) & 0xff);

	LCD_1IN4_Write_Command(0x2b);
	LCD_1IN4_WriteData_Byte(Ystart >>8);
	LCD_1IN4_WriteData_Byte(Ystart & 0xff);
	LCD_1IN4_WriteData_Byte((Yend - 1) >> 8);
	LCD_1IN4_WriteData_Byte((Yend - 1) & 0xff);

	LCD_1IN4_Write_Command(0x2C);
}

/******************************************************************************
function:	Settings window
parameter	:
	  Xstart: 	Start UWORD x coordinate
	  Ystart:	Start UWORD y coordinate

******************************************************************************/
void LCD_1IN4_SetCursor(UWORD X, UWORD Y)
{ 
	LCD_1IN4_Write_Command(0x2a);
	LCD_1IN4_WriteData_Byte(X >> 8);
	LCD_1IN4_WriteData_Byte(X);
	LCD_1IN4_WriteData_Byte(X >> 8);
	LCD_1IN4_WriteData_Byte(X);

	LCD_1IN4_Write_Command(0x2b);
	LCD_1IN4_WriteData_Byte(Y >> 8);
	LCD_1IN4_WriteData_Byte(Y);
	LCD_1IN4_WriteData_Byte(Y >> 8);
	LCD_1IN4_WriteData_Byte(Y);

	LCD_1IN4_Write_Command(0x2C);
}

/******************************************************************************
function:	Clear screen function, refresh the screen to a certain color
parameter	:
	  Color :		The color you want to clear all the screen
******************************************************************************/
void LCD_1IN4_Clear(UWORD Color)
{
	UWORD i;
	UWORD image[LCD_1IN4_WIDTH];
	for(i=0;i<LCD_1IN4_WIDTH;i++){
		image[i] = Color>>8 | (Color&0xff)<<8;
	}
	UBYTE *p = (UBYTE *)(image);
	LCD_1IN4_SetWindow(0, 0, LCD_1IN4_WIDTH, LCD_1IN4_HEIGHT);
	DEV_Digital_Write(LCD_DC, 1);
	for(i = 0; i < LCD_1IN4_HEIGHT; i++){
		DEV_SPI_Write_nByte(p,LCD_1IN4_WIDTH*2);
	}
}

/******************************************************************************
function:	Refresh a certain area to the same color
parameter	:
	  Xstart: Start UWORD x coordinate
	  Ystart:	Start UWORD y coordinate
	  Xend  :	End UWORD coordinates
	  Yend  :	End UWORD coordinates
	  color :	Set the color
******************************************************************************/
void LCD_1IN4_ClearWindow(UWORD Xstart, UWORD Ystart, UWORD Xend, UWORD Yend,UWORD color)
{          
	UWORD i,j; 
	LCD_1IN4_SetWindow(Xstart, Ystart, Xend-1,Yend-1);
	for(i = Ystart; i <= Yend-1; i++){
		for(j = Xstart; j <= Xend-1; j++){
			LCD_1IN4_WriteData_Word(color);
		}
	}
}

/******************************************************************************
function: Show a picture
parameter	:
		image: Picture buffer
******************************************************************************/
void LCD_1IN4_Display(UBYTE *image)
{
	UWORD i;
	LCD_1IN4_SetWindow(0, 0, LCD_1IN4_WIDTH, LCD_1IN4_HEIGHT);
	DEV_Digital_Write(LCD_DC, 1);
	for(i = 0; i < LCD_1IN4_HEIGHT; i++){
		DEV_SPI_Write_nByte((UBYTE *)image+LCD_1IN4_WIDTH*2*i,LCD_1IN4_WIDTH*2);
	}
}

/******************************************************************************
function: Draw a point
parameter	:
	    X	: 	Set the X coordinate
	    Y	:	Set the Y coordinate
	  Color :	Set the color
******************************************************************************/
void LCD_1IN4_DrawPaint(UWORD x, UWORD y, UWORD Color)
{
	LCD_1IN4_SetCursor(x, y);
	LCD_1IN4_WriteData_Word(Color); 	    
}

void  Handler_1IN4_LCD(int signo)
{
    //System Exit
    printf("\r\nHandler:Program stop\r\n");     
    DEV_ModuleExit();
    exit(0);
}
