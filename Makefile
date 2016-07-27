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
	firefox https://github.com/kaleemullah360/file-system-c &

view-profile:
	firefox https://github.com/kaleemullah360 &
	
ifeq ($(c),)
 c = 'updates'
endif

push:
	git add -A
	git commit -m $(c)
	git push origin master

pull:
	git pull origin master

setup-project:
	sudo bash ./runonce.sh