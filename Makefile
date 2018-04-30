# A simple Makefile
# # Elias Aleman 01020585
# # CS 262, Lab Section 202
# # Project 1
#
#
CC = gcc
CFLAGS=-g -Wall
TARGET = proj1_ealeman_202
all = $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c

clean:
	 rm $(TARGET)
