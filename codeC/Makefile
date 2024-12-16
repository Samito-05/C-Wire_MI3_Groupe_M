All : prg 

prg: code.o station.o 
	@echo "Final compilation"
	@gcc $(CFLAGS) code.o station.o -o prg

code.o: main.c station.h
	@echo "Compilation of the main code"
	@gcc $(CFLAGS) -c main.c 

station.o: sation.c station.h
	@echo "Compilation of the station code"
	@gcc $(CFLAGS) -c station.c 


vide:
	@echo "Deleting files"
	@rm -f *.o
	@rm prg