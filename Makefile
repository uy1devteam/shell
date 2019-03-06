
options= -Wall -Wextra
do : exe
fonctions.o: fonctions.cpp header.h
	g++ -c ${options} -o fonctions.o -c fonctions.cpp 
main.o: main.cpp header.h 
	g++ -c ${options}  -o main.o  main.cpp  
exe: main.o fonctions.o
	g++ -o exe main.o fonctions.o
clean:
	rm -rf *.o
