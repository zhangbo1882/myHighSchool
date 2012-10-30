object = dList.o memory.o test.o
main: $(object)
	gcc $(object) -o main
clean:
	rm -rf *.o
	rm main
