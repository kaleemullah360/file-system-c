compile: my-disk.c
	gcc -Wall my-disk.c -o my-disk.exe

run: my-disk.exe
	./my-disk.exe

clean:
	rm -f *.o
	rm -f *.exe

clean-all:
	rm -f *.o
	rm -f *.exe
	rm -f *.txt

create-file:
	vim Sample.txt

view-project:
	firefox https://github.com/kaleemullah360/file-system-c

