// Written by MAX (Created 06 Mar, 2022)

// Funtions:    Quality-Of-Life Functions

//--------------------------------------------------------//

#include "QOL_Func.h"
#include "../../IncludeLists.h"

// Easy Serial Write
void Serial_println(){
    Serial_print("\n");
}
void Serial_print(const char* msg){
    Serial_M->write(msg,strlen(msg));
}
void Serial_println(const char* msg){
    Serial_print(msg);
    Serial_print("\n");
}
void Serial_print(string msg){
    char msg_char_array[msg.length()+1];
    strcpy(msg_char_array, msg.c_str());
    Serial_print(msg_char_array);
}
void Serial_println(string msg){
    Serial_print(msg.append("\n"));
}
void Serial_print(int msg){
    Serial_print(to_string(msg).c_str());
}
void Serial_println(int msg){
    Serial_println(to_string(msg).c_str());
}
void Serial_print(uint16_t msg){
    Serial_print(to_string((long)msg).c_str());
}
void Serial_println(uint16_t msg){
    Serial_println(to_string((long)msg).c_str());
}
void Serial_print(uint32_t msg){
    Serial_print(to_string((long)msg).c_str());
}
void Serial_println(uint32_t msg){
    Serial_println(to_string((long)msg).c_str());
}
void Serial_print(float msg){
    int temp = (int)((msg-(int)msg)*100000000);
    string temps = to_string(temp);
    temps.insert(0,8-temps.length(),'0');
    Serial_print(to_string((int)msg).c_str());
    Serial_print(".");
    Serial_print(temps.c_str());
}
void Serial_println(float msg){
    int temp = (int)((msg-(int)msg)*100000000);
    string temps = to_string(temp);
    temps.insert(0,8-temps.length(),'0');
    Serial_print(to_string((int)msg).c_str());
    Serial_print(".");
    Serial_println(temps.c_str());
}

// Easy Wait
void wait_ms(uint16_t ms){
    wait_us(ms*1000);
}
void wait_s(uint16_t s){
    wait_ms(s*1000);
}

// Easy Angle <=> Radian
float angle_to_radian(float angle){
    return angle*PI_M/180.0;
}
float radian_to_angle(float radian){
    float temp_angle = radian*180.0/PI_M;
    if (temp_angle < 0.0) {
        temp_angle += 360.0;
    }
    return temp_angle;
}