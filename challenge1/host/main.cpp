/* 
 * Name: Matasano Challenge 1 (hex2base64)
 * File: main.cpp
 * Description: Simple program to demo the decode
 * 		of a string of hex digits to base64
 * 		using the hex2base64 class
 * Author: kmmankad (kmmankad@gmail.com)
 * License: MIT License
 *
 */
#include "hex2base64.h"

int main (int argc, char* argv[]){

	// Construct the converter class
	hex2base64 *h2b64 = new hex2base64();
	
	// Input string
	// TODO: Add support to slurp a file instead
	const char* input_str = "ABCDEFGHI";
	
	// Get the input string length
	unsigned int input_sz = strlen(input_str);

	// Define the output string
	char* output_str = new char[2*input_sz];

	// Call the decode function
	h2b64->decode(input_str,input_sz, output_str);

	// Print the final output
	cout << "output:"<< output_str <<endl;

	return 0;
}
