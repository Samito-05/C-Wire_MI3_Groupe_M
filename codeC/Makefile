all : c-wire 

code.o: ./main.c ./station.h
	@echo "Compilation of the main code"
	@gcc $(CFLAGS) -c ./main.c -o code.o

station.o: ./station.c ./station.h
	@echo "Compilation of the station code"
	@gcc $(CFLAGS) -c ./station.c -o station.o

c-wire: station.o code.o
	@echo "Final compilation"
	@gcc $(CFLAGS) station.o code.o -o c-wire


empty:
	@echo "Deleting files"
	@rm -f *.o
	@rm c-wire
