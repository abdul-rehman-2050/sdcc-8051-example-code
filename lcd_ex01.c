/*
 */

#include <mcs51/8051.h>

#define LCD_PORT P0
#define LCD_RS P2_1
#define LCD_EN P2_0

#define NOP() \
    __asm     \
        nop   \
    __endasm  \


//============================================

__code unsigned char welcomeMessage[]={'w','e','l','c','o','m','e'};

//============================================
void lcd_init(void);
void lcd_cmd(unsigned char);
void lcd_data(unsigned char);
void DELAY(unsigned);
void lcd_puts(unsigned char*);
//=============================================
void main(void)
{

    lcd_init();
    lcd_puts(welcomeMessage);


    while(1)
        ;

}

//==================================================================================
void lcd_cmd(unsigned char cmd_val)  //Function to send command instruction to LCD
{
    LCD_PORT = cmd_val;
    LCD_RS= 0;
    LCD_EN=1;
    NOP();
    LCD_EN=0;
}

void lcd_data(unsigned char value)  //Function to send display data to LCD
{
    LCD_PORT = value;
    LCD_RS= 1;
    LCD_EN=1;
    NOP();
    LCD_EN=0;
}

 void lcd_init()    //Function to prepare the LCD  and get it ready
{
    lcd_cmd(0x38);  // for using 2 lines and 5X7 matrix of LCD
    DELAY(10);
    lcd_cmd(0x0F);  // turn display ON, cuLCD_RSor blinking
    DELAY(10);
    lcd_cmd(0x01);  //clear screen
    DELAY(10);
    lcd_cmd(0x81);  //force to line1 character 1
    DELAY(1);
}

void lcd_puts(unsigned char* str){
    while((*str) != '\0'){
        lcd_data(*str++);
    }
}
//=================================================================================

void DELAY(unsigned x){
    unsigned int i=1275;
    for(;x>0;x--)
        for(i=1275;i>0;i--);
}
