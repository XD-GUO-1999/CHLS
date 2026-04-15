//  main.cpp 
// Testbench pour FFT avec donn�es en flottant
#define SC_INCLUDE_FX

#include <systemc.h>
#include "main.h"


int sc_main(int argc, char *argv[])
{

  // Instanciation du TOP
  TOP mainTop("top");

  // Creation des traces
  sc_trace_file *tf = sc_create_vcd_trace_file("trace");
  tf->set_time_unit(1, SC_NS);
  // ATTENTION:
  // on peut pas faire ceci:
  //sc_trace(tf, mainTop.source_fft, "fifo1");
  // MAIS il faut faire appel a la methode
  // trace() du canal que l'on veut suivre
  // mainTop.source_fft.trace(tf);
  // mainTop.fft_sink.trace(tf);
  sc_trace(tf, mainTop.sig_real, "sig_real");
  sc_trace(tf, mainTop.sig_imag, "sig_imag");
  sc_trace(tf, mainTop.sig_valid, "sig_valid");
  sc_trace(tf, mainTop.sig_req, "sig_req");

  sc_trace(tf, mainTop.sig_real_sink, "sig_real_sink");
  sc_trace(tf, mainTop.sig_imag_sink, "sig_imag_sink");
  sc_trace(tf, mainTop.sig_valid_sink, "sig_valid_sink");
  sc_trace(tf, mainTop.sig_req_sink, "sig_req_sink");

  //Lancement de la simulation
  sc_start(2000, SC_NS);

  //Fin
  cout << "Finished at " << sc_time_stamp() << "\n";
  //Fermeture du fichier de traces
  sc_close_vcd_trace_file(tf);

  return 0;

}
