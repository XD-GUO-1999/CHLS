/* fichier source.cpp */

#include <fstream>
#include <iostream>
#include "source.h"

using std::cout;
using std::endl;

void SOURCE::COMPORTEMENT()
{
  std::ifstream realStream("in_real.txt");
  std::ifstream imagStream("in_imag.txt");

  data_t_st1 tmp_real, tmp_imag;

  if (!realStream || !imagStream)
    cout << "[SOURCE] " << "Un des fichiers d'entree n'est pas ouvert" << endl;

  wait();

  out_valid.write(true);
  if (!realStream.eof() && !imagStream.eof())
  {
    realStream >> tmp_real;
    out_real.write(tmp_real);
    imagStream >> tmp_imag;
    out_imag.write(tmp_imag);
  }

  while (true)
  {
    wait();

    if (in_req.read() == true && out_valid)
    {
      if (!realStream.eof() && !imagStream.eof())
      {
        realStream >> tmp_real;
        out_real.write(tmp_real);
        imagStream >> tmp_imag;
        out_imag.write(tmp_imag);
        out_valid.write(true);
      }
      else
      {
        out_valid.write(false);
        cout << "[SOURCE] " << "Fin des fichiers d'entree atteinte." << endl;
      }
    }
  }
}
