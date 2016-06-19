compile: my-disk.c
	gcc -Wall my-disk.c -o my-disk.exe

run: my-disk.exe
	./my-disk.exe

clean:
	rm -f *.o
	rm -f *.exe
	rm -f *.txt