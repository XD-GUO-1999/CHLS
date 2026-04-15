#ifndef FFT_H
#define FFT_H

#define SC_INCLUDE_FX
#include <systemc.h>

// typedef sc_fixed<23, 18, SC_RND, SC_SAT> data_t_st1;
// typedef sc_fixed<25, 20, SC_RND, SC_SAT> data_t_st2;
// typedef sc_fixed<27, 22, SC_RND, SC_SAT> data_t_st3;
// typedef sc_fixed<29, 24, SC_RND, SC_SAT> data_t_out;

typedef sc_fixed<29, 24, SC_RND, SC_SAT> data_t_st1;
typedef sc_fixed<29, 24, SC_RND, SC_SAT> data_t_st2;
typedef sc_fixed<29, 24, SC_RND, SC_SAT> data_t_st3;
typedef sc_fixed<29, 24, SC_RND, SC_SAT> data_t_out;
typedef sc_fixed<23, 2, SC_RND, SC_SAT> widdle_t;


//#pragma hls_design top
SC_MODULE(FFT)
{
    sc_in_clk clk;
    // sc_fifo_in<float> in;
    // sc_fifo_out<float> out;

    sc_in<data_t_st1> in_real;
    sc_in<data_t_st1> in_imag;
    sc_in<bool> in_valid;
    sc_out<bool> out_req;
    ///////////
    //sc_in<bool> rst;

    sc_out<data_t_out> out_real_sink;
    sc_out<data_t_out> out_imag_sink;
    sc_out<bool> out_valid_sink;
    sc_in<bool> in_req_sink;

    data_t_st1 sample_real[8];
    data_t_st1 sample_imag[8];

    SC_CTOR(FFT)
    {
        SC_THREAD(process);
        sensitive << clk.pos();
///////////////////
        //reset_signal_is(rst, false);
    }
    void process();




};
#endif
