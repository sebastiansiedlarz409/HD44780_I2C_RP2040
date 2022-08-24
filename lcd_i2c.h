#pragma once

#include <stdint.h>

#include "pico/stdlib.h"
#include "hardware/i2c.h"

//SCREEN PINS
#define RS 0
#define RW 1
#define EN 2
#define BL 3 //backlight

#define D7 7
#define D6 6
#define D5 5
#define D4 4

#define RS_CMD 0
#define RS_DATA 1

#define RW_WRITE 0
#define RW_READ 1

#define EN_ENABLE 1
#define EN_DISABLE 0

i2c_inst_t* lcd_hi2c;
uint8_t lcd_address;
uint8_t lcd_rows;
uint8_t lcd_columns;
uint8_t lcd_data;

uint8_t LCD_Begin(i2c_inst_t* hi2c, uint8_t address, uint8_t rows, uint8_t columns, uint8_t blink, uint8_t backlight);
uint8_t LCD_Write();
uint8_t LCD_SetPin(uint8_t pin, uint8_t state);
uint8_t LCD_SendCmd(uint8_t cmd);
uint8_t LCD_SendData(uint8_t data);
uint8_t LCD_SendCharacter(uint8_t chr);
uint8_t LCD_SendString(const char* str);
uint8_t LCD_ClearScreen();
uint8_t LCD_MoveCursorLeft();
uint8_t LCD_MoveCursorRight();
uint8_t LCD_MoveDisplayLeft();
uint8_t LCD_MoveDisplayRight();
uint8_t LCD_BackLight(uint8_t on);
uint8_t LCD_TurnOff();
uint8_t LCD_TurnOn(uint8_t blink);
uint8_t LCD_SetCursorPosition(uint8_t row, uint8_t column);
uint8_t LCD_CursorOff();
uint8_t LCD_CursorOn(uint8_t blink);
