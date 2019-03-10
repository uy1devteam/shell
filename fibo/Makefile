
options= -Wall -Wextra
do : fibo
fonctions.o: fonctions.cpp header.h
	g++ -c ${options} -o fonctions.o fonctions.cpp 
main.o: main.cpp header.h 
	g++ -c ${options}  -o main.o  main.cpp  
fibo: main.o fonctions.o
	g++ -o fibo main.o fonctions.o
clean:
	rm -rf *.o
