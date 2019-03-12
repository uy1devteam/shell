
options= -Wall -Wextra
do : max
fonctions.o: fonctions.cpp header.h
	g++ -c ${options} -o fonctions.o fonctions.cpp 
main.o: main.cpp header.h 
	g++ -c ${options}  -o main.o  main.cpp  
max: main.o fonctions.o
	g++ -o max main.o fonctions.o
clean:
	rm -rf *.o
