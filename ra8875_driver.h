#ifndef RA8875_H
#define RA8875_H

// ===========================================
// Command/Data pins for SPI
// ===========================================
#define RA8875_DATAWRITE        0x00
#define RA8875_DATAREAD         0x40
#define RA8875_CMDWRITE         0x80
#define RA8875_CMDREAD          0xC0


// ===========================================
// Colors (RGB565)
// ===========================================
#define	RA8875_BLACK            0x0000
#define	RA8875_BLUE             0x001F
#define	RA8875_RED              0xF800
#define	RA8875_GREEN            0x07E0
#define RA8875_CYAN             0x07FF
#define RA8875_MAGENTA          0xF81F
#define RA8875_YELLOW           0xFFE0  
#define RA8875_WHITE            0xFFFF

// ===========================================
// REGISTERS AND MASKS
// ===========================================
#define RA8875_STSR             0x00 // Status register [0x00]

#define RA8875_PWRR             0x01 // Power and Display Control Register
#define RA8875_PWRR_DISPON      0x80
#define RA8875_PWRR_DISPOFF     0x00
#define RA8875_PWRR_SLEEP       0x02
#define RA8875_PWRR_NORMAL      0x00
#define RA8875_PWRR_SOFTRESET   0x01

#define RA8875_MRWC             0x02 // Memory Read/Write Command

#define RA8875_PCSR             0x04 // Pixel Clock Setting Register
#define RA8875_PCSR_PDATR       0x00
#define RA8875_PCSR_PDATL       0x80
#define RA8875_PCSR_CLK         0x00
#define RA8875_PCSR_2CLK        0x01
#define RA8875_PCSR_4CLK        0x02
#define RA8875_PCSR_8CLK        0x03

#define RA8875_SROC             0x05 // Serial Flash/ROM Configuration Register

#define RA8875_SFCLR            0x06 // Serial Flash/ROM CLK Setting Register

#define RA8875_SYSR             0x10 // System Configuration Register
#define RA8875_SYSR_8BPP        0x00
#define RA8875_SYSR_16BPP       0x0C
#define RA8875_SYSR_MCU8        0x00
#define RA8875_SYSR_MCU16       0x03

#define RA8875_GPI              0x12 // General Purpose Input

#define RA8875_GPO              0x13 // General Purpose Output

#define RA8875_HDWR             0x14 // LCD Horizontal Display Width Register

#define RA8875_HNDFTR           0x15 // Horizontal Non-Display Period Fine Tuning Option Register
#define RA8875_HNDFTR_DE_HIGH   0x00
#define RA8875_HNDFTR_DE_LOW    0x80

#define RA8875_HNDR             0x16 //LCD Horizontal Non-Display Period Register

#define RA8875_HSTR             0x17 // HSYNC Start Position Register

#define RA8875_HPWR             0x18 // HSYNC Pulse Width Register
#define RA8875_HPWR_LOW         0x00
#define RA8875_HPWR_HIGH        0x80

#define RA8875_VDHR0            0x19 // LCD Vertical Display Height Register 0
#define RA8875_VDHR1            0x1A // LCD Vertical Display Height Register 1

#define RA8875_VNDR0            0x1B // LCD Vertical Non-Display Period Register 0
#define RA8875_VNDR1            0x1C // LCD Vertical Non-Display Period Register 1

#define RA8875_VSTR0            0x1D // VSYNC Start Position Register 0
#define RA8875_VSTR1            0x1E // VSYNC Start Position Register 0

#define RA8875_VPWR             0x1F // VSYNC Pulse Width Register

#define RA8875_DPCR             0x20 // Display Configuration Register

#define RA8875_FNCR0            0x21 // Font Control Register 0
#define RA8875_FNCR1            0x22 // Font Control Register 1

#define RA8875_CGSR             0x23 // CGRAM Select Register

#define RA8875_HOFS0            0x24 // Horizontal Scroll Offset Register 0
#define RA8875_HOFS1            0x25 // Horizontal Scroll Offset Register 1

#define RA8875_VOFS0            0x26 // Vertical Scroll Offset Register 0
#define RA8875_VOFS1            0x27 // Vertical Scroll Offset Register 1

#define RA8875_FLDR             0x29 // Font Line Distance Setting Register

#define RA8875_F_CURXL          0x2A // Font Write Cursor Horizontal Position Register LOW
#define RA8875_F_CURXH          0x2B // Font Write Cursor Horizontal Position Register HIGH

#define RA8875_F_CURYL          0x2C // Font Write Cursor Vertical Position Register LOW
#define RA8875_F_CURYH          0x2D // Font Write Cursor Vertical Position Register HIGH

#define RA8875_FWR              0x2E // Font Write Type Setting Register

#define RA8875_SFRS             0x2F // Serial Font ROM Setting

#define RA8875_HSAW0            0x30 // Horizontal Start Point of Active Window Register 0
#define RA8875_HSAW1            0x31 // Horizontal Start Point of Active Window Register 1

#define RA8875_VSAW0            0x32 // Vertical Start Point of Active Window Register 0
#define RA8875_VSAW1            0x33 // Vertical Start Point of Active Window Register 1

#define RA8875_HEAW0            0x34 // Horizontal End Point of Active Window Register 0
#define RA8875_HEAW1            0x35 // Horizontal End Point of Active Window Register 1

#define RA8875_VEAW0            0x36 // Vertical End Point of Active Window Register 0
#define RA8875_VEAW1            0x37 // Vertical End Point of Active Window Register 1

#define RA8875_HSSW0            0x38 // Horizontal Start Point of Scroll Window Register 0
#define RA8875_HSSW1            0x39 // Horizontal Start Point of Scroll Window Register 1

#define RA8875_VSSW0            0x3A // Vertical Start Point of Scroll Window Register 0
#define RA8875_VSSW1            0x3B // Vertical Start Point of Scroll Window Register 1

#define RA8875_HESW0            0x3C // Horizontal End Point of Scroll Window Register 0
#define RA8875_HESW1            0x3D // Horizontal End Point of Scroll Window Register 1

#define RA8875_VESW0            0x3E // Vertical End Point of Scroll Window Register 0
#define RA8875_VESW1            0x3F // Vertical End Point of Scroll Window Register 1

#define RA8875_MWCR0            0x40 // Memory Write Control Register 0
#define RA8875_MWCR0_GFXMODE    0x00
#define RA8875_MWCR0_TXTMODE    0x80

#define RA8875_MWCR1            0x41 // Memory Write Control Register 1

#define RA8875_BTCR             0x44 // Blink Time Control Register

#define RA8875_MCRD             0x45 // Memory Read Cursor Direction

#define RA8875_CURH0            0x46 // Memory Write Cursor Horizontal Position Register 0
#define RA8875_CURH1            0x47 // Memory Write Cursor Horizontal Position Register 1

#define RA8875_CURV0            0x48 // Memory Write Cursor Vertical Position Register 0
#define RA8875_CURV1            0x49 // Memory Write Cursor Vertical Position Register 1

#define RA8875_RCURH0           0x4A // Memory Read Cursor Horizontal Position Register 0
#define RA8875_RCURH1           0x4B // Memory Read Cursor Horizontal Position Register 1

#define RA8875_RCURV0           0x4C // Memory Read Cursor Vertical Position Register 0
#define RA8875_RCURV1           0x4D // Memory Read Cursor Vertical Position Register 1

#define RA8875_CURHS            0x4E // Font Write Cursor and Memory Write Cursor Horizontal Size Register
#define RA8875_CURVS            0x4F // Font Write Cursor Vertical Size Register

#define RA8875_BECR0            0x50 // BTE Function Control Register 0
#define RA8875_BECR1            0x51 // BTE Function Control Register 1

#define RA8875_LTPR0            0x52 // Layer Transparency Register 0
#define RA8875_LTPR1            0x53 // Layer Transparency Register 1

#define RA8875_HSBE0            0x54 // Horizontal Source Point of BTE Register 0
#define RA8875_HSBE1            0x55 // Horizontal Source Point of BTE Register 1

#define RA8875_VSBE0            0x56 // Vertical Source Point of BTE Register 0
#define RA8875_VSBE1            0x57 // Vertical Source Point of BTE Register 1

#define RA8875_HDBE0            0x58 // Horizontal Destination Point of BTE Register 0
#define RA8875_HDBE1            0x59 // Horizontal Destination Point of BTE Register 1

#define RA8875_VDBE0            0x5A // Vertical Destination Point of BTE Register 0
#define RA8875_VDBE1            0x5B // Vertical Destination Point of BTE Register 1

#define RA8875_BEWR0            0x5C // BTE Width Register 0
#define RA8875_BEWR1            0x5D // BTE Width Register 1

#define RA8875_BEHR0            0x5E // BTE Height Register 0
#define RA8875_BEHR1            0x5F // BTE Height Register 1

#define RA8875_BGCR0            0x60 // Background Color Register 0
#define RA8875_BGCR1            0x61 // Background Color Register 1
#define RA8875_BGCR2            0x62 // Background Color Register 2

#define RA8875_FGCR0            0x63 // Foreground Color Register 0
#define RA8875_FGCR1            0x64 // Foreground Color Register 1
#define RA8875_FGCR2            0x65 // Foreground Color Register 2















#define RA8875_GPIOX            0xC7

#define RA8875_PLLC1            0x88
#define RA8875_PLLC1_PLLDIV2    0x80
#define RA8875_PLLC1_PLLDIV1    0x00

#define RA8875_PLLC2            0x89
#define RA8875_PLLC2_DIV1       0x00
#define RA8875_PLLC2_DIV2       0x01
#define RA8875_PLLC2_DIV4       0x02
#define RA8875_PLLC2_DIV8       0x03
#define RA8875_PLLC2_DIV16      0x04
#define RA8875_PLLC2_DIV32      0x05
#define RA8875_PLLC2_DIV64      0x06
#define RA8875_PLLC2_DIV128     0x07











#define RA8875_VPWR_LOW         0x00
#define RA8875_VPWR_HIGH        0x80





#define RA8875_MCLR             0x8E
#define RA8875_MCLR_START       0x80
#define RA8875_MCLR_STOP        0x00
#define RA8875_MCLR_READSTATUS  0x80
#define RA8875_MCLR_FULL        0x00
#define RA8875_MCLR_ACTIVE      0x40

#define RA8875_DCR                    0x90
#define RA8875_DCR_LINESQUTRI_START   0x80
#define RA8875_DCR_LINESQUTRI_STOP    0x00
#define RA8875_DCR_LINESQUTRI_STATUS  0x80
#define RA8875_DCR_CIRCLE_START       0x40
#define RA8875_DCR_CIRCLE_STATUS      0x40
#define RA8875_DCR_CIRCLE_STOP        0x00
#define RA8875_DCR_FILL               0x20
#define RA8875_DCR_NOFILL             0x00
#define RA8875_DCR_DRAWLINE           0x00
#define RA8875_DCR_DRAWTRIANGLE       0x01
#define RA8875_DCR_DRAWSQUARE         0x10


#define RA8875_ELLIPSE                0xA0 // Draw Ellipse, Ellipse Curve, Circle Square Control Register
#define RA8875_ELLIPSE_STATUS         0x80





#define RA8875_P1CR             0x8A
#define RA8875_P1CR_ENABLE      0x80
#define RA8875_P1CR_DISABLE     0x00
#define RA8875_P1CR_CLKOUT      0x10
#define RA8875_P1CR_PWMOUT      0x00

#define RA8875_P1DCR            0x8B

#define RA8875_P2CR             0x8C
#define RA8875_P2CR_ENABLE      0x80
#define RA8875_P2CR_DISABLE     0x00
#define RA8875_P2CR_CLKOUT      0x10
#define RA8875_P2CR_PWMOUT      0x00

#define RA8875_P2DCR            0x8D

#define RA8875_PWM_CLK_DIV1     0x00
#define RA8875_PWM_CLK_DIV2     0x01
#define RA8875_PWM_CLK_DIV4     0x02
#define RA8875_PWM_CLK_DIV8     0x03
#define RA8875_PWM_CLK_DIV16    0x04
#define RA8875_PWM_CLK_DIV32    0x05
#define RA8875_PWM_CLK_DIV64    0x06
#define RA8875_PWM_CLK_DIV128   0x07
#define RA8875_PWM_CLK_DIV256   0x08
#define RA8875_PWM_CLK_DIV512   0x09
#define RA8875_PWM_CLK_DIV1024  0x0A
#define RA8875_PWM_CLK_DIV2048  0x0B
#define RA8875_PWM_CLK_DIV4096  0x0C
#define RA8875_PWM_CLK_DIV8192  0x0D
#define RA8875_PWM_CLK_DIV16384 0x0E
#define RA8875_PWM_CLK_DIV32768 0x0F

#define RA8875_TPCR0                  0x70
#define RA8875_TPCR0_ENABLE           0x80
#define RA8875_TPCR0_DISABLE          0x00
#define RA8875_TPCR0_WAIT_512CLK      0x00
#define RA8875_TPCR0_WAIT_1024CLK     0x10
#define RA8875_TPCR0_WAIT_2048CLK     0x20
#define RA8875_TPCR0_WAIT_4096CLK     0x30
#define RA8875_TPCR0_WAIT_8192CLK     0x40
#define RA8875_TPCR0_WAIT_16384CLK    0x50
#define RA8875_TPCR0_WAIT_32768CLK    0x60
#define RA8875_TPCR0_WAIT_65536CLK    0x70
#define RA8875_TPCR0_WAKEENABLE       0x08
#define RA8875_TPCR0_WAKEDISABLE      0x00
#define RA8875_TPCR0_ADCCLK_DIV1      0x00
#define RA8875_TPCR0_ADCCLK_DIV2      0x01
#define RA8875_TPCR0_ADCCLK_DIV4      0x02
#define RA8875_TPCR0_ADCCLK_DIV8      0x03
#define RA8875_TPCR0_ADCCLK_DIV16     0x04
#define RA8875_TPCR0_ADCCLK_DIV32     0x05
#define RA8875_TPCR0_ADCCLK_DIV64     0x06
#define RA8875_TPCR0_ADCCLK_DIV128    0x07

#define RA8875_TPCR1            0x71
#define RA8875_TPCR1_AUTO       0x00
#define RA8875_TPCR1_MANUAL     0x40
#define RA8875_TPCR1_VREFINT    0x00
#define RA8875_TPCR1_VREFEXT    0x20
#define RA8875_TPCR1_DEBOUNCE   0x04
#define RA8875_TPCR1_NODEBOUNCE 0x00
#define RA8875_TPCR1_IDLE       0x00
#define RA8875_TPCR1_WAIT       0x01
#define RA8875_TPCR1_LATCHX     0x02
#define RA8875_TPCR1_LATCHY     0x03

#define RA8875_TPXH             0x72
#define RA8875_TPYH             0x73
#define RA8875_TPXYL            0x74

#define RA8875_INTC1            0xF0
#define RA8875_INTC1_KEY        0x10
#define RA8875_INTC1_DMA        0x08
#define RA8875_INTC1_TP         0x04
#define RA8875_INTC1_BTE        0x02

#define RA8875_INTC2            0xF1
#define RA8875_INTC2_KEY        0x10
#define RA8875_INTC2_DMA        0x08
#define RA8875_INTC2_TP         0x04
#define RA8875_INTC2_BTE        0x02


#define TRUE 1
#define FALSE 0


#define COLOR_BLACK        0x0000      /*   0,   0,   0 */
#define COLOR_NAVY         0x000F      /*   0,   0, 128 */
#define COLOR_DARK_GREEN   0x03E0      /*   0, 128,   0 */
#define COLOR_DARK_CYAN    0x03EF      /*   0, 128, 128 */
#define COLOR_DARK_GRAY    0x4208      /*  64,  64,  64 */
#define COLOR_MAROON       0x7800      /* 128,   0,   0 */
#define COLOR_PURPLE       0x780F      /* 128,   0, 128 */
#define COLOR_OLIVE        0x7BE0      /* 128, 128,   0 */
#define COLOR_LIGHT_GRAY   0xC618      /* 192, 192, 192 */
#define COLOR_GRAY         0x7BEF      /* 128, 128, 128 */
#define COLOR_BLUE         0x001F      /*   0,   0, 255 */
#define COLOR_GREEN        0x07E0      /*   0, 255,   0 */
#define COLOR_CYAN         0x07FF      /*   0, 255, 255 */
#define COLOR_RED          0xF800      /* 255,   0,   0 */
#define COLOR_MAGENTA      0xF81F      /* 255,   0, 255 */
#define COLOR_YELLOW       0xFFE0      /* 255, 255,   0 */
#define COLOR_WHITE        0xFFFF      /* 255, 255, 255 */
#define COLOR_ORANGE       0xFD20      /* 255, 165,   0 */
#define COLOR_GREEN_YELLOW 0xAFE5      /* 173, 255,  47 */
#define COLOR_PINK         0xF81F

#define RGB16(r,g,b) ((b >> 3)|((g >> 2) << 5)|((r >> 3)<< 11))

void ra8875_init       (void);
void ra8875_soft_reset (void);
void ra8875_display_on (char on);
void ra8875_sleep      (char sleep);

/* Graphics functions */
void ra8875_set_xy_position    (unsigned int x, unsigned int y);
void ra8875_draw_line          (unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1, unsigned int color);
void ra8875_draw_circle		   (unsigned int x0, unsigned int y0, unsigned int r, unsigned int color, char filled);
void ra8875_draw_circle_sqr    (unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1, unsigned char r, unsigned int color, char filled);
void ra8875_draw_rectangle     (unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1, unsigned int color, char filled);
void ra8875_draw_rectangle_bte (unsigned int x, unsigned int y, unsigned int width, unsigned int height, unsigned int color);

void ra8875_draw_triangle      (unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, unsigned int color, char filled);
//void ra8875_draw_ellipse       (unsigned int xCenter, unsigned int yCenter, unsigned int longAxis, unsigned int shortAxis, unsigned char color, char filled);
//void ra8875_draw_curve         (unsigned int xCenter, unsigned int yCenter, unsigned int longAxis, unsigned int shortAxis, unsigned char curvePart, unsigned char color, char filled);


/* Backlight */
//void ra8875_gpiox       (char on);
void ra8875_pwm1_config (char on, unsigned char clock);
//void ra8875_pwm2_config (char on, unsigned char clock);
void ra8875_pwm1_out    (unsigned char p);
//void ra8875_pwm2_out    (unsigned char p);


/* Low level access */
void writeReg(unsigned char reg, unsigned char val);
void writeReg_slow(unsigned char reg, unsigned char val);

//unsigned char readReg(unsigned char reg);
void    writeData(unsigned char d);
//unsigned char readData(void);
void    writeCommand(unsigned char d);
//unsigned char readStatus(void);





#endif
