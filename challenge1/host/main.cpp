/* 
 * Name: Matasano Challenge 1 (hex2base64)
 * File: main.cpp
 * Description: Simple program to demo the encode 
 * 		of a string of hex digits to base64
 * 		using the hex2base64 class
 * Author: kmmankad (kmmankad@gmail.com)
 * License: MIT License
 *
 */
#include "hex2base64.h"
#include <fstream>

// Function which prints the usage of this executable
void print_usage()
{
	cerr <<	"hex2base64: Encodes files using base64\n"
	     << "Usage: base64 [input] [output]\n"
	     << "       [input] and [output] are the input and output files, respectively.\n";
}

int main (int argc, char* argv[]){

	// Construct the converter class
	hex2base64 *h2b64 = new hex2base64();

	// If we have the wrong number of args,
	// print the usage banner and exit.
	if (argc != 3){
		print_usage();
		exit(-1);
	}

	// argv[1] is our input file
	// argv[2] is our output file
	string input_f = argv[1];
	// Open the input in binary mode.
	ifstream instream(input_f.c_str(), ios_base::in | ios_base::binary);
	if (!instream.is_open())
	{
		cerr << "Could not open input file!" << endl;
		exit(-1);
	}
	
	string output_f = argv[2];
	// Open the output in binary mode.
	ofstream outstream(output_f.c_str(), ios_base::out | ios_base::binary);
	if (!outstream.is_open())
	{
		cerr << "Could not open output file!" << endl;
		exit(-1);
	}

	h2b64->encode(instream,outstream);
	return 0;
}
