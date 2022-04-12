//#ifndef XC_HEADER_TAMPLATE_H
//#define XC_HEADER_TAMPLATE_H
#include <pic16f1827.h>
#include <stdint.h>
#include "16F1827_I2C.h"
#define state1 0b00001001//receive complite and startbit detected last was address
#define state2 0b00101001//receive complite and startbit detected last was data

uint16_t duty=0;
uint16_t d3=0,d4=0;
unsigned int a;
unsigned int b;
//pic datasheet p281

void i2c_receive_callback(uint16_t data){
    
    //CCPRxL=4*(PRx)*dutycicle  
    a=(data>>7)&0b1;
   
    if(a){
        data=(~data)+0b1;
        duty=((float)data/127)*4*256;
        CCPR3L=(duty&0b1111111100)>>2;
        CCPR4L=0x00;
        //d3=(duty&0b1111111100)>>2;
        //d4=0x00;
    }
    else{
        duty=((float)data/127)*4*256;
        CCPR3L=0x00;
        CCPR4L=(duty&0b1111111100)>>2;
        //d3=0x00;
        //d4=(duty&0b1111111100)>>2;
    }
}

void main(){
    OSCCONbits.IRCF=0b1110;//8MH
    OSCCONbits.SCS=0b11;;//use internal oscillator as system clock
    
    
    TRISB=0b00100100;// RB2,RB5 i2c input pin
    TRISA=0x00;
    ANSELA=0x00;
    ANSELB=0x00;
    RB4=0;
    
    //pwm setting
    CCP3CON=0b00001100;
    CCP4CON=0b00001100;
    CCPTMRS=0b00010000;// ccp3 use timer4, ccp4 use timer2
    T2CON=0b00000100;// timer2 on and prescaler is 16
    T4CON=0b00000100;// timer4 on and prescaler is 16
    PR2=255;//pwm period is 0.001s  pwm frequency is 976Hz
    PR4=255;
  
    i2c_slave_init();
    
    
    while(1){
        ;
    }
   
}









