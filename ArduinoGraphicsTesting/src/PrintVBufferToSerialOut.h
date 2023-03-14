#include <HardwareSerial.h>

#include "../../../JDevTools/JDT_source/ConsoleToolkit/ConsoleDraw.h"

char* getPrintBuffer()
{
    static char print_buffer[0xff] = "";
    return print_buffer;
}

void drawPixelSRL(PixelData data)
{
	setScreenColour(data.screen_colour);
    Serial.write(data.character);
	if(getTerminalSettings()->double_spaced_draw)
	{
		printf("%c", data.character);
	}
}

void drawBorderTopSRL(bool draw_border, int buffer_width, bool lettered_top)
{
	if(getTerminalSettings()->double_spaced_draw){draw_border *= 2;}
	if(draw_border)
	{
		printf("\t");
		drawPixel(newPixel(RESET, '/'));
		if(lettered_top)
		{
			for(int i = 0; i != 2; i++)
			{
				for(int j = 0; j != buffer_width; j++)
				{
					char temp[3] = "";
					sprintf(temp, "%02d", j);
					drawPixelSRL(newPixel(RESET, temp[i]));
				}
				char end_char[3] = {"\\|"};
				printf("%c\n", end_char[i]);
				if(!i)
				{
					printf("\t|");
				}
			}
		}
		else
		{
			drawPixel(newPixel(RESET, '`'));
			for(int i = 1; i != buffer_width - 1; i++)
			{
				drawPixel(newPixel(RESET, '`'));
			}
			drawPixel(newPixel(RESET, '`'));
			drawPixel(newPixel(RESET, '\\'));
		}
	}
}
void drawBorderBottomSRL(bool draw_border, int buffer_width)
{
	if(draw_border)
	{
		printf("\t");
		drawPixel(newPixel(RESET, '\\'));
		drawPixel(newPixel(RESET, '_'));
		for(int i = 1; i != buffer_width - 1; i++)
		{
			drawPixel(newPixel(RESET, '_'));
		}
		drawPixel(newPixel(RESET, '_'));
		drawPixel(newPixel(RESET, '/'));
	}
	printf("\n");
}

void drawBufferContentsSRL(VBuffer* buffer, bool draw_border)
{
	for(int x = 0; x != buffer->width; x++)
	{
		printf("%02d\t", x);
		if(draw_border){drawPixel(newPixel(RESET, '|'));}
		for(int y = 0; y != buffer->width; y++)
		{
			// printf("x %d y %d\n", x, y);
			drawPixel(
						buffer->data[getArrayAccessFromPoint((Point){y, x}, buffer->width)]
					);
		}
		if(draw_border){drawPixel(newPixel(RESET, '|'));}
		printf("\n");
	}
}

void drawBufferSRL(VBuffer* buffer, bool draw_border, bool lettered)
{
	printf("\ndrawBuffer %p\n", (void*)buffer);

	drawBorderTop(draw_border, buffer->width, lettered);
	drawBufferContents(buffer, draw_border);
	drawBorderBottom(draw_border, buffer->width);
