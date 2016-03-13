/* 
 * Name: Matasano Challenge 1 (hex2base64)
 * File: hex2base64.cpp
 * Description: C implementation of a simple approach to encode
 * 		a string of hex digits to base64
 * Author: kmmankad (kmmankad@gmail.com)
 * License: MIT License
 *
 */
#include <string.h>
#include <stdio.h>
#include "hex2base64.h"


void encode(FILE* input_fp, FILE* output_fp){

	const int buff_sz = 16777216;
	char* inputtext;
	char* code;
	size_t n;
	int plainlength, codelength;

	//Allocate memory for the arrays
	inputtext = (char*)malloc(buff_sz);
	code = (char*)malloc(2*buff_sz);
	
	// Read in the file buff_sz bytes at a time
	while ((n = fread(inputtext, sizeof(char), buff_sz, input_fp)) == buff_sz){
		codelength = encode_block (inputtext, sizeof(inputtext),code);
		fwrite(code, sizeof(char), codelength, output_fp);
	}
	// If its a smaller file than our buffer_sz.
	if (n>0){
		codelength = encode_block (inputtext, n,code);
		fwrite(code, sizeof(char), codelength, output_fp);
	}
	
	// Declare completion to the user.
	printf("Done processing.\n");
	
	if (!feof(input_fp)){
		printf("File I/O Error!");
		return;
	}
	fwrite("\n",sizeof(char),1,output_fp);

	// Free the dynamically malloc'd pointers
	free(code);
	free(inputtext);
}

//Actual encode_block function
unsigned int encode_block( char* input, unsigned int size, char* output){

	char decoded_octets[4];
	printf ("hex2base64::encode_block: Input Len: %d\n",size);
	unsigned int i,j=0;

	for (i=0; i<size; i=i+3){
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

