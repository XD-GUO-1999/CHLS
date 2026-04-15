/* fichier source.h */
#define SC_INCLUDE_FX
#ifndef SOURCE_H
#define SOURCE_H

#include <systemc.h>

typedef sc_fixed<29, 24, SC_RND, SC_SAT> data_t_st1;

SC_MODULE(SOURCE)
    {
        sc_in_clk    clk;
        //sc_fifo_out<float> out;
        sc_out<data_t_st1> out_real;
        sc_out<data_t_st1> out_imag;
        sc_out<bool>  out_valid;
        sc_in<bool>   in_req;

        void COMPORTEMENT();

          SC_CTOR(SOURCE)
                {
                  SC_THREAD(COMPORTEMENT);
                  sensitive << clk.pos();
                 }
};
#endif
