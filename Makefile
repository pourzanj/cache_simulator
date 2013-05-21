all:
	gcc -g cachesim.c main.c
clean:
	rm -rf a.out
test:
	./a.out
submit:
	./submit.sh
