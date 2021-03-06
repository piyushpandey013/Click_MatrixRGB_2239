#include "matrixrgb_hw.h"
#include "resources.h"

sbit MATRIXRGB_CS       at GPIOD_ODR.B13;
sbit MATRIXRGB_READY    at GPIOD_IDR.B10;
sbit MATRIXRGB_RST      at GPIOC_ODR.B2;

void system_setup( uint8_t width, uint8_t height );

void main()
{
    uint16_t count = 0;
    uint8_t i     = 0;
    color_t my_color;

    system_setup( 2, 2 );

    matrixrgb_scroll_img_left( MikroE_Sign_bmp, 32, 32, 25 );
    matrixrgb_scroll_off_scrn_down( 25 );
    matrixrgb_set_color( &my_color, 1, 1, 1 );
    matrixrgb_scroll_text_right( "Matrix ", my_color, 17, 10 );
    matrixrgb_set_color( &my_color, 1, 0, 0 );
    matrixrgb_scroll_text_left( "R", my_color, 17, 1 );
    matrixrgb_set_color( &my_color, 0, 1, 0 );
    matrixrgb_scroll_text_left( "G", my_color, 17, 1 );
    matrixrgb_set_color( &my_color, 0, 0, 1 );
    matrixrgb_scroll_text_left( "B ", my_color, 17, 1 );
    matrixrgb_set_color( &my_color, 1, 1, 1 );
    matrixrgb_scroll_off_scrn_up( 30 );
    matrixrgb_set_color( &my_color, 1, 0, 0 );
    matrixrgb_scroll_text_left( "By: ", my_color, 17, 4 );
    matrixrgb_set_color( &my_color, 1, 1, 1 );
    matrixrgb_scroll_text_left( "Corey ", my_color, 17, 6 );
    matrixrgb_set_color( &my_color, 0, 0, 1 );
    matrixrgb_scroll_text_left( "Lakey ", my_color, 17, 6 );
    matrixrgb_scroll_off_scrn_left( 17 );
    matrixrgb_scroll_img_right( MikroeBITMAP_bmp, 64, 16, 25 );
    matrixrgb_scroll_off_scrn_right( 10 );

    while(1)
    {
      /* matrixrgb_refresh();
       count++;
       if( count >= 200 )
       {
           count = 0;
           matrixrgb_shift_down();
       }  */
        matrixrgb_set_color( &my_color, 1, 1, 1 );
        matrixrgb_scroll_text_left( "Matrix", my_color, 10, 10 );
        matrixrgb_set_color( &my_color, 1, 0, 0 );
        matrixrgb_scroll_text_left( "R", my_color, 10, 1 );
        matrixrgb_set_color( &my_color, 0, 1, 0 );
        matrixrgb_scroll_text_left( "G", my_color, 10, 1 );
        matrixrgb_set_color( &my_color, 0, 0, 1 );
        matrixrgb_scroll_text_left( "B", my_color, 10, 1 );
    }
}

void system_setup( uint8_t width, uint8_t height )
{
    
    GPIO_Digital_Output( &GPIOD_BASE, _GPIO_PINMASK_13); // Set Chip Select pin as output
    GPIO_Digital_Output( &GPIOC_BASE, _GPIO_PINMASK_2 ); // Set Reset pin to output
    GPIO_Digital_Input( &GPIOD_BASE, _GPIO_PINMASK_10);  // Set Ready to input

    // Initialize SPI
    SPI3_Init_Advanced(_SPI_FPCLK_DIV2, _SPI_MASTER | _SPI_8_BIT |
                       _SPI_CLK_IDLE_LOW | _SPI_FIRST_CLK_EDGE_TRANSITION |
                       _SPI_MSB_FIRST | _SPI_SS_DISABLE | _SPI_SSM_DISABLE | _SPI_SSI_1,
                       &_GPIO_MODULE_SPI3_PC10_11_12);

    MATRIXRGB_RST = 0;        //Reset slave ( toggle )
    Delay_ms(20);
    MATRIXRGB_RST = 1;
    Delay_ms(200);

    matrixrgb_init( width, height );
    Delay_ms(200);

}