all: casos_Practica1 test_oraculo tiempos

tiempos: tiempos.cpp Practica1.o
	g++ tiempos.cpp Practica1.o -o tiempos

casos_Practica1: casos_Practica1.cpp Practica1.o
	g++ casos_Practica1.cpp Practica1.o -o casos_Practica1

test_oraculo: test_oraculo.cpp Practica1.o
	g++ test_oraculo.cpp Practica1.o -o test_oraculo

Practica1.o: Practica1.cpp Practica1.h
	g++ -c Practica1.cpp

clean:
	rm -f *.o casos_Practica1 test_oraculo tiempos *.exe *.pdf *.csv