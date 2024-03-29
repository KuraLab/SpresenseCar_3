// Written by MAX (Created 07-09-2022)

/* Features :   Code for Spresense SubCore 2
                SubCore 2 -> FFT
*/
//--------------------------------------------------------//

#if (SUBCORE == 2)

//--------------------------------------------------------//

#include "Sub2_main.h"
#include "Sub2_TaskList.h"
#include <IncludeLists.h>
#include "../FFT_Param/FFT_Param.h"

//--------------------------------------------------------//

// Functions Declaration

//--------------------------------------------------------//

namespace MAX2022
{
    void Sub2_setup(void){
        // MP.begin();
        arm_fft_init();
        phi_init();
    }
    void Sub2_loop(void){
        int8_t msgid;
        uint32_t msgdata;

        // MPLog("now wait receive");
        MP.Recv(&msgid, &msgdata);
        // MPLog("now received");

        switch (msgid)
        {
        case C2_T0_FFT:{
            // MPLog("now enter fft");

            // get phi
            phi_update(msgdata);
            // MPLog("%ld\r", msgdata);

            // get dx_phi
            MP.Recv(&msgid, &msgdata);
            if (msgid == C2_T1_DXPHI)
            {
                dx_phi_update(msgdata);
            }

            //get dy_phi
            MP.Recv(&msgid, &msgdata);
            if (msgid == C2_T2_DYPHI)
            {
                dy_phi_update(msgdata);
            }


            // FFT calculation
            static uint16_t FFT_countdown_sub2 = FFT_LEN;
            // MPLog("%d\n", FFT_countdown_sub2);
            if (FFT_countdown_sub2 == 0)
            {
                // reset count
                FFT_countdown_sub2 = FFT_CALC_RATE;

                // FFT & Power Spectrum
                // ->-> rfft->FFT, cmplx_mag->complex magnitude
                // -> phi
                arm_rfft_fast_f32(&FFT_instance, input_buffer, output_buffer, 0);
                arm_cmplx_mag_f32(output_buffer, FFT_result, FFT_LEN/2);
                // -> dx_phi
                arm_rfft_fast_f32(&FFT_instance, dx_input_buffer, dx_output_buffer, 0);
                arm_cmplx_mag_f32(dx_output_buffer, dx_FFT_result, FFT_LEN/2);
                // -> dy_phi
                arm_rfft_fast_f32(&FFT_instance, dy_input_buffer, dy_output_buffer, 0);
                arm_cmplx_mag_f32(dy_output_buffer, dy_FFT_result, FFT_LEN/2);

                // determine if need to self-excite by finding peak
                if (!peak_check())
                {
                    MP.Send(C2_T3_NO_PEAK, C2_T3_NO_PEAK);  // メインコアに失敗を通報
                }

                // FFT result preprocessing
                FFT_result_processing();

                // estimate inner/outer layer  ********
                Judgement = inner_outer_estimate();

                // print out data to Serial Monitor
                // fft_data_print_out();

                // get peak & check need for self-excite (not used now)
                // float f_peak = get_peak_frequency(FFT_result);
                // if (f_peak < 0) // 検出失敗
                // {
                //     MP.Send(C2_T3_NO_PEAK, C2_T3_NO_PEAK);  // メインコアに失敗を通報
                // }
                // determine swarm size (not used now)
                // float length_estimate = length_estimation(f_peak);
                // MPLog("Length Estimate : %4.2f\n", length_estimate);

                // check phi [2023/02/15]
                // test_20230215();

            } else {
                FFT_countdown_sub2--;
            }
            break;
        }
        // case C2_T1_DXPHI:    // not for receiving
        // case C2_T2_DYPHI:    // not for receiving
        // case C2_T3_NO_PEAK:  // not for receiving
        default:
            break;
        }
    }

    // void test_20230215(){
    //     // for (int i = 0; i < FFT_LEN/2; i++)
    //     // {
    //     //     MPLog("%5.5f", FFT_result[i]);
    //     // }
    //     // MPLog("\n");

    //     for (int i = 1; i < FFT_LEN/2; i++)
    //     {
    //         if ((FFT_result[i]>FFT_result[i+1]) && (FFT_result[i]>FFT_result[i-1]))
    //         {
    //             MPLog("%d\n", i);
    //             break;
    //         }
    //     }
    // }
}

#endif