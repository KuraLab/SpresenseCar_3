// Written by MAX (Created 06 Mar, 2023)

// Features:    Initialization code for Nucleo64

//--------------------------------------------------------//

#include "Init.h"
#include "../../IncludeLists.h"

// Init ALL Components
void Init(){
    // Components Init
    Onboard_LED_Init(LED);
    Onboard_Button_Init(Button);
    I2C_Init(I2C_SLAVE_M);
    Motor_Input_Init();
    Motor_PWM_Pin_Init(Motor_PWM);
    Motor_DIR_Pin_Init(Motor_DIR);
    // Motor_HALL_Pin_Init(Motor_HALL);
    Serial_Init(Serial_M);
    HAL_Init();     //get time with HAL_GetTick, return (uint32_t)

    // Global Variable Init
    X = 0;
    Y = 0;
    target_X = 0;
    target_Y = 0;

    // Init Finished
    Nucleo64_Init_Finished_Successfully(LED);
    Serial_println("Init finished successfully");
}

// Init the 2 onboard components, simply that
void Onboard_LED_Init(DigitalOut*& LED){
    LED = new DigitalOut(LED1);
}
void Onboard_Button_Init(DigitalIn*& Button){
    Button = new DigitalIn(BUTTON1);
    Button->mode(PullDown);
}

// Init I2C pins & I2C
void I2C_Init(I2CSlave*& I2C_SLAVE_M){
    I2C_SLAVE_M = new I2CSlave(I2C_M_SDA_PIN,I2C_M_SCL_PIN);
    I2C_SLAVE_M->frequency(400000);
    I2C_SLAVE_M->address(NUCLEO_I2C_ADDR);
}

// Init static Motor_Input object
void Motor_Input_Init(){
    Curr_Motor_Input.M1_PWM = 0.0;
    Curr_Motor_Input.M2_PWM = 0.0;
    Curr_Motor_Input.M3_PWM = 0.0;
    Curr_Motor_Input.M4_PWM = 0.0;
}

// Init the pins for Motor Control
void Motor_PWM_Pin_Init(PwmOut* motor_PWM[]){       //1x4 pins
    motor_PWM[0] = new PwmOut(M1_PWM_PIN);
    motor_PWM[1] = new PwmOut(M2_PWM_PIN);
    motor_PWM[2] = new PwmOut(M3_PWM_PIN);
    motor_PWM[3] = new PwmOut(M4_PWM_PIN);
}
void Motor_DIR_Pin_Init(DigitalOut* motor_DIR[]){   //2x4 pins
    motor_DIR[0] = new DigitalOut(M1_DIR_1_PIN);
    motor_DIR[1] = new DigitalOut(M1_DIR_2_PIN);
    motor_DIR[2] = new DigitalOut(M2_DIR_1_PIN);
    motor_DIR[3] = new DigitalOut(M2_DIR_2_PIN);
    motor_DIR[4] = new DigitalOut(M3_DIR_1_PIN);
    motor_DIR[5] = new DigitalOut(M3_DIR_2_PIN);
    motor_DIR[6] = new DigitalOut(M4_DIR_1_PIN);
    motor_DIR[7] = new DigitalOut(M4_DIR_2_PIN);
}
// void Motor_HALL_Pin_Init(InterruptIn* motor_HALL[]){//2x4 pins
    // motor_HALL[0] = new InterruptIn(M1_HALL_1_PIN, PullDown);
    // motor_HALL[0]->rise(&M1_HALL_1_handler);
    // motor_HALL[1] = new InterruptIn(M1_HALL_2_PIN, PullDown);
    // motor_HALL[1]->rise(&M1_HALL_2_handler);
    // motor_HALL[2] = new InterruptIn(M2_HALL_1_PIN, PullDown);
    // motor_HALL[2]->rise(&M2_HALL_1_handler);
    // motor_HALL[3] = new InterruptIn(M2_HALL_2_PIN, PullDown);
    // motor_HALL[3]->rise(&M2_HALL_2_handler);
    // motor_HALL[4] = new InterruptIn(M3_HALL_1_PIN, PullDown);
    // motor_HALL[4]->rise(&M3_HALL_1_handler);
    // motor_HALL[5] = new InterruptIn(M3_HALL_2_PIN, PullDown);
    // motor_HALL[5]->rise(&M3_HALL_2_handler);
    // motor_HALL[6] = new InterruptIn(M4_HALL_1_PIN, PullDown);
    // motor_HALL[6]->rise(&M4_HALL_1_handler);
    // motor_HALL[7] = new InterruptIn(M4_HALL_2_PIN, PullDown);
    // motor_HALL[7]->rise(&M4_HALL_2_handler);
// }

// Init Serial Communication
void Serial_Init(BufferedSerial*& Serial_M){
    Serial_M = new BufferedSerial(CONSOLE_TX,CONSOLE_RX);
    Serial_M->set_baud(9600);
    Serial_M->set_format(
        /* bits */ 8,
        /* parity */ BufferedSerial::None,
        /* stop bit */ 1
    );
}

//--------------------------------------------------------//

//HALL Pin Interrupt Handler
// long HALL_past_tick [2*4] = {0,0,0,0,0,0,0,0};
// void HALL_Interrupt_Time_Check(uint8_t index, long curr_tick);
// void M1_HALL_1_handler(){HALL_Interrupt_Time_Check(0,HAL_GetTick());}
// void M1_HALL_2_handler(){HALL_Interrupt_Time_Check(1,HAL_GetTick());}
// void M2_HALL_1_handler(){HALL_Interrupt_Time_Check(2,HAL_GetTick());}
// void M2_HALL_2_handler(){HALL_Interrupt_Time_Check(3,HAL_GetTick());}
// void M3_HALL_1_handler(){HALL_Interrupt_Time_Check(4,HAL_GetTick());}
// void M3_HALL_2_handler(){HALL_Interrupt_Time_Check(5,HAL_GetTick());}
// void M4_HALL_1_handler(){HALL_Interrupt_Time_Check(6,HAL_GetTick());}
// void M4_HALL_2_handler(){HALL_Interrupt_Time_Check(7,HAL_GetTick());}
// void HALL_Interrupt_Time_Check(uint8_t index, long curr_tick){
//     // if (curr_tick - HALL_past_tick[index] < HALL_UPDATE_PERIOD) {return;}
//     // HALL_past_tick[index] = curr_tick;
//     Motor_HALL_count[index] = Motor_HALL_count[index] + 1;
// }

//--------------------------------------------------------//

static int Nucleo64_Init_Duration = 30*1000;
void Nucleo64_Init_Short(DigitalOut* LED){
    LED->write(1);
    wait_us(Nucleo64_Init_Duration);
    LED->write(0);
    wait_us(Nucleo64_Init_Duration);
}
void Nucleo64_Init_Long(DigitalOut* LED){
    LED->write(1);
    wait_us(Nucleo64_Init_Duration*3);
    LED->write(0);
    wait_us(Nucleo64_Init_Duration);
}
void Nucleo64_Init_NextWord(){
    wait_us(Nucleo64_Init_Duration*2);
}
void Nucleo64_Init_Finished_Successfully(DigitalOut* LED){
    Nucleo64_Init_Short(LED);
    Nucleo64_Init_Long(LED);
    Nucleo64_Init_NextWord();

    Nucleo64_Init_Short(LED);
    Nucleo64_Init_Long(LED);
    Nucleo64_Init_Short(LED);
    Nucleo64_Init_Short(LED);
    Nucleo64_Init_NextWord();

    Nucleo64_Init_Short(LED);
    Nucleo64_Init_Long(LED);
    Nucleo64_Init_Short(LED);
    Nucleo64_Init_Short(LED);
    Nucleo64_Init_NextWord();

    Nucleo64_Init_Long(LED);
    Nucleo64_Init_Short(LED);
    Nucleo64_Init_NextWord();

    Nucleo64_Init_Short(LED);
    Nucleo64_Init_Long(LED);
    Nucleo64_Init_NextWord();

    Nucleo64_Init_Long(LED);
    Nucleo64_Init_Long(LED);
    Nucleo64_Init_NextWord();

    Nucleo64_Init_Short(LED);
    Nucleo64_Init_NextWord();

    Nucleo64_Init_Long(LED);
    Nucleo64_Init_Long(LED);
    Nucleo64_Init_Long(LED);
    Nucleo64_Init_NextWord();

    Nucleo64_Init_Long(LED);
    Nucleo64_Init_Short(LED);
    Nucleo64_Init_Long(LED);
    Nucleo64_Init_Short(LED);
    Nucleo64_Init_NextWord();

    Nucleo64_Init_Long(LED);
    Nucleo64_Init_Short(LED);
    Nucleo64_Init_Long(LED);
    Nucleo64_Init_Short(LED);
    Nucleo64_Init_NextWord();
    
    Nucleo64_Init_Short(LED);
    Nucleo64_Init_Short(LED);
    Nucleo64_Init_Long(LED);
    Nucleo64_Init_NextWord();

    Nucleo64_Init_Short(LED);
    Nucleo64_Init_Long(LED);
    Nucleo64_Init_Long(LED);
    Nucleo64_Init_Short(LED);
    Nucleo64_Init_NextWord();

    Nucleo64_Init_Short(LED);
    Nucleo64_Init_Short(LED);
    Nucleo64_Init_NextWord();

    Nucleo64_Init_Short(LED);
    Nucleo64_Init_NextWord();

    Nucleo64_Init_Long(LED);
    Nucleo64_Init_Short(LED);
    Nucleo64_Init_Short(LED);
    Nucleo64_Init_NextWord();
}