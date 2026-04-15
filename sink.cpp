/* fichier sink.cpp */
#include <fstream>
#include <iostream>
#include "sink.h"

using std::cout;
using std::endl;

void SINK::COMPORTEMENT()
{
	std::ofstream realStream("out_real.txt");
	std::ofstream imagStream("out_imag.txt");

	std::ifstream realStream_ref("out_real_ref_valid.txt");
	std::ifstream imagStream_ref("out_imag_ref_valid.txt");

	data_t_out real, imag, real_ref, imag_ref, diff, max_error = 0;
	//data_t_out real_fix, imag_fix;

	int i = 0;
	if (!realStream || !imagStream || !realStream_ref || !imagStream_ref)
		cout << "[SINK] " << "Un des fichiers d'entree n'est pas ouvert" << endl;
	wait();

	out_req_sink.write(true);

	while (true)
	{
		wait();
		// if (in_real_sink.num_available() == 8 && in_imag_sink.num_available() == 8)
		if (out_req_sink && in_valid_sink.read() == true)
		{
			cout << "[SINK] " << "Lecture des 16 échantillons par le bloc SINK..." << endl;
			// for (i = 0; i < 8; i++)
			// {
			real = in_real_sink.read();
			imag = in_imag_sink.read();

			// real = real_fix.to_double();
			// imag = imag_fix.to_double();

			realStream << real << endl;
			imagStream << imag << endl;

			if (!realStream_ref.eof() && !imagStream_ref.eof())
			{
				realStream_ref >> real_ref;
				imagStream_ref >> imag_ref;
				diff = abs(real - real_ref);
				max_error = diff > max_error ? diff : max_error;
				diff = abs(imag - imag_ref);
				max_error = diff > max_error ? diff : max_error;
				out_req_sink.write(true);
			}
			//}
			cout << "[SINK] " << "Erreur maximale actuelle: " << max_error << endl;
		}
	}
}
