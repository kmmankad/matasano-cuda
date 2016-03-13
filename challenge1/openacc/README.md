# Hex2Base64 - with OpenACC
This is a simple C-openACC based implementation of the initial single threaded implementation in ../host. It uses the PGI compiler's implementation of the OpenACC standard.

Why a C version? The machine I have access to runs Windows, and the PGI C++ Compiler (pgc++) is not available for windows.

### Description
To build:
```sh
make
```
To run: (where input.txt is a sample input file)
```sh
hex2base64acc input.txt
```
### Benchmarks
TODO
### License
MIT

