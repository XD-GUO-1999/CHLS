//  main.h
#define SC_INCLUDE_FX
#include <systemc.h>
#include "source.h"
#include "fft.h"
#include "sink.h"

// typedef sc_fixed<23, 18, SC_RND, SC_SAT> data_t_st1;
typedef sc_fixed<29, 24, SC_RND, SC_SAT> data_t_st1;
// typedef sc_fixed<25, 20, SC_RND, SC_SAT> data_t_st2;
// typedef sc_fixed<27, 22, SC_RND, SC_SAT> data_t_st3;
typedef sc_fixed<29, 24, SC_RND, SC_SAT> data_t_out;

SC_MODULE (TOP) {
  
  // signals
  sc_clock clk;
  //sc_fifo<float> source_fft;
  //sc_fifo<float> fft_sink;
      
  sc_signal<data_t_st1> sig_real;
  sc_signal<data_t_st1> sig_imag;
  sc_signal<bool>  sig_valid;
  sc_signal<bool>  sig_req;

  sc_signal<data_t_out> sig_real_sink;
  sc_signal<data_t_out> sig_imag_sink;
  sc_signal<bool>  sig_valid_sink;
  sc_signal<bool>  sig_req_sink;

  // instanciate
  SOURCE SOURCE1;
  FFT FFT1;
  SINK SINK1;

 SC_CTOR(TOP)
   :  clk("clk", 10, SC_NS, 0.5),
    //source_fft("source_fft", 16),
    //fft_sink("fft_sink", 16),
    FFT1("FFT_PROCESS"),
    SOURCE1("SOURCE_PROCESS"),
    SINK1("SINK_PROCESS")
      {

	FFT1.clk(clk);
	//FFT1.in(source_fft);
  //FFT1.in_data(sig_data);
  FFT1.in_real(sig_real);
  FFT1.in_imag(sig_imag);
  FFT1.in_valid(sig_valid);
  FFT1.out_req(sig_req);

	//FFT1.out(fft_sink);
  FFT1.out_real_sink(sig_real_sink);
  FFT1.out_imag_sink(sig_imag_sink);
  FFT1.out_valid_sink(sig_valid_sink);
  FFT1.in_req_sink(sig_req_sink);


	// SOURCE1.clk(clk);
	// SOURCE1.out(source_fft);

  SOURCE1.clk(clk);
  //SOURCE1.out_data(sig_data);
  SOURCE1.out_real(sig_real);
  SOURCE1.out_imag(sig_imag);
  SOURCE1.out_valid(sig_valid);
  SOURCE1.in_req(sig_req);

	SINK1.clk(clk);
	//SINK1.in(fft_sink);   
  SINK1.in_real_sink(sig_real_sink);
  SINK1.in_imag_sink(sig_imag_sink);
  SINK1.in_valid_sink(sig_valid_sink);
  SINK1.out_req_sink(sig_req_sink);
      }
};

