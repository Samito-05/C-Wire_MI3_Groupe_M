all : prg 

prg: station.o code.o
	@echo "Final compilation"
	@gcc $(CFLAGS) station.o code.o -o prg

code.o: main.c station.h
	@echo "Compilation of the main code"
	@gcc $(CFLAGS) -c main.c

station.o: station.c station.h
	@echo "Compilation of the station code"
	@gcc $(CFLAGS) -c station.c 


empty:
	@echo "Deleting files"
	@rm -f *.o
	@rm prg