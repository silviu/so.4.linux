CFLAGS= -fPIC -Wall -g

build:monitor.o rw.o
	gcc -shared monitor.o -o LibMonitor.so 	
	gcc -shared rw.o -o LibRW.so 

test:
	make -f Makefile.checker build-pre && make build && make -f Makefile.checker build-post && make -f Makefile.checker

clean:
	rm -rf monitor rw *.o *~ *.so Test _test/*.o
