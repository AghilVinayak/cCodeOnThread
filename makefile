
output: ./test/src/test.o
	gcc -pthread ./test/src/test.o -o output

test.o: ./test/src/test.c
	gcc -c ./test/src/test.c

clean:
	rm ./test/src/*.o output
