#include "RA8875.h"
#include <P24EP512GP806.h>

#define CS_LCD_HIGH LATDbits.LATD4 = 1
#define CS_LCD_LOW  LATDbits.LATD4 = 0

#define DISPLAY_BUSY_STATUS PORTDbits.RD1
#define DISPLAY_INT_STATUS  PORTDbits.RD0

#define RA8875_BUSY 0
#define RA8875_IDLE 1

unsigned int _width = 800;
unsigned int _height = 480;


void delay_ms (unsigned long value)
{
	unsigned long timer = 0;
	for (timer = 0; timer < value; timer++)
	{
		Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();
		Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();
		Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();
		Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();
	}
};

// ======================================================================================
// display init
// ======================================================================================
void ra8875_init (void)
{
	
	unsigned char pixclk = RA8875_PCSR_PDATL | RA8875_PCSR_2CLK;
  	unsigned char  hsync_start    = 32;
  	unsigned char  hsync_pw       = 96;
  	unsigned char  hsync_finetune = 0;
  	unsigned char  hsync_nondisp  = 26;
  	unsigned char  vsync_pw       = 2;
  	unsigned int   vsync_nondisp  = 32;
  	unsigned int   vsync_start    = 23;


	RPOR1bits.RP66R = 0b000101;  // SPI 1 MOSI OUTPUT
	RPOR2bits.RP69R = 0b000110;  // SPI 1 CLK OUTPUT
	RPINR20bits.SDI1R = 0b1000000;
	
	CS_LCD_HIGH;
	LATDbits.LATD5 = 1;
	LATDbits.LATD2 = 1;

	TRISDbits.TRISD1 = 1; // DISPLAY BUSY
	TRISDbits.TRISD4 = 0; // DISPLAY CS
	TRISDbits.TRISD5 = 0; // SPI CLK
	TRISDbits.TRISD2 = 0; // SPI MOSI
	//TRISDbits.TRISD3 = 0; // LED
	TRISDbits.TRISD0 = 1; // DISPLAY INTERRUPT
	
	
	
	SPI1CON1bits.DISSCK = 0; // Internal serial clock is enabled
	SPI1CON1bits.DISSDO = 0; // SDOx pin is controlled by the module
	SPI1CON1bits.MODE16 = 0; // Communication is byte-wide (8 bits)
	SPI1CON1bits.SMP = 0; // Input data is sampled at the middle of data output time
	SPI1CON1bits.SSEN = 1;
	
	SPI1CON1bits.CKE = 0; // 0
	SPI1CON1bits.CKP = 1; // 1
	
	
	
	// 60 FP / 4 * 4 = 3.75 mHz
	SPI1CON1bits.PPRE = 0b01;  // primary prescaler = 4
	SPI1CON1bits.SPRE = 0b100; // secondary prescaler = 4
	
	// active state is a high-level
	SPI1CON1bits.MSTEN = 1; // Master mode enabled
	SPI1STATbits.SPIEN = 1; // Enable SPI module


	
	
	// RA8875 PLL CONFIGURE
  	writeReg_slow (RA8875_PLLC1, 11);
  	delay_ms (10000);
  	writeReg_slow(RA8875_PLLC2, RA8875_PLLC2_DIV4);
  	delay_ms (10000);
  	writeReg_slow (RA8875_SYSR, RA8875_SYSR_16BPP | RA8875_SYSR_MCU8);
  	delay_ms (10000);
  	writeReg_slow(RA8875_PCSR, pixclk);
  	delay_ms (10000);
  	
  	
  	
  	SPI1STATbits.SPIEN = 0;
  	
	// 60 FP / 1 * 3 = 20 mHz
	SPI1CON1bits.PPRE = 0b11;  // primary prescaler = 1 // 11
	SPI1CON1bits.SPRE = 0b101; // secondary prescaler = 3 // 101
	SPI1STATbits.SPIEN = 1;
	

	// Horizontal settings registers
	writeReg(RA8875_HDWR, 0x63); // (99 + 1) * 8 = 800 width
	writeReg(RA8875_HNDFTR, RA8875_HNDFTR_DE_HIGH + hsync_finetune);
 	writeReg(RA8875_HNDR, (hsync_nondisp - hsync_finetune - 2)/8);    // H non-display: HNDR * 8 + HNDFTR + 2 = 10
	writeReg(RA8875_HSTR, hsync_start / 8 - 1);                         // Hsync start: (HSTR + 1)*8 
	writeReg(RA8875_HPWR, RA8875_HPWR_LOW + (hsync_pw/8 - 1));        // HSync pulse width = (HPWR+1) * 8
	
	// Vertical settings registers
	writeReg(RA8875_VDHR0, 0xDF);  // 1DF = 479 height
	writeReg(RA8875_VDHR1, 0x01);
	writeReg(RA8875_VNDR0, vsync_nondisp-1);                          // V non-display period = VNDR + 1
	writeReg(RA8875_VNDR1, vsync_nondisp >> 8);
	writeReg(RA8875_VSTR0, vsync_start-1);                            // Vsync start position = VSTR + 1
	writeReg(RA8875_VSTR1, vsync_start >> 8);
	writeReg(RA8875_VPWR, RA8875_VPWR_LOW + vsync_pw - 1);            // Vsync pulse width = VPWR + 1
	
	// Set active window X
	writeReg(RA8875_HSAW0, 0);                                        // horizontal start point
	writeReg(RA8875_HSAW1, 0);
	writeReg(RA8875_HEAW0, 0x1F); // 31F = 799
	writeReg(RA8875_HEAW1, 0x03);
	
	// Set active window Y
	writeReg(RA8875_VSAW0, 0);                                        // vertical start point
	writeReg(RA8875_VSAW1, 0);  
	writeReg(RA8875_VEAW0, 0xDF);           // horizontal end point
	writeReg(RA8875_VEAW1, 0x01);
	
	// ToDo: Setup touch panel?
	
	// Clear the entire window
	writeReg(RA8875_MCLR, RA8875_MCLR_START | RA8875_MCLR_FULL);
	delay_ms (10000); 
	
	
}


// ======================================================================================
// Software reset
// ======================================================================================
void ra8875_soft_reset(void)
{
  writeCommand(RA8875_PWRR);
  writeData(RA8875_PWRR_SOFTRESET);
  writeData(RA8875_PWRR_NORMAL);
  delay_ms(10000);
}

// ======================================================================================
// Sets display on / off
// ======================================================================================
void ra8875_display_on (char on) 
{
	if (on) writeReg(RA8875_PWRR, RA8875_PWRR_NORMAL | RA8875_PWRR_DISPON); else writeReg(RA8875_PWRR, RA8875_PWRR_NORMAL | RA8875_PWRR_DISPOFF);
}

// ======================================================================================
// Sets sleep
// ======================================================================================
void ra8875_sleep (char sleep) 
{
	if (sleep) writeReg(RA8875_PWRR, RA8875_PWRR_DISPOFF | RA8875_PWRR_SLEEP); else writeReg(RA8875_PWRR, RA8875_PWRR_DISPOFF);
}




// ======================================================================================
// Sets the current X/Y position on the display before drawing
//    
// x[in] The 0-based x location
// y[in] The 0-base y location
// ======================================================================================
void ra8875_set_xy_position (unsigned int x, unsigned int y)
{
	writeReg (RA8875_CURH0, (unsigned char)x);
	writeReg (RA8875_CURH1, (unsigned char)(x >> 8));
	writeReg (RA8875_CURV0, (unsigned char)y);
	writeReg (RA8875_CURV1, (unsigned char)(y >> 8));
}












// ======================================================================================
// DRAW PIXEL
// ======================================================================================
void ra8875_draw_pixel(unsigned int x, unsigned int y, unsigned int color)
{
 	writeReg (RA8875_CURH0, x);
 	writeReg (RA8875_CURH1, x >> 8);
 	writeReg (RA8875_CURV0, y);
 	writeReg (RA8875_CURV1, y >> 8);  
	writeReg (RA8875_MRWC, color);
}


// ======================================================================================
// Draws a HW accelerated line on the display
// ======================================================================================
void ra8875_draw_line (unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1, unsigned int color)
{
	// Set active window X
	writeReg(RA8875_HSAW0, 0);
	writeReg(RA8875_HSAW1, 0);
	writeReg(RA8875_HEAW0, 0x1F);
	writeReg(RA8875_HEAW1, 0x03);
	
	// Set active window Y
	writeReg(RA8875_VSAW0, 0);
	writeReg(RA8875_VSAW1, 0);  
	writeReg(RA8875_VEAW0, 0xDF);
	writeReg(RA8875_VEAW1, 0x01);
		
	writeReg (RA8875_CURH0, 0);
	writeReg (RA8875_CURH1, 0);
	writeReg (RA8875_CURV0, 0);
	writeReg (RA8875_CURV1, 0); 
		
	/* Set X */
	writeReg(0x91, (unsigned char)x0);
	writeReg(0x92, (unsigned char)(x0 >> 8));
	
	/* Set Y */
	writeReg(0x93, (unsigned char)y0);
	writeReg(0x94, (unsigned char)(y0 >> 8));
	
	/* Set X1 */
	writeReg(0x95, (unsigned char)x1);
	writeReg(0x96, (unsigned char)(x1 >> 8));
	
	/* Set Y1 */
	writeReg(0x97, (unsigned char)y1);
	writeReg(0x98, (unsigned char)(y1 >> 8));
	
	/* Set Color */
	writeReg(RA8875_FGCR0, (unsigned char)(color >> 11)); // red bits
	writeReg(RA8875_FGCR1, (unsigned char)((color & 0x7E0) >> 5));  // green bits
	writeReg(RA8875_FGCR2, (unsigned char)(color & 0x1F)); // blue bits
	
	/* Draw! */
	writeReg(RA8875_DCR, 0x80);
	while (DISPLAY_BUSY_STATUS == RA8875_BUSY) {};

}








// ======================================================================================
// Draws a HW accelerated circle on the display
//
// x[in]     The 0-based x location of the center of the circle
// y[in]     The 0-based y location of the center of the circle
// w[in]     The circle's radius
// color[in] The RGB565 color to use when drawing the pixel
// filled    True of false
// ======================================================================================
void ra8875_draw_circle(unsigned int x0, unsigned int y0, unsigned int r, unsigned int color, char filled)
{
	// Set active window X
	writeReg(RA8875_HSAW0, 0);
	writeReg(RA8875_HSAW1, 0);
	writeReg(RA8875_HEAW0, 0x1F);
	writeReg(RA8875_HEAW1, 0x03);
	
	// Set active window Y
	writeReg(RA8875_VSAW0, 0);
	writeReg(RA8875_VSAW1, 0);  
	writeReg(RA8875_VEAW0, 0xDF);
	writeReg(RA8875_VEAW1, 0x01);
		
	writeReg (RA8875_CURH0, 0);
	writeReg (RA8875_CURH1, 0);
	writeReg (RA8875_CURV0, 0);
	writeReg (RA8875_CURV1, 0); 
	
	
	/* Set X */
	writeReg (0x99, x0);
	writeReg (0x9a, x0 >> 8);
		
	/* Set Y */
	writeReg(0x9b, y0);
	writeReg(0x9c, y0 >> 8);	   
		
	/* Set Radius */
	writeReg(0x9d, r);
		
	/* Set Color */
	writeReg(RA8875_FGCR0,  color >> 11); // red bits
	writeReg(RA8875_FGCR1, (color & 0x7E0) >> 5);  // green bits
	writeReg(RA8875_FGCR2,  color & 0x1F); // blue bits
		
	/* Draw! */
	if (filled) writeReg(RA8875_DCR, RA8875_DCR_CIRCLE_START | RA8875_DCR_FILL); else writeReg(RA8875_DCR, RA8875_DCR_CIRCLE_START | RA8875_DCR_NOFILL);
	
	while (DISPLAY_BUSY_STATUS == RA8875_BUSY) {};
}







// ======================================================================================
// Draws a HW accelerated circle square on the display
//
// x[in]     The 0-based x location of the center of the circle
// y[in]     The 0-based y location of the center of the circle
// w[in]     The circle's radius
// color[in] The RGB565 color to use when drawing the pixel
// filled    True of false
// ======================================================================================
void ra8875_draw_circle_sqr (unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1,unsigned char r, unsigned int color, char filled)
{
    // Set active window X
    writeReg(RA8875_HSAW0, 0);
    writeReg(RA8875_HSAW1, 0);
    writeReg(RA8875_HEAW0, 0x1F);
    writeReg(RA8875_HEAW1, 0x03);
  
    // Set active window Y
    writeReg(RA8875_VSAW0, 0);
    writeReg(RA8875_VSAW1, 0);  
    writeReg(RA8875_VEAW0, 0xDF);
    writeReg(RA8875_VEAW1, 0x01);
	
    writeReg (RA8875_CURH0, 0);
    writeReg (RA8875_CURH1, 0);
	writeReg (RA8875_CURV0, 0);
	writeReg (RA8875_CURV1, 0); 
	
    /* Set X */
    writeReg(0x91, (unsigned char)x0);
    writeReg(0x92, (unsigned char)(x0 >> 8));

    /* Set Y */
    writeReg(0x93, (unsigned char)y0);
    writeReg(0x94, (unsigned char)(y0 >> 8));	   

    /* Set X1 */
    writeReg(0x95, (unsigned char)x1);
    writeReg(0x96, (unsigned char)(x1 >> 8));

    /* Set Y1 */
    writeReg(0x97, (unsigned char)y1);
    writeReg(0x98, (unsigned char)(y1 >> 8));   

    /* Set Radius */
    writeReg(0xA1, (unsigned char)r);
    writeReg(0xA2, (unsigned char)(r >> 8));   
    writeReg(0xA3, (unsigned char)r);
    writeReg(0xA4, (unsigned char)(r >> 8));   

    /* Set Color */
	writeReg(RA8875_FGCR0,  color >> 11); // red bits
	writeReg(RA8875_FGCR1, (color & 0x7E0) >> 5);  // green bits
	writeReg(RA8875_FGCR2,  color & 0x1F); // blue bits

    /* Draw! */
    if (filled) writeReg(0xA0, 0xE0); else writeReg(0xA0, 0xA0);

    while (DISPLAY_BUSY_STATUS == RA8875_BUSY) {};
}

// ======================================================================================
//      Draws a HW accelerated rectangle on the display
//
//      x[in]     The 0-based x location of the top-right corner
//      y[in]     The 0-based y location of the top-right corner
//      w[in]     The rectangle width
//      h[in]     The rectangle height
//      color[in] The RGB565 color to use when drawing the pixel
//			filled    True or false
// ======================================================================================
void ra8875_draw_rectangle(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1, unsigned int color, char filled)
{
	// Set active window X
	writeReg(RA8875_HSAW0, 0);
	writeReg(RA8875_HSAW1, 0);
	writeReg(RA8875_HEAW0, 0x1F);
	writeReg(RA8875_HEAW1, 0x03);
	
	// Set active window Y
	writeReg(RA8875_VSAW0, 0);
	writeReg(RA8875_VSAW1, 0);  
	writeReg(RA8875_VEAW0, 0xDF);
	writeReg(RA8875_VEAW1, 0x01);
	
	writeReg (RA8875_CURH0, 0);
	writeReg (RA8875_CURH1, 0);
	writeReg (RA8875_CURV0, 0);
	writeReg (RA8875_CURV1, 0); 
	
	/* Set X */
	writeReg(0x91, (unsigned char)x0);
	writeReg(0x92, (unsigned char)(x0 >> 8));
	
	/* Set Y */
	writeReg(0x93, (unsigned char)y0);
	writeReg(0x94, (unsigned char)(y0 >> 8));	   
	
	/* Set X1 */
	writeReg(0x95, (unsigned char)x1);
	writeReg(0x96, (unsigned char)(x1 >> 8));
	
	
	/* Set Y1 */
	writeReg(0x97, (unsigned char)y1);
	writeReg(0x98, (unsigned char)(y1 >> 8));
	
	/* Set Color */
	writeReg(RA8875_FGCR0,  color >> 11); // red bits
	writeReg(RA8875_FGCR1, (color & 0x7E0) >> 5);  // green bits
	writeReg(RA8875_FGCR2,  color & 0x1F); // blue bits
	
	/* Draw! */
	if (filled) writeReg(RA8875_DCR, 0xB0); else  writeReg(RA8875_DCR, 0x90);
	
	while (DISPLAY_BUSY_STATUS == RA8875_BUSY) {};
}


// ======================================================================================
// DRAW RECTANGLE BTE
// ======================================================================================
void ra8875_draw_rectangle_bte (unsigned int x, unsigned int y, unsigned int width, unsigned int height, unsigned int color)
{
	int i = 0;
	
	unsigned char color_h = (unsigned char)(color >> 8);
	unsigned char color_l = (unsigned char)color;
	
	
	// Set X
	writeReg (RA8875_HDBE0, (unsigned char)x);
	writeReg (RA8875_HDBE1, (unsigned char)(x >> 8));
	
	// Set Y
	writeReg (RA8875_VDBE0, (unsigned char)y);
	writeReg (RA8875_VDBE1, (unsigned char)(y >> 8));  
	
	// Set width
	writeReg (RA8875_BEWR0, (unsigned char)width);
	writeReg (RA8875_BEWR1, (unsigned char)(width >> 8));
	
	// Set height
	writeReg (RA8875_BEHR0, (unsigned char)height);
	writeReg (RA8875_BEHR1, (unsigned char)(height >> 8));
	
	// Set transparent color = COLOR_BLACK
	writeReg (RA8875_FGCR0, 0x00);
	writeReg (RA8875_FGCR1, 0x00);  
	writeReg (RA8875_FGCR2, 0x00);
	
	writeReg (RA8875_BECR1, 0b11100000);  // bits 7.. 4 BOOLEAN FUNCTION OPERATIONS / 0 .. 3  ROP FUNCTION
	
	// Switch on BTE function
	writeReg (RA8875_BECR0, 0x80); 

	delay_ms (1);
	CS_LCD_LOW;
	delay_ms (1);
	
	SPI1BUF = RA8875_CMDWRITE;
	while (SPI1STATbits.SPITBF == 1) {}

	
	SPI1BUF = RA8875_MRWC;
	while (SPI1STATbits.SPITBF == 1) {}
	
	SPI1BUF = RA8875_DATAWRITE;
	while (SPI1STATbits.SPITBF == 1) {}

	for (i = 0; i < (width * height); i++)
	{
		SPI1BUF = color_h;
		while (SPI1STATbits.SPITBF == 1) {}
		SPI1BUF = color_l;
		while (SPI1STATbits.SPITBF == 1) {}
				
		while (DISPLAY_BUSY_STATUS == RA8875_BUSY) {};
	}


	delay_ms (1);
	CS_LCD_HIGH;
	delay_ms (1);


}



// ======================================================================================
//      Draws a HW accelerated triangle on the display
//
//      x0[in]    The 0-based x location of point 0 on the triangle
//      0[in]     The 0-based y location of point 0 on the triangle
//      x1[in]    The 0-based x location of point 1 on the triangle
//      y1[in]    The 0-based y location of point 1 on the triangle
//      x2[in]    The 0-based x location of point 2 on the triangle
//      y2[in]    The 0-based y location of point 2 on the triangle
//      color[in] The RGB565 color to use when drawing the pixel
//			filled    True or false
// ======================================================================================
void ra8875_draw_triangle (unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, unsigned int color, char filled)
{
	// Set active window X
	writeReg(RA8875_HSAW0, 0);
	writeReg(RA8875_HSAW1, 0);
	writeReg(RA8875_HEAW0, 0x1F);
	writeReg(RA8875_HEAW1, 0x03);
	
	// Set active window Y
	writeReg(RA8875_VSAW0, 0);
	writeReg(RA8875_VSAW1, 0);  
	writeReg(RA8875_VEAW0, 0xDF);
	writeReg(RA8875_VEAW1, 0x01);
		
	writeReg (RA8875_CURH0, 0);
	writeReg (RA8875_CURH1, 0);
	writeReg (RA8875_CURV0, 0);
	writeReg (RA8875_CURV1, 0); 
	
	/* Set Point 0 */
	writeReg(0x91, (unsigned char)x0);
	writeReg(0x92, (unsigned char)(x0 >> 8));
	writeReg(0x93, (unsigned char)y0);
	writeReg(0x94, (unsigned char)(y0 >> 8));
	
	/* Set Point 1 */
	writeReg(0x95, (unsigned char)x1);
	writeReg(0x96, (unsigned char)(x1 >> 8));
	writeReg(0x97, (unsigned char)y1);
	writeReg(0x98, (unsigned char)(y1 >> 8));
	
	/* Set Point 2 */
	writeReg(0xA9, (unsigned char)x2);
	writeReg(0xAA, (unsigned char)(x2 >> 8));
	writeReg(0xAB, (unsigned char)y2);
	writeReg(0xAC, (unsigned char)(y2 >> 8));
	
	/* Set Color */
	writeReg(RA8875_FGCR0,  color >> 11); // red bits
	writeReg(RA8875_FGCR1, (color & 0x7E0) >> 5);  // green bits
	writeReg(RA8875_FGCR2,  color & 0x1F); // blue bits
	
	/* Draw! */
	if (filled) writeReg(RA8875_DCR, 0xA1); else writeReg(RA8875_DCR, 0x81);
	
	/* Wait for the command to finish */
	while (DISPLAY_BUSY_STATUS == RA8875_BUSY) {};
}




// ======================================================================================
// PWM1 OUT
// ======================================================================================
void ra8875_pwm1_out(unsigned char p)
{
	writeReg(RA8875_P1DCR, p);
	
	delay_ms (10000);
}


// ======================================================================================
// PWM1 config
// ======================================================================================
void ra8875_pwm1_config (char on, unsigned char clock)
{
  if (on) writeReg(RA8875_P1CR, RA8875_P1CR_ENABLE | (clock & 0xF)); else writeReg(RA8875_P1CR, RA8875_P1CR_DISABLE | (clock & 0xF));
}

// ======================================================================================
// PWM2 config
// ======================================================================================
/*
void ra8875_pwm2_config (char on, unsigned char clock)
{
  if (on) writeReg(RA8875_P2CR, RA8875_P2CR_ENABLE | (clock & 0xF)); else writeReg(RA8875_P2CR, RA8875_P2CR_DISABLE | (clock & 0xF));
}
*/



// ======================================================================================
// LOW LEVEL FUNCTIONS
// ======================================================================================

void writeReg_slow (unsigned char reg, unsigned char val) 
{
	while (DISPLAY_BUSY_STATUS == RA8875_BUSY) {}
	
	CS_LCD_LOW;
	delay_ms (10);
	
	SPI1BUF = RA8875_CMDWRITE;
	while (SPI1STATbits.SPITBF == 1) {}
	
	delay_ms (10);
	
	SPI1BUF = reg;
	while (SPI1STATbits.SPITBF == 1) {}
		
	delay_ms (10);
	
	CS_LCD_HIGH;
	Nop ();
	delay_ms (10);
	CS_LCD_LOW;		
	Nop ();
		
	SPI1BUF = RA8875_DATAWRITE;
	while (SPI1STATbits.SPITBF == 1) {}
	
	delay_ms (10);
	
	SPI1BUF = val;
	while (SPI1STATbits.SPITBF == 1) {}
		
	delay_ms (10);
	
	CS_LCD_HIGH;
	delay_ms (10);
}

void writeReg (unsigned char reg, unsigned char val) 
{
	while (DISPLAY_BUSY_STATUS == RA8875_BUSY) {}
	
	CS_LCD_LOW;
	delay_ms (1);
	
	SPI1BUF = RA8875_CMDWRITE;
	while (SPI1STATbits.SPITBF == 1) {}
	
	delay_ms (1);
	
	SPI1BUF = reg;
	while (SPI1STATbits.SPITBF == 1) {}
		
	delay_ms (1);
	
	CS_LCD_HIGH;
	Nop ();
	delay_ms (1);
	CS_LCD_LOW;		
	Nop ();
		
	SPI1BUF = RA8875_DATAWRITE;
	while (SPI1STATbits.SPITBF == 1) {}
	
	delay_ms (1);
	
	SPI1BUF = val;
	while (SPI1STATbits.SPITBF == 1) {}
		
	delay_ms (1);
	
	CS_LCD_HIGH;
	delay_ms (1);
}



void writeData (unsigned char d) 
{
	while (DISPLAY_BUSY_STATUS == RA8875_BUSY) {};
	
	delay_ms (5);
	Nop ();
	delay_ms (5);
	
	SPI1BUF = RA8875_DATAWRITE;
	while (SPI1STATbits.SPITBF == 1) {}
	
	delay_ms (5);
	
	SPI1BUF = d;
	while (SPI1STATbits.SPITBF == 1) {}
		
	delay_ms (5);
	CS_LCD_HIGH;
	delay_ms (5);
}


void writeCommand (unsigned char d) 
{
	while (DISPLAY_BUSY_STATUS == RA8875_BUSY) {}
	
	delay_ms (5);
	CS_LCD_LOW;
	delay_ms (5);
	
	SPI1BUF = RA8875_CMDWRITE;
	while (SPI1STATbits.SPITBF == 1) {}
	
	delay_ms (5);
	
	SPI1BUF = d;
	while (SPI1STATbits.SPITBF == 1) {}
		
	delay_ms (5);
	CS_LCD_HIGH;
	delay_ms (5);
}


