# hex2base64
#/* 
# * Name: Matasano Challenge 1 (hex2base64)
# * File: Makefile
# * Description: A minimalist Makefile to build this project
# * Author: kmmankad (kmmankad@gmail.com)
# * License: MIT License
# *
# */

CC := pgcc
TARGET := hex2base64
OBJECTS := $(patsubst %.c,%.obj, $(wildcard *.c))
CCFLAGS := -I. -g
ACCFLAGS := -fast -Minfo -acc -ta=nvidia 
EXE := exe

all: clean $(TARGET).$(EXE)

$(TARGET).$(EXE): $(wildcard *.c)
	$(CC) $(CCFLAGS) $(ACCFLAGS) -o $@ $^

clean:
	rm -rf $(OBJECTS) $(TARGET).$(EXE) $(TARGET).dwf $(TARGET).pdb 
