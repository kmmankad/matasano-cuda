#ifndef HEX2BASE64_
#define HEX2BASE64_
/* 
 * Name: Matasano Challenge 1 (hex2base64)
 * File: hex2base64.h
 * Description: C++ declaration of a simple class
 * 		that implements a function to decode
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

		//Function to decode a hex string into base64 string
		void decode(const char* input, unsigned int size, char* output);
	private:
		static const char* base64_LUT; 
		char* decoded;
};
#endif //HEX2BASE64
