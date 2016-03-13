#ifndef HEX2BASE64_
#define HEX2BASE64_
/* 
 * Name: Matasano Challenge 1 (hex2base64)
 * File: hex2base64.h
 * Description: C declaration of an implementation to encode
 * 		a string of hex digits to base64
 * Author: kmmankad (kmmankad@gmail.com)
 * License: MIT License
 *
 */
#include <stdlib.h>
#include <string.h>


//Function to encode a hex string into base64 string
void encode(FILE* input_fp, FILE* output_fp);
unsigned int encode_block(char* input, unsigned int size, char* output);
static const char* base64_LUT = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+\\";

#endif //HEX2BASE64
