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

char findkey();
void delay(unsigned int);
void lcd_cmd(unsigned char);
void lcd_init();
void charDisplay(unsigned char);
void strDisplay(unsigned char *);
void calculate(char);
void clearLCD();
void lcd_print(volatile long);
void pressedKey(char key);

int number = 0, num1 = 0, num2 = 0, result = 0;
char action = 0;

void main()
{
    lcd_init();               
    strDisplay("Calculator"); 
    delay(2000);
    clearLCD(); 

    while (1)
    {
        char key = findkey(); 
        pressedKey(key);      
    }
}

void delay(unsigned int i)
{
    unsigned int x;
    for (x = 0; x < i; x++)
        ;
}

void lcd_cmd(unsigned char cmd)
{
    rs = 0;
    port_data = cmd;
    en = 1;
    delay(1000);
    en = 0;
}

void charDisplay(unsigned char lcd_data)
{
    rs = 1;
    port_data = lcd_data;
    en = 1;
    delay(1000);
    en = 0;
    delay(1000);
}

void lcd_init()
{
    lcd_cmd(0x38);
    lcd_cmd(0x0F);
    lcd_cmd(0x01);
    lcd_cmd(0x80);
}

void strDisplay(unsigned char *str)
{
    while (*str)
        charDisplay(*str++);
}

void clearLCD()
{
    lcd_cmd(0x01);
    lcd_cmd(0x80);
}

void lcd_print(volatile long num)
{
	
    char buf[10];
    int i = 0;
    int j;
			if (num < 0) {
			charDisplay('-');
			num = ~num + 1; 
		}
    if (num == 0)
    {
        charDisplay('0');
        return;
    }
    while (num)
    {
        buf[i++] = (num % 10) + '0';
        num /= 10;
    }
    for (j = i - 1; j >= 0; j--)
    {
        charDisplay(buf[j]);
    }
}

void pressedKey(char key)
{
    if (key >= '0' && key <= '9')
    {
        number = (number * 10) + (key - '0');
        charDisplay(key);
    }
    else if (key == '+' || key == '-' || key == '*' || key == '/')
    {
        num1 = number;
        number = 0;
        action = key;
        charDisplay(key);
    }
    else if (key == '=')
    {
        num2 = number;
        number = 0;
        if (action == '+')
            result = num1 + num2;
        else if (action == '-')
            result = num1 - num2;
        else if (action == '*')
            result = num1 * num2;
        else if (action == '/' && num2 != 0)
            result = num1 / num2;
        else
        {
            strDisplay("Invalid Inputs");
            delay(2000);
            clearLCD();
            return;
        }
        clearLCD();
        lcd_print(result);
        num1 = result;
    }
    else if (key == 'C')
    {
        num1 = num2 = result = number = 0;
        clearLCD();
    }
}
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

        
        r3 = 0; r1 = r2 = r4 = 1; // Activate row 3
        if (c1 == 0) { delay(20000); while (c1 == 0); return '1'; } 
        if (c2 == 0) { delay(20000); while (c2 == 0); return '2'; } 
        if (c3 == 0) { delay(20000); while (c3 == 0); return '3'; } 
        if (c4 == 0) { delay(20000); while (c4 == 0); return '-'; } 

        
        r4 = 0; r1 = r2 = r3 = 1; // Activate row 4
        if (c1 == 0) { delay(20000); while (c1 == 0); return 'C'; } 
        if (c2 == 0) { delay(20000); while (c2 == 0); return '0'; } 
        if (c3 == 0) { delay(20000); while (c3 == 0); return '='; } 
        if (c4 == 0) { delay(20000); while (c4 == 0); return '+'; } 
    }
}
