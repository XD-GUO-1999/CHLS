
#ifndef SINK_H
#define SINK_H
#define SC_INCLUDE_FX
#include <systemc.h>

typedef sc_fixed<29, 24, SC_RND, SC_SAT> data_t_out;

SC_MODULE(SINK)
{
     sc_in_clk clk;
     // sc_fifo_in<float> in;
     sc_in<data_t_out> in_real_sink;
     sc_in<data_t_out> in_imag_sink;
     sc_out<bool> out_req_sink;
     sc_in<bool> in_valid_sink;

     void COMPORTEMENT();

     SC_CTOR(SINK)
     {
          SC_THREAD(COMPORTEMENT);
          sensitive << clk.pos();
     }
};
#endif
