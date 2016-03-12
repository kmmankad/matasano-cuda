#ifndef HEX2BASE64_
#define HEX2BASE64_
/* 
 * Name: Matasano Challenge 1 (hex2base64)
 * File: hex2base64.h
 * Description: C++ declaration of a simple class
 * 		that implements a function to encode
 * 		a string of hex digits to base64
 * Author: kmmankad (kmmankad@gmail.com)
 * License: MIT License
 *
 */
#include <stdlib.h>
#include <iostream>
#include <string.h>

using namespace std;

class hex2base64{
	public:
		//Constructor
		hex2base64();

		//Function to encode a hex string into base64 string
		unsigned int encode_block(const char* input, unsigned int size, char* output);
		void encode(std::istream& istream_in, std::ostream& ostream_in);
	private:
		static const char* base64_LUT; 
};
#endif //HEX2BASE64
