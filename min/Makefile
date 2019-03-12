
options= -Wall -Wextra
do : min
fonctions.o: fonctions.cpp header.h
	g++ -c ${options} -o fonctions.o fonctions.cpp 
main.o: main.cpp header.h 
	g++ -c ${options}  -o main.o  main.cpp  
min: main.o fonctions.o
	g++ -o min main.o fonctions.o
clean:
	rm -rf *.o
