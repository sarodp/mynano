// arduino nano DIO,ADC Pins
/*
D0 = PD0(TXD)
D1 = PD1(RXD)
D2 = PD2(INT0)
D3 = PD3(INT1)
D4 = PD4
D5 = PD5
D6 = PD6
D7 = PD7

D8 = PB0
D9 = PB1
D10 = PB2(SS)
D11 = PB3(MOSI)
D12 = PB4(MISO)
D13 = PB5(SCK)

A0 = PC0(ADC0)
A1 = PC1(ADC1)
A2 = PC2(ADC2)
A3 = PC3(ADC3)
A4 = PC4(SDA)
A5 = PC5(SCL)
A6 = ADC6
A7 = ADC7
*/

#ifndef LED_BUILTIN
#define LED_BUILTIN 13
#endif

#define PD0 0   // D0    UART-TXD
#define PD1 1   // D1    UART-RX
#define PD2 2   // D2    INT0
#define PD3 3   // D3pwm INT1
#define PD4 4   // D4    I2C-SDA
#define PD5 5   // D5pwm I2C-SCL
#define PD6 6   // D6pwm          
#define PD7 7   // D7          

#define PB0 8   // D8
#define PB1 9   // D9pwm        
#define PB2 10  // D10pwm?  SPI-SS 
#define PB3 11  // D11pwm   SPI-MOSI
#define PB4 12  // D12      SPI-MISO
#define PB5 13  // D13      SPI-SCK , built-in LED

#define PC0 14    // A0 ADC0
#define PC1 15    // A1 ADC1
#define PC2 16    // A2 ADC2
#define PC3 17    // A3 ADC3
#define PC4 18    // A4 ADC4
#define PC5 19    // A5 ADC5

#define ADC6 20    // A6 ADC6  ..analog input only
#define ADC7 21    // A7 ADC7  ..analog input only
