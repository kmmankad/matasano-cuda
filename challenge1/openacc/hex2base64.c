/* 
 * Name: Matasano Challenge 1 (hex2base64)
 * File: hex2base64.cpp
 * Description: C-OpenACC implementation of a simple approach to encode
 * 		a string of hex digits to base64
 * Author: kmmankad (kmmankad@gmail.com)
 * License: MIT License
 *
 */
#include <string.h>
#include <stdio.h>
#include "openacc.h"
#include "hex2base64.h"

///  \brief encode reads a file block-by-block, and 
///		   encodes each block of ASCII to Base64 via the \c encode_block() function.
///  \params input_fp File handle to the input file
///  \params output_fp File handle to the output file
///  \return void
void encode(FILE* input_fp, FILE* output_fp){

	const int buff_sz = 16777216;
	char* inputtext;
	char* code;
	int n;
	int plainlength, codelength;

	// Allocate memory for the arrays
	inputtext = (char*)malloc(buff_sz);
	code = (char*)malloc(2*buff_sz);
	
	// Read in the file buff_sz bytes at a time
	while ((n = fread(inputtext, sizeof(char), buff_sz, input_fp)) == buff_sz){
		#pragma acc data copyin(inputtext[0:buff_sz]), copyin(base64_LUT[64]), copyout(code[0:4*buff_sz/3])
		codelength = encode_block (inputtext, sizeof(inputtext),code);
		fwrite(code, sizeof(char), codelength, output_fp);
	}
	// If its a smaller block than our buff_sz.
	// This could be at the end of a large file, or if the file itself
	// is smaller than buff_sz
	if (n>0){
		#pragma acc data copyin(inputtext[0:n]), present_or_copyin(base64_LUT[64]), copyout(code[0:4*n/3])
		codelength = encode_block (inputtext, n,code);
		fwrite(code, sizeof(char), codelength, output_fp);
	}
	
	// Declare completion to the user.
	printf("encode: Done processing.\n");
	
	if (!feof(input_fp)){
		printf("encode: File I/O Error!");
		return;
	}
	
	// Add in the trailing newline. 
	// Somehow windows doesn't need this, but linux did.
	fwrite("\n",sizeof(char),1,output_fp);

	// Free the dynamically malloc'd pointers
	free(code);
	free(inputtext);
}


///  \brief encode_block encodes a block of ASCII to Base64 function.
///		   We process 3 bytes at a time, which produce 4 bytes of Base64
///		   encoded data. We lookup the index of the Base64 character from 
///		   a static LUT, \c base64_LUT
///  \params input_fp File handle to the input file
///  \params output_fp File handle to the output file
///  \return void
unsigned int encode_block( char *restrict input, unsigned int size, char *restrict output){
	// Variables for timekeeping
    timestruct t1,t2;
	long long time_elapsed;
	
	// 4 byte array to store the indexes of the elements to lookup
	// from the base64_LUT LUT.
	char decoded_octets[4];
	printf ("hex2base64::encode_block: Input Len: %d\n",size);
	
	// i variable will track the input array position
	// k variable will track the output array position
	unsigned int i, k;
	
	// Mark the start time
	gettime( &t1 );
	
	#pragma acc data present(input[0:size]), present(base64_LUT[64]), copyout(output[0:4*size/3])
	#pragma acc kernels 
	#pragma acc loop private(decoded_octets, k) independent
	for (i=0; i<size; i=i+3){ // Process 3 bytes in one iteration
		// X X X X X X X X Y Y Y Y  Y Y Y Y Z Z  Z Z Z Z Z Z 
		// |    o1   |    o2       |   o3       |  o4
		
		// Calculate the output array position based
		// on the input array position (loop iteration)
		k = (4*i)/3;
		
		// Process o1
		decoded_octets[0] = input[i] >> 2;
		output[k] = base64_LUT[decoded_octets[0]];
		
		// Process o2
		decoded_octets[1] = (input[i] & 0x03) << 4;
		
		// Check if we have (i+1)th input element
		if (i+1 < size){
			// Process o2
			decoded_octets[1] |= ((input[i+1] & 0xF0) >> 4);
			output[k+1] = base64_LUT[decoded_octets[1]];

			// Process o3
			decoded_octets[2] = ((input[i+1] & 0x0F) << 2);
			
			// Check if we have an (i+2)th input element
			if (i+2 < size){
				// Process o3
				decoded_octets[2] |= ((input[i+2] & 0xC0) >> 6);
				output[k+2] = base64_LUT[decoded_octets[2]];

				// Process o4
				decoded_octets[3] = input[i+2] & 0x3F;
				output[k+3] = base64_LUT[decoded_octets[3]];
			} else {
				output[k+2] = base64_LUT[decoded_octets[2]];
				output[k+3] = '=';
			}
		}else{
			output[k+1] = base64_LUT[decoded_octets[1]];
			output[k+2] = '='; 
			output[k+3] = '='; 
		}
	
	}
	// Mark the end time
	gettime(&t2);
	
	// Compute time elapsed
	time_elapsed = usec(t1,t2);
	
	// Display that to the user
	printf("encode_block: %03ld microseconds\n", time_elapsed );
	
	// Return the code length
	return ((4*size)/3);
}

