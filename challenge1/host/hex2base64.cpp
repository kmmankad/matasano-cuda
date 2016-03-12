/* 
 * Name: Matasano Challenge 1 (hex2base64)
 * File: hex2base64.cpp
 * Description: C++ implementation of a simple approach to encode
 * 		a string of hex digits to base64
 * Author: kmmankad (kmmankad@gmail.com)
 * License: MIT License
 *
 */
#include <iostream>
#include <string.h>
#include <stdio.h>
#include "hex2base64.h"

using namespace std;
const char* hex2base64::base64_LUT = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+\\";

//Constructor
hex2base64::hex2base64(){
}

void hex2base64::encode(std::istream& istream_in, std::ostream& ostream_in){

	const int buff_sz = 16777216;
	char* inputtext = new char[buff_sz];
	char* code = new char[2*buff_sz];
	int plainlength;
	int codelength;

	do
	{
		istream_in.read(inputtext, buff_sz);
		plainlength = istream_in.gcount();
		//
		codelength = encode_block(inputtext, plainlength, code);
		ostream_in.write(code, codelength);
	}
	while (istream_in.good() && plainlength > 0);
       	
	ostream_in.write("\n",1);

	delete [] code;
	delete [] inputtext;
}

//Actual encode_block function
unsigned int hex2base64::encode_block(const char* input, unsigned int size, char* output){

	char decoded_octets[4];
	cout << "hex2base64::encode_block: Input Len:" << size << endl;
	unsigned int j=0;

	for (int i=0; i<size; i=i+3){
		// X X X X X X X X Y Y Y Y  Y Y Y Y Z Z  Z Z Z Z Z Z 
		// |    o1   |    o2       |   o3       |  o4
		decoded_octets[0] = input[i] >> 2;
		output[j++] = base64_LUT[decoded_octets[0]];
		decoded_octets[1] = (input[i] & 0x03) << 4;
		// Check if we have (i+1)th input element
		if (i+1 < size){
			decoded_octets[1] |= ((input[i+1] & 0xF0) >> 4);
			output[j++] = base64_LUT[decoded_octets[1]];

			decoded_octets[2] = ((input[i+1] & 0x0F) << 2);
			// Check if we have an (i+2)th input element
			if (i+2 < size){
				decoded_octets[2] |= ((input[i+2] & 0xC0) >> 6);
				output[j++] = base64_LUT[decoded_octets[2]];

				decoded_octets[3] = input[i+2] & 0x3F;
				output[j++] = base64_LUT[decoded_octets[3]];
			} else {
				output[j++] = base64_LUT[decoded_octets[2]];
				output[j++] = '=';
			}
		}else{
			output[j++] = base64_LUT[decoded_octets[1]];
			output[j++] = '='; 
			output[j++] = '='; 
		}
	
	}

	// Return the code length
	return (j);
}

