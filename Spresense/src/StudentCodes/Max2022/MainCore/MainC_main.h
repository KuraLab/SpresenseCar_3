// Written by MAX (Created 20-06-2022)

// Features : Main program for Spresense

//--------------------------------------------------------//

#define max12345 allnameoccupied

//--------------------------------------------------------//

// Only for Main Core
#ifndef SUBCORE

//--------------------------------------------------------//

#ifndef MAX2022_MAINC_MAIN_H
#define MAX2022_MAINC_MAIN_H

namespace MAX2022
{
    // Functions Declaration
    unsigned int FFT_PikaPika_Routine();

    //--------------------------------------------------------//

    // MAIN PROGRAM
    void MainCore_setup();
    void MainCore_loop();
}

#endif

#endif