// Written by MAX (Created 07-09-2022)

// Features : Parameters & Settings for FFT

// Important: Each core share different of variable, even if same address

//--------------------------------------------------------//

#ifndef MAX2022_FFT_PARAM_H
#define MAX2022_FFT_PARAM_H

#define ITSMAX2022TIME
#ifdef  ITSMAX2022TIME
    /* Use CMSIS library */
    #define ARM_MATH_CM4
    #define __FPU_PRESENT 1U
    #include <cmsis/arm_math.h>
#endif

//--------------------------------------------------------//

namespace MAX2022 
{
    // FFT Parameter (1)
    const float Omega_0                         = 20.0;     // 固有角速度 [rad\s]（振動）

    // FFT Program Parameter
    // -> Time related
    const int   FFT_UPDATE_PERIOD_US            = 100;      // 制御周期[us] 100us -> 10kHz
    const float FFT_TIME_RESOLUTION             = 0.000001;
    // -> Period - How often does main core sends phi data to FFT core (so that data is taken at correct interval)
    const float FFT_PROCESS_PERIOD_US           = (2.0*PI/Omega_0/2.0)/FFT_TIME_RESOLUTION/FFT_UPDATE_PERIOD_US;      // 通報周期[us] // =1570.80...
    // -> Period - How often does FFt core actually carry out FFT
    const int   FFT_CALC_RATE                   = 8;

    // FFT Hyperparameter
    extern arm_rfft_fast_instance_f32           FFT_instance;
    const float FFT_MSG_SCALE                   = 10000.0;
    const float FFT_MIDSHIFT                    = 100000000.0;
    // const int   FFT_LEN                         = 256       //original
    const int   FFT_LEN                         = 512;
    const int   FFT_MAX_CHANNEL_NUM             = 1;

    // FFT Parameter (2)
    const float dt                              = FFT_TIME_RESOLUTION * FFT_UPDATE_PERIOD_US;
    const float kappa                           = 0.5;      // 結合強度（振動型）
    const float my_gamma                        = 0.20;     // 粘性係数
    const float PEAK_POWER_THRESHOLD            = 3.0;      // 観測している位相のピークパワーがこれを下回ったら検出扱いにしない
    // const float SELF_EXITATION_INTENSITY        = 2.0;      // 自励入力の大きさ
    const float GAMMA_CONST_1                   = 0.09;     // 動的粘性の定数項
    const float GAMMA_CONST_2                   = 0.09;     // 動的粘性のエッジ数に比例する項

    // FFT Variables
    extern double  mod_varphi;
    extern double  varphi;                                  // 出力位相 phi+phi_bar [rad]
    extern double  phi_bar;                                 // 相互作用無しの位相 [rad]
    extern double  phi;                                     // 相互作用位相 [rad]
    extern double  sum_dphi;
    extern double  adaptive_gamma;                          // 定数項
    extern double  dphi[PIKA_SENSOR_COUNT];                 // 各方向の位相差 [rad] 
    extern double  c_fft;

    // FFT Runtime Variables
    extern bool    is_Self_Excitation;
    extern uint8_t PikaPika_light_sensor_life[PIKA_SENSOR_COUNT];
    extern uint8_t Judgement;
    // -> phi
    extern float   phi_buffer[FFT_LEN];
    extern float   input_buffer[FFT_LEN];
    extern float   output_buffer[FFT_LEN];
    extern float   FFT_result[FFT_LEN];
    extern float   FFT_result_processed[FFT_LEN];
    extern uint8_t FFT_peak_trough_pos[FFT_LEN];
    // -> dx phi
    extern float   dx_phi_buffer[FFT_LEN];
    extern float   dx_input_buffer[FFT_LEN];
    extern float   dx_output_buffer[FFT_LEN];
    extern float   dx_FFT_result[FFT_LEN];
    extern float   dx_FFT_result_processed[FFT_LEN];
    extern uint8_t dx_FFT_peak_trough_pos[FFT_LEN];
    // -> dy phi
    extern float   dy_phi_buffer[FFT_LEN];
    extern float   dy_input_buffer[FFT_LEN];
    extern float   dy_output_buffer[FFT_LEN];
    extern float   dy_FFT_result[FFT_LEN];
    extern float   dy_FFT_result_processed[FFT_LEN];
    extern uint8_t dy_FFT_peak_trough_pos[FFT_LEN];

}

#endif