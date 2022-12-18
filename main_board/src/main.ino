#include<Wire.h>
#define MD1 5

void i2c_write(int8_t addr,int8_t data){
    //data min:-128 max:127; 
    if(data<0){ 
        uint8_t num; 
        num=~abs(data);
        data=num+0b1;
    }
    Wire.beginTransmission(addr);
    Wire.write(data);
    Serial.println(Wire.endTransmission());
}


void setup(){
    Serial.begin(9600);
    Wire.begin();
    GPIOB->PUPDR|=(1<<16);
    GPIOB->PUPDR|=(1<<18);
}
void loop(){
    i2c_write(MD1,120);//MD1はduty比 120/127 で稼働
}
