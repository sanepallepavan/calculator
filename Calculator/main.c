#include <reg51.h>
sbit rs = P2 ^ 0;
sbit en = P2 ^ 1;
sfr port_data = 0xB0;
sfr port_1 = 0x90;
sbit r1 = P1 ^ 0;
sbit r2 = P1 ^ 1;
sbit r3 = P1 ^ 2;
sbit r4 = P1 ^ 3;
sbit c1 = P1 ^ 4;
sbit c2 = P1 ^ 5;
sbit c3 = P1 ^ 6;
sbit c4 = P1 ^ 7;
void lcd_print(volatile long);
void calculateResult();
char findkey();
void delay(unsigned int);
void lcd_cmd(unsigned char);
void lcd_init();
void charDisplay(unsigned char);
void strDisplay(unsigned char *);
void calculateNumber(char);
unsigned int i;
char key, action;
void clearLcd();
int num1 = 0, num2 = 0, number = 0, result = 0;
/*------------------------------------Main Function--------------------------------------------------------------*/
void main()
{
    lcd_init();
    strDisplay("Calculator ");
    lcd_cmd(0xC0);
    strDisplay("Enter the values ");
    delay(500000);
    clearLcd();
    while (1)
    {
        key = findkey();
        calculateNumber(key);
    }
}
/*------------------------------------LCD clear Function--------------------------------------------------------------*/
void clearLcd()
{
    lcd_cmd(0x01);
    lcd_cmd(0x80);
}
/*------------------------------------Delay Function--------------------------------------------------------------*/
void delay(unsigned int i)
{
    unsigned int x;
    for (x = 0; x < i; x++)
        ;
}
/*------------------------------------LCD Commands Function--------------------------------------------------------------*/
void lcd_cmd(unsigned char cmd)
{
    rs = 0; // cmd
    port_data = cmd;
    en = 1;
    delay(1000);
    en = 0;
}
/*------------------------------------Functions for LCD Print Characters --------------------------------------------------------------*/
void charDisplay(unsigned char lcd_data)
{
    rs = 1; // data
    port_data = lcd_data;
    en = 1;
    delay(1000);
    en = 0;
    delay(1000);
}
/*------------------------------------LCD setup Function--------------------------------------------------------------*/
void lcd_init()
{
    lcd_cmd(0x38); // 8 BIT MODE AND 2 LINE
    lcd_cmd(0x0F); // display on and cursor on and blink on
    lcd_cmd(0x01); // clear dispaly
    lcd_cmd(0x80); // set cursor to first line
}
/*------------------------------------String Dispaly Function--------------------------------------------------------------*/
void strDisplay(unsigned char *str)
{
    while (*str)
        charDisplay(*str++);
}
/*------------------------------------Result Function--------------------------------------------------------------*/
void calculateResult()
{
    if (action == '+')
        result = num1 + num2;
    else if (action == '-')
        result = num1 - num2;
    else if (action == '*')
        result = num1 * num2;
    else if (action == '/' && (num2 != 0))
        result = num1 / num2;
    else
    {
        clearLcd();
        strDisplay("Inavalid Inputs");
        delay(90000);
        number = num1 = num2 = result = action = 0;
        clearLcd();
    }
    clearLcd();
    strDisplay("RESULT :");
    lcd_cmd(0xC0);
    lcd_print(result);
    delay(60000);
    lcd_cmd(0x80);
    strDisplay("             ");
    lcd_cmd(0x80);
}
/*------------------------------------Number Print Function--------------------------------------------------------------*/
void lcd_print(volatile long printNumber)
{
    volatile char i = 0, j, num[20], revNum[20], length = 0;
    if (printNumber < 0)
    {
        charDisplay('-');
        printNumber = ~printNumber + 1;
    }
    if (printNumber == 0)
    {
        charDisplay('0');
    }

    while (printNumber)
    {
        revNum[i++] = printNumber % 10;
        printNumber /= 10;
        length++;
    }
    length--;

    for (i = 0, j = length; i <= length; i++, j--)
    {
        num[i] = revNum[j] + '0';
    }

    for (i = 0; i <= length; i++)
    {
        charDisplay(num[i]);
    }
}
/*------------------------------------Calculatiing Number--------------------------------------------------------------*/
void calculateNumber(char key)
{
    charDisplay(key);
    if (key == '/' || key == '*' || key == '-' || key == '+')
    {
        if (result)
        {
            num1 = result;
            result = num2 = number = 0;
            action = key;
        }
        else
        {
            num1 = number;
            number = 0;
            action = key;
        }
    }
    else if (key == '=')
    {
        num2 = number;
        number = 0;
        calculateResult();
    }
    else if (key == 'c')
    {
        number = num1 = num2 = result = action = 0;
        clearLcd();
    }
    else if (key >= '0' && key <= '9')
    {

        if (number == 0)
            number = key - '0';
        else
            number = (number * 10) + (key - '0');
    }
    delay(2000);
}
/*------------------------------------Finding Which key Pressed--------------------------------------------------------------*/
char findkey() {
    while (1) {
        
        r1 = 0; r2 = r3 = r4 = 1; 
        if (c1 == 0) { delay(20000); while (c1 == 0); return '7'; } 
        if (c2 == 0) { delay(20000); while (c2 == 0); return '8'; } 
        if (c3 == 0) { delay(20000); while (c3 == 0); return '9'; } 
        if (c4 == 0) { delay(20000); while (c4 == 0); return '/'; } 

       
        r2 = 0; r1 = r3 = r4 = 1; 
        if (c1 == 0) { delay(20000); while (c1 == 0); return '4'; } 
        if (c2 == 0) { delay(20000); while (c2 == 0); return '5'; } 
        if (c3 == 0) { delay(20000); while (c3 == 0); return '6'; } 
        if (c4 == 0) { delay(20000); while (c4 == 0); return '*'; } 

        
        r3 = 0; r1 = r2 = r4 = 1;
        if (c1 == 0) { delay(20000); while (c1 == 0); return '1'; } 
        if (c2 == 0) { delay(20000); while (c2 == 0); return '2'; } 
        if (c3 == 0) { delay(20000); while (c3 == 0); return '3'; } 
        if (c4 == 0) { delay(20000); while (c4 == 0); return '-'; } 

        
        r4 = 0; r1 = r2 = r3 = 1; 
        if (c1 == 0) { delay(20000); while (c1 == 0); return 'c'; } 
        if (c2 == 0) { delay(20000); while (c2 == 0); return '0'; } 
        if (c3 == 0) { delay(20000); while (c3 == 0); return '='; } 
        if (c4 == 0) { delay(20000); while (c4 == 0); return '+'; } 
    }
}