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
#include <openacc.h>

#if defined(_WIN32) || defined(_WIN64)
#include <sys/timeb.h>
#define gettime(a) _ftime(a)
#define usec(t1,t2) ((((t2).time-(t1).time)*1000+((t2).millitm-(t1).millitm))*100)
typedef struct _timeb timestruct;
#else
#include <sys/time.h>
#define gettime(a) gettimeofday(a,NULL)
#define usec(t1,t2) (((t2).tv_sec-(t1).tv_sec)*1000000+((t2).tv_usec-(t1).tv_usec))
typedef struct timeval timestruct;
#endif

//Function to encode a hex string into base64 string
void encode(FILE* input_fp, FILE* output_fp);
unsigned int encode_block(char* input, unsigned int size, char* output);
static const char *restrict base64_LUT = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+\\";

#endif //HEX2BASE64
