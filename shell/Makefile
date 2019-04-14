OBJECTS= main.o env.o commande.o commandes.o fonctions.o number.o names.o histo.o
LIB= -lreadline -lgmp -lgmpxx
CFLAGS= -Wall -Wextra -g -c 
CPP= g++
do : shell
%.o: %.cpp %.hpp header.hpp
	$(CPP) $(CFLAGS)  $< -o $@  
shell: ${OBJECTS}
	g++ -o shell ${OBJECTS} ${LIB} 
clean:
	rm -rf *.o