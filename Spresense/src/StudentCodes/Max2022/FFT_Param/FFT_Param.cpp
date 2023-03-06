// Written by MAX (Created 07-09-2022)

// Features : Parameters & Settings for FFT

// Important: Each core share different of variable, even if same address

//--------------------------------------------------------//

#include <IncludeLists.h>

namespace MAX2022
{
    // FFT Hyperparameter
    arm_rfft_fast_instance_f32 FFT_instance;

    // FFT Variables
    double  mod_varphi          = 0.0;
    double  varphi              = 0.0;          // 出力位相 phi+phi_bar [rad]
    double  phi_bar             = 0.0;          // 相互作用無しの位相 [rad]
    double  phi                 = 0.0;          // 相互作用位相 [rad]
    double  sum_dphi            = 0.0;
    double  adaptive_gamma      = GAMMA_CONST_1;// 定数項
    double  dphi[PIKA_SENSOR_COUNT] =           // 各方向の位相差 [rad]
                {0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0}; 
    double  c_fft               = 0.0;

    // FFT Runtime Variables
    bool    is_Self_Excitation = false;
    uint8_t PikaPika_light_sensor_life[PIKA_SENSOR_COUNT] = {0,0,0,0,0,0,0,0};
    uint8_t Judgement;
    // -> phi
    float   phi_buffer[FFT_LEN];
    float   input_buffer[FFT_LEN];
    float   output_buffer[FFT_LEN];
    float   FFT_result[FFT_LEN];
    float   FFT_result_processed[FFT_LEN];
    uint8_t FFT_peak_trough_pos[FFT_LEN];
    // -> dx phi
    float   dx_phi_buffer[FFT_LEN];
    float   dx_input_buffer[FFT_LEN];
    float   dx_output_buffer[FFT_LEN];
    float   dx_FFT_result[FFT_LEN];
    float   dx_FFT_result_processed[FFT_LEN];
    uint8_t dx_FFT_peak_trough_pos[FFT_LEN];
    // -> dy phi
    float   dy_phi_buffer[FFT_LEN];
    float   dy_input_buffer[FFT_LEN];
    float   dy_output_buffer[FFT_LEN];
    float   dy_FFT_result[FFT_LEN];
    float   dy_FFT_result_processed[FFT_LEN];
    uint8_t dy_FFT_peak_trough_pos[FFT_LEN];
}