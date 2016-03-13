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
#include <stdio.h>
#include "hex2base64.h"

// Function which prints the usage of this executable
void print_usage()
{
	printf ("hex2base64: Encodes files using base64\n");
	printf("	Usage: base64 [input] [output]\n");
	printf("	[input] and [output] are the input and output files, respectively.\n");
}

int main (int argc, char* argv[]){

	// If we have the wrong number of args,
	// print the usage banner and exit.
	if (argc != 3){
		print_usage();
		exit(-1);
	}

	// argv[1] is our input file
	// argv[2] is our output file
	// Open the input in binary mode.
	FILE* instream = fopen(argv[1], "rb");
	if (instream == NULL)
	{
		printf("Could not open input file!");
		exit(-1);
	}
	
	// Open the output in binary mode.
	FILE* outstream = fopen(argv[2], "wb");
	if (outstream == NULL)
	{
		printf("Could not open output file!");
		exit(-1);
	}

	// Call the encode function which will
	// fread the input, encode that block
	// and fwrite the output
	encode(instream,outstream);
	
	// Close both file handles
	fclose(instream);
	fclose(outstream);
	return 0;
}
