# hex2base64
#/* 
# * Name: Matasano Challenge 1 (hex2base64)
# * File: Makefile
# * Description: A minimalist Makefile to build this project
# * Author: kmmankad (kmmankad@gmail.com)
# * License: MIT License
# *
# */
TARGET := hex2base64
OBJECTS := $(patsubst %.c,%.o, $(wildcard *.c))
CXXFLAGS := -I. -g

all: clean $(TARGET)

$(TARGET): $(OBJECTS)
	gcc -g -o $@ $^

clean:
	\rm -rf $(OBJECTS) $(TARGET)
