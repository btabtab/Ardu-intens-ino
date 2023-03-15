#include <SPI.h>
#include <Arduino.h>
#include <HardwareSerial.h>

#include <U8g2lib.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>

#include "JDevRendering/jdr_base_functions.h"
#include "JDevRendering/jdr_super_functions.h"

U8G2_SH1106_128X64_NONAME_F_HW_I2C screen(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

void jdr_plot(int x, int y, Colour32 colour)
{
	// screen.setDrawColor(!(!colour));
	
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

void jdr_drawLine(int ax, int ay, int bx, int by, Colour32 colour)
{
	screen.drawLine(ax % 128, ay % 64, bx % 128, by % 64);
}

void setup()
{
	screen.begin();
}


void loop()
{
	static uint16_t z = 0, a = 0;
	jdr_startDrawing();
	{
		jdr_plot(z - 1, a, 1);
		jdr_plot(z, a, 1);
	}
	jdr_stopDrawing();
	if(z==128){a++;}
	z += 2;
}