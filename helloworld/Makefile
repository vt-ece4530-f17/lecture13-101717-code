hello: main.c
	arm-linux-gnueabihf-gcc -g -Wall main.c -o hello
	arm-linux-gnueabihf-objdump -D hello >hello.lst

clean:
	rm -f hello *.o *~ *.lst
