CC=g++
CFLAGS=-I.


%.o: %.cpp
	$(CC) -c -o $@ $< $(CFLAGS)
main.out: game.o main.o
	$(CC) -o main.out game.o main.o
clean:
	rm -f *.o
