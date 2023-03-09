#ifndef _LIGHT_SENSOR_H_
#define _LIGHT_SENSOR_H_

class LightSensor {
    private:
        int pin_sensor_in;
        int pin_status_led;
        double dphi = 0.0;
        const int LIFEMAX = 10;
        int lifecnt;
        double* mod_varphi_ptr;
    public:
        //LightSensor();
        //~LightSensor();
        void init(const double* mv_ptr, const int pin_in, const int pin_stat){
            mod_varphi_ptr = mv_ptr;
            pin_sensor_in = pin_in;
            pin_status_led = pin_stat;
            /*
            if (pin_sensor_in>0){
                attachInterrupt(pin_sensor_in, this::detect, FALLING);
            }else{
                MPLog("ERROR : invailded sensor pin");
            }*/
            if (pin_status_led>0){
                pinMode(pin_status_led, OUTPUT);
            }
        }
        bool getIsActive(){
          return lifecnt>0;
        }
        double getDphi(){
            return dphi;
        }
        int getSensorPin(){
            return pin_sensor_in;
        }
        void* getDetectHandle(){
            return (void*)&LightSensor::detect;
        }
        void update(){
            lifecnt--;
            if(lifecnt<=0){
                dphi = 0.0;
                digitalWrite(pin_status_led, LOW);
            }
        }
        void detect(){
            dphi = *mod_varphi_ptr - PI;
            digitalWrite(pin_status_led, HIGH);
            lifecnt = LIFEMAX;
            return;
        }
};

#endif
