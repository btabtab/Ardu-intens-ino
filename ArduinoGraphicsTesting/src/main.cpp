#include <SPI.h>
#include <Arduino.h>
#include <HardwareSerial.h>

#include <U8g2lib.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>

#include "JDevRendering/jdr_base_functions.h"

U8G2_SH1106_128X64_NONAME_F_HW_I2C screen(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

void jdr_plot(int x, int y, Colour32 colour)
{
	screen.setDrawColor(!(!colour));
	
	/*
	The modulo here will keep the pixel
	within the bounds. While this may cause
	undesired wrapping it will most likely
	prevent crashing in some cases.
	*/
	screen.drawPixel(x % 128, y % 64);
}

void jdr_clearScreen()
{
	screen.clearBuffer();
	screen.sendBuffer();
}

void jdr_startDrawing()
{
	screen.clearBuffer();
}

void jdr_stopDrawing()
{
	screen.sendBuffer();
}

void setup()
{
	screen.begin();
}


void loop()
{
	static int z = 0;
	jdr_startDrawing();
	{
		jdr_plot((z >> 1) + 1, z++, 1);
	}
	jdr_stopDrawing();
}