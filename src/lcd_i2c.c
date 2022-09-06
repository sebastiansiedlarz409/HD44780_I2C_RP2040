#include <stdint.h>

#include "lcd_i2c.h"
#include "pico/stdlib.h"
#include "hardware/i2c.h"

i2c_inst_t* lcd_hi2c;
uint8_t lcd_address;
uint8_t lcd_rows;
uint8_t lcd_columns;
uint8_t lcd_data;

uint8_t LCD_Begin(i2c_inst_t* hi2c, uint8_t address, uint8_t rows, uint8_t columns, uint8_t blink, uint8_t backlight){
	uint8_t status = 0;

	lcd_hi2c = hi2c;
	lcd_address = address;
	lcd_rows = rows;
	lcd_columns = columns;
	lcd_data = 0x00;

	LCD_BackLight(backlight);
	LCD_SendCmd(0);

	//init screen
	if(rows == 2){
		status |= LCD_SendCmd(0x28); //4bits 2 rows
	}
	else if(rows == 1){
		status |= LCD_SendCmd(0x20); //4bits 1 row
	}
	else{
		return 255;
	}

	//move to first position in first row
	if(blink){
		status |= LCD_SendCmd(0x0F);
	}
	else{
		status |= LCD_SendCmd(0x0E);
	}

	status |= LCD_SendCmd(0x01);
	status |= LCD_SendCmd(0x02);

	return status;
}

uint8_t LCD_Write(){
    return !i2c_write_blocking(lcd_hi2c, lcd_address, &lcd_data, 1, false);
}

uint8_t LCD_SetPin(uint8_t pin, uint8_t state){
	if(pin>7) return 255;

	if(state > 0)
		lcd_data |= (1<<pin);
	else
		lcd_data &= ~(1<<pin);

	return 0;
}

uint8_t LCD_BackLight(uint8_t on){
	if(on){
		return LCD_SetPin(BL, 1);
	}
	else{
		return LCD_SetPin(BL, 0);
	}
}

uint8_t LCD_PulseEnable(){
	uint8_t status = 0;

	status |= LCD_SetPin(EN, EN_ENABLE);
	status |= LCD_Write();
	sleep_ms(10);
	status |= LCD_SetPin(EN, EN_DISABLE);
	status |= LCD_Write();
	sleep_ms(10);

	return status;
}

uint8_t LCD_SendCmd(uint8_t cmd){
	uint8_t status = 0;

	uint8_t hn = (cmd>>4)&0x0F;
	uint8_t ln = cmd&0x0F;

	status |= LCD_SetPin(RW, RW_WRITE);
	status |= LCD_SetPin(RS, RS_CMD);

	lcd_data &= 0x0F; //clear data bits
	status |= LCD_SetPin(D4, hn&0b0001);
	status |= LCD_SetPin(D5, hn&0b0010);
	status |= LCD_SetPin(D6, hn&0b0100);
	status |= LCD_SetPin(D7, hn&0b1000);
	status |= LCD_PulseEnable();

	lcd_data &= 0x0F; //clear data bits
	status |= LCD_SetPin(D4, ln&0b0001);
	status |= LCD_SetPin(D5, ln&0b0010);
	status |= LCD_SetPin(D6, ln&0b0100);
	status |= LCD_SetPin(D7, ln&0b1000);
	status |= LCD_PulseEnable();

	return status;
}

uint8_t LCD_SendData(uint8_t data){
	uint8_t status = 0;

	uint8_t hn = (data>>4)&0x0F;
	uint8_t ln = data&0x0F;

	status |= LCD_SetPin(RW, RW_WRITE);
	status |= LCD_SetPin(RS, RS_DATA);

	lcd_data &= 0x0F; //clear data bits
	status |= LCD_SetPin(D4, hn&0b0001);
	status |= LCD_SetPin(D5, hn&0b0010);
	status |= LCD_SetPin(D6, hn&0b0100);
	status |= LCD_SetPin(D7, hn&0b1000);
	status |= LCD_PulseEnable();

	lcd_data &= 0x0F; //clear data bits
	status |= LCD_SetPin(D4, ln&0b0001);
	status |= LCD_SetPin(D5, ln&0b0010);
	status |= LCD_SetPin(D6, ln&0b0100);
	status |= LCD_SetPin(D7, ln&0b1000);
	status |= LCD_PulseEnable();

	return status;
}

uint8_t LCD_SendCharacter(uint8_t chr){
	return LCD_SendData(chr);
}

uint8_t LCD_SendString(const char* str){
	uint8_t status = 0;
	while(*str){
		status |= LCD_SendCharacter((uint8_t)*str);
		str++;
	}
	return status;
}

uint8_t LCD_ClearScreen(){
	return LCD_SendCmd(0x01);
}

uint8_t LCD_MoveCursorLeft(){
	return LCD_SendCmd(0x10);
}

uint8_t LCD_MoveCursorRight(){
	return LCD_SendCmd(0x14);
}

uint8_t LCD_MoveDisplayLeft(){
	return LCD_SendCmd(0x18);
}

uint8_t LCD_MoveDisplayRight(){
	return LCD_SendCmd(0x1C);
}

uint8_t LCD_SetCursorPosition(uint8_t row, uint8_t column){
	if(row >= lcd_rows || column >= lcd_columns) return 255;

	uint8_t status = LCD_SendCmd(0x02);

	uint8_t offset = (row*0x40)+column;
	return LCD_SendCmd(0x80+offset) | status;
}

uint8_t LCD_TurnOff(){
	return LCD_SendCmd(0x08);
}

uint8_t LCD_TurnOn(uint8_t blink){
	if (blink)
		return LCD_SendCmd(0xF);
	else
		return LCD_SendCmd(0xE);
}

uint8_t LCD_CursorOff(){
	return LCD_SendCmd(0x0C);
}

uint8_t LCD_CursorOn(uint8_t blink){
	return LCD_TurnOn(blink);
}
