#makefile for server
server:server.o parseString.o mySocket.o sqlite3Helper.o process.o 
	$(CC) -g -Wall -o $(@) $^ -lpthread -lsqlite3
.c.o:
	$(CC) -c $<
all:server
clean:all
	rm -f *.o 
install:clean
	cp server /usr/local/bin

