all: main.o library.o album.o metadata.o
	gcc -o harmony -g main.o library.o album.o metadata.o -lavformat -lavutil -lavcodec -g

main.o: main.c library.c library.h album.c album.h metadata.c metadata.h
	gcc -c -g main.c 

library.o: library.c library.h album.c album.h metadata.c metadata.h
	gcc -c -g library.c

album.o: album.c album.h metadata.c metadata.h
	gcc -c -g album.c

metadata.o: metadata.c metadata.h
	gcc -c -g metadata.c

clean:
	@rm *.o *.exe *.gch || true