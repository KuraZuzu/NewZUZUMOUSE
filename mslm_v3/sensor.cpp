#include "sensor.h"
#include "mbed.h"

DistanceSensor::DistanceSensor( PinName analog_value ):_analog_value(analog_value){
	//_analog_value = 0;
}


int DistanceSensor::get_val(){
	return (((_analog_value*3.3) - 2.375)/(-0.0375))*10;
}


gp2y_i2c::gp2y_i2c(PinName sda, PinName scl):
    i2c(sda,scl)
{
    Distance_adrs[0] = 0x5E;
    Distance_adrs[1] = 0x5F;
}

gp2y_i2c::gp2y_i2c(PinName sda, PinName scl, int _frequncy):
    i2c(sda,scl)
{
    Distance_adrs[0] = 0x5E;
    Distance_adrs[1] = 0x5F;
    i2c.frequency(_frequncy);
}

char gp2y_i2c::i2c_read(int addr,char regist){
    cmd[0] = regist;
    i2c.write(addr,cmd,1);
    i2c.read(addr,cmd,1);
    return cmd[0];
}

void gp2y_i2c::set_frequency(int _val){
    i2c.frequency(_val);
}

int gp2y_i2c::distance(char adrs){
    return (int((i2c_read(adrs,Distance_adrs[0]))*16+(i2c_read(adrs,Distance_adrs[1]))/16/4));
}
