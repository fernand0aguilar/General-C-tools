main: main.o libseno.so
	 gcc -o main main.o -L. -lseno -Wl,-rpath,./

main.o: main.c libseno.h
	gcc -c main.c

libseno.so: libseno.o
	gcc -shared -fPIC -o libseno.so libseno.o

libseno.o: libseno.c
	gcc -fPIC -o libseno.o -c libseno.c

clean:
	rm -f *.o
	rm libseno.so main
