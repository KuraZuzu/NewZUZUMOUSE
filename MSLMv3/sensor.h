#ifndef SENSOR_H
#define SENSOR_H
#include "deftype.h"

class DistanceSensor{
    private:
        AnalogIn _analog_value;
    public:
        DistanceSensor( PinName );
        int get_val();

        operator int (){
            return get_val();
        }
};

class gp2y_i2c{
    private:
        I2C i2c;
        char cmd[2];
        char Distance_adrs[2];
        char i2c_read(int,char);

    public:
        gp2y_i2c(PinName, PinName);
        gp2y_i2c(PinName, PinName, int);
        void set_frequency(int);
        int distance(char);
};

class RotaryEncoder{
    private:

        unsigned int data;
        unsigned int angle;
        unsigned int status;

        long int integra_val;
        int error;
        int speed_cnt;
        int speed_val;
        int speed_temp_val;

        bool _cwccw;

        unsigned int temp_angle;
        SPI *encoder;

        int ans;
        int temp_cal;
        int over_temp_cal;
        int diff;
        int diff_error[300];


    public:
        RotaryEncoder(PinName mosi,PinName miso,PinName clock,bool cwccw)
        {
            encoder = new SPI(mosi,miso,clock);
            encoder->format( 16,2 );
            encoder->frequency(500000);
            speed_val=speed_cnt=temp_angle=0;
            error=0x00;
            _cwccw = cwccw;
        }

        ~RotaryEncoder()
        {
            delete encoder;
        }


        void Reset(){
            integra_val = 0;
        }

        int Error( int return_mode=0, int i=0 ){
            switch(return_mode){
                case 1:
                    return diff_error[i];

                default:
                    return error;
            }

        }

        int Status(){
            return status;
        }

        int Angle(){
            int val = angle;
            val = (double)val*0.351;
            return val;
        }

        int Speed(bool mode=false){
            if(mode){
                if( speed_cnt >= 50 ){
                    speed_val = speed_temp_val;
                    speed_temp_val=speed_cnt=0;
                }else speed_temp_val+= diff;
                speed_cnt++;
            }else{
                if( _cwccw )return speed_val;
                else return -speed_val;
            }
            return false;
        }

        long int Integration_Value(){
            long int val = integra_val;
            val = integra_val;
            if( _cwccw )return val;
            else return -val;
        }


        void encoder_calc(){
            int temp_cal;
            data = encoder->write(0x00);
            angle = (data >> 5) & 0x3ff;
            status = data & 0x1f;

            temp_cal = (int)(angle - temp_angle);

            if( temp_cal == 0 ){
                error=0x00;
                diff = 0;
            }else{
                diff = integra_val;
                if( temp_cal == 1 || temp_cal == 1023 ){
                    integra_val++;

                }else if( temp_cal == -1 || temp_cal == -1023 ){
                    integra_val--;

                }else if( temp_cal <= 30 && temp_cal > 1 ){
                    integra_val += temp_cal;

                }else if( temp_cal >= -30 && temp_cal < -1 ){
                    integra_val += temp_cal;

                }else if( temp_cal > 1000 ){
                    integra_val += angle-1023-temp_angle;

                }else if( temp_cal < -1000 ){
                    integra_val += 1023-temp_angle+angle;

                }else{
                    //if(error<300)diff_error[error];
                    error++;
                }
                diff = integra_val-diff;
            }

            RotaryEncoder::Speed(true);

            temp_angle = angle;
        }


};

#endif
