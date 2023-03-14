
#ifndef BUFFER_DRAW_H
#define BUFFER_DRAW_H

#define BYTE_BIT_COUNT (8)
#define VBUFFER_WIDTH (16)
#define VBUFFER_HEIGHT (VBUFFER_WIDTH * BYTE_BIT_COUNT)
#define VBUFFER_LENGTH (VBUFFER_WIDTH * VBUFFER_HEIGHT)

/*
	The way that the Vbuffer is going to work is that each bit is going to represent 1 pixel.
	This means that the end picture will be monocrome BUT will have a much higher resolution.
	This will save on memory by a massive factor.

	Alot of this takes inspiration from here:
		[https://github.com/btabtab/JDevTools/blob/master/JDT_source/ConsoleToolkit/ConsoleDraw.h]
*/

/*
	The Vbuffer contains an array of chars that each hold 8 bytes (ofc),
	Then by multiplying that (8) with the width of the X dimension
	you get the Y dimension of the buffer.
		For example:
			8 bits per char * 10 chars on X axis means 80 bits (or pixels).
			Then by mutliplying this by the result (80) we then get how many
			chars are needed for the Y axis.

			-> what a 4 width Vbuffer would result in.
				1 * 8	+ 1 * 8 + 1 * 8 + 1 * 8		4 bytes
				 8		 16		 24		 32			(X-axis == 64 bits (4 bytes))
			01 - [8 bits][8 bits][8 bits][8 bits]
			02 - [8 bits][8 bits][8 bits][8 bits]
			03 - [8 bits][8 bits][8 bits][8 bits]
			...
			61 - [8 bits][8 bits][8 bits][8 bits]
			62 - [8 bits][8 bits][8 bits][8 bits]
			63 - [8 bits][8 bits][8 bits][8 bits]
			64 - [8 bits][8 bits][8 bits][8 bits]
			Y-axis == (64 bits (64 rows of 8 bits * width))
								64 rows of 4 bytes
*/
typedef struct Vbuffer
{
	uint8_t buffer[VBUFFER_LENGTH];
}
Vbuffer;

Vbuffer* getVbufferBuffer()
{
	static Vbuffer vbuffer;
	return &vbuffer;
}

void initVbuffer(Vbuffer* vbuffer)
{
	for(int i = 0; i != SERIAL; i++)
	{
		vbuffer->buffer[i] = 0x00;
	}
}
#define resetVbuffer initVbuffer

typedef struct VbufferDecoder
{
	Vbuffer* vbuffer;
	//cursor values for decode tracking.
	int cursor_x, cursor_y;
}
VbufferDecoder;

int convert2DCoordValuesinto1D(int x, int y, int width)
{
	return x + (width * y);
}

void initVbufferDecoder(VbufferDecoder* vbuffer_decoder, Vbuffer* n_vbuffer)
{
	vbuffer_decoder->vbuffer = n_vbuffer;
	vbuffer_decoder->cursor_x = vbuffer_decoder->cursor_y = 0x00;
}

uint8_t* getVbufferPixelSetAddr(VbufferDecoder* decoder)
{
	return &decoder->vbuffer->buffer[convert2DCoordValuesinto1D(decoder->cursor_x, decoder->cursor_y, VBUFFER_WIDTH)];
}

/*
	[8]			[8]			[8]			[8]
	[00000000]	[00000000]	[00000000]	[00000000]


	int target: 10
	{10 - 8	;}	{2 - 8	;}	{		;}	{		;}
	[8]			[2]			[-]			[-]
	[--------]	[-X      ]	[        ]	[        ]
*/
int decodeXcoordIntoByteOffset(int x_pos, int width_of_buffer_in_bytes)
{
	int i = x_pos;
	// int bytes_skipped = 0;
	while (8 < i)
	{
		i =- 8;
		// bytes_skipped++;
	}
	return i;
}

bool getVbufferPixelValue(VbufferDecoder* decoder)
{
	int magic_number = decodeXcoordIntoByteOffset(decoder->cursor_x, VBUFFER_WIDTH / 8);
	return ((decoder->vbuffer->buffer[]) << magic_number - 1) >> magic_number;
}


#endif
