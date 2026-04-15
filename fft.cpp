/* fichier fft.cpp */

#include <iostream>
#include "fft.h"
using std::cout;
using std::endl;

template <typename T_IN, typename T_OUT>
void butterfly(T_IN ar, T_IN ai, T_IN br, T_IN bi, widdle_t wr, widdle_t wi,
                T_OUT &ar_out, T_OUT &ai_out, T_OUT &br_out, T_OUT &bi_out)
{
    T_OUT tr = br * wr - bi * wi;
    T_OUT ti = br * wi + bi * wr;

    br_out = ar - tr;
    bi_out = ai - ti;

    ar_out = ar + tr;
    ai_out = ai + ti;
}

const widdle_t W_R[4] = {1, 0.7071067812, 0, -0.7071067812};
const widdle_t W_I[4] = {0, -0.7071067812, -1, -0.7071067812};

// your code
void FFT::process()
{
    int i = 0;
    int k = 0;
    int k1 = 0;
    int j = 0;

    data_t_st1 R1[8], I1[8];           // conserver les donnée (Real, Imag)
    data_t_st2 R2[8], I2[8];
    data_t_st3 R3[8], I3[8];
    data_t_out R4[8], I4[8];

    data_t_st1 temp_R[8], temp_I[8]; // temporaire pour les calculs
    out_req.write(true);

///////////////////////////////////////
    // out_valid_sink.write(false);
    // out_real_sink.write(0);
    // out_imag_sink.write(0);
    /////////////
    //out_valid_sink.write(true);/

    while (1)
    {
        wait();
        cout << "[FFT: " << sc_time_stamp() << "] i= " << i << endl;
        // 1. lire
        // out_req.write(true);
        if (i < 8 && j == 0)
        {
            if (in_valid.read() == true && out_req)
            {
                temp_R[i] = in_real.read();
                temp_I[i] = in_imag.read();
                i++;
            }
        }

        if (i == 8)
            out_req.write(false);
        else
            out_req.write(true);

        // out_req.write(false);
        
        if (i == 8 && k == 0)
        {
            for (k1 = 0; k1 < 8; k1++)
            {
                cout << "real = " << temp_R[k1] << "   imag = " << temp_I[k1] << endl;
            }
            // 2. calcule
            R1[0] = temp_R[0];
            I1[0] = temp_I[0];
            R1[1] = temp_R[4];
            I1[1] = temp_I[4];
            R1[2] = temp_R[2];
            I1[2] = temp_I[2];
            R1[3] = temp_R[6];
            I1[3] = temp_I[6];
            R1[4] = temp_R[1];
            I1[4] = temp_I[1];
            R1[5] = temp_R[5];
            I1[5] = temp_I[5];
            R1[6] = temp_R[3];
            I1[6] = temp_I[3];
            R1[7] = temp_R[7];
            I1[7] = temp_I[7];
            // === STAGE 1 (premier colonne) ===
            butterfly(R1[0], I1[0], R1[1], I1[1], W_R[0], W_I[0], R2[0], I2[0], R2[1], I2[1]);
            butterfly(R1[2], I1[2], R1[3], I1[3], W_R[0], W_I[0], R2[2], I2[2], R2[3], I2[3]);
            butterfly(R1[4], I1[4], R1[5], I1[5], W_R[0], W_I[0], R2[4], I2[4], R2[5], I2[5]);
            butterfly(R1[6], I1[6], R1[7], I1[7], W_R[0], W_I[0], R2[6], I2[6], R2[7], I2[7]);

            // === STAGE 2 (second colonne) ===
            butterfly(R2[0], I2[0], R2[2], I2[2], W_R[0], W_I[0], R3[0], I3[0], R3[2], I3[2]); // Group 1
            butterfly(R2[1], I2[1], R2[3], I2[3], W_R[2], W_I[2], R3[1], I3[1], R3[3], I3[3]); // Group 1 (W2)

            butterfly(R2[4], I2[4], R2[6], I2[6], W_R[0], W_I[0], R3[4], I3[4], R3[6], I3[6]); // Group 2
            butterfly(R2[5], I2[5], R2[7], I2[7], W_R[2], W_I[2], R3[5], I3[5], R3[7], I3[7]); // Group 2 (W2)

            // === STAGE 3 (troisième colonne) ===
            // W0, W1, W2, W3
            butterfly(R3[0], I3[0], R3[4], I3[4], W_R[0], W_I[0], R4[0], I4[0], R4[4], I4[4]);
            butterfly(R3[1], I3[1], R3[5], I3[5], W_R[1], W_I[1], R4[1], I4[1], R4[5], I4[5]);
            butterfly(R3[2], I3[2], R3[6], I3[6], W_R[2], W_I[2], R4[2], I4[2], R4[6], I4[6]);
            butterfly(R3[3], I3[3], R3[7], I3[7], W_R[3], W_I[3], R4[3], I4[3], R4[7], I4[7]);

            for (k = 0; k < 8; k++)
            {
                cout << "real = " << R4[k] << "   imag = " << I4[k] << " k = "<< k << endl;
            }
        }

                // 3. écrir
        //out_valid_sink.write(true);
        if (k == 8)
        {   
            if (j == 0){
            out_valid_sink.write(true);
            out_real_sink.write(R4[j]);
            out_imag_sink.write(I4[j]);
            }

            if (j < 8)
            {
                 if (in_req_sink.read() == true && out_valid_sink)
                {
                    cout << "real = " << R4[j+1] << "   imag = " << I4[j+1] << " j = "<< j << endl;
                    out_real_sink.write(R4[j+1]);
                    out_imag_sink.write(I4[j+1]);
                    j++;
                }
            }

            if (j == 8){
                out_valid_sink.write(false);
                j = 0;
                i = 0;
                k = 0;
            }else{
                out_valid_sink.write(true);
            }
        }
    }
}
