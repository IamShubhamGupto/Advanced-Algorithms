CC=gcc
CFLAGS=-c -Wall

prog: client.o server.o
	$(CC) client.o server.o 
client.o: client.c
	$(CC) $(CFLAGS) client.c
server.o: header.h server.c
	$(CC) $(CFLAGS) server.c
clean:
	rm -rf *.o