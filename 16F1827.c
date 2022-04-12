#include"16F1827_I2C.h"
#define state1 0b00001001//receive complite and startbit detected last was address
#define state2 0b00101001//receive complite and startbit detected last was data

#define _XTAL_FREQ 16000000
unsigned char state;
uint8_t value;

void i2c_slave_init(){
    SSP2CON1=0b00100110;
    SSP2CON2=0b00000001;
    SSP2ADD=4<<1;
    SSP2STAT=0b10000000;
    SSP2IF=0;//clear mssp interrupt flag
    SSP2IE=1;//enable i2c interrupt
    PEIE=1;//enable periferal interrupt
    GIE=1;//enabke global iterrupt
    SSP2CON3=0x00;
    SSP2MSK = 0b11111110 ; 
}

void i2c_state(){
    state=SSP2STAT;
    state=(state&0b00101101);
    
    switch(state){
        case state1://address detected
            value=SSP2BUF;
            RB4=1;
            if(SSP2CON1bits.SSPOV)
                SSP2CON1bits.SSPOV=0;
            if(SSP2CON2bits.SEN)
                SSP2CON1bits.CKP=1;
            break;
        case state2:
            value=SSP2BUF;
            i2c_receive_callback(value);
            if(SSP2CON2bits.SEN)
                SSP2CON1bits.CKP=1;//release sclline
            break;
            
    }
}
void __interrupt()_isr(){
    if(SSP2IF){
        RB4=1;
        SSP2IF=0;//clear interrupt flag
        i2c_state();
    }
}
