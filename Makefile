all: cmpSimulador cmpTraza cmpCola

cmpSimulador: cmpCola
	gcc SimuladorCache.c colaDirecciones.o -o SimuladorCache -Wall

cmpCola:
	gcc colaDirecciones.c -c -Wall

cmpTraza:
	gcc creaTrazaTXT.c -o creaTrazaTXT -Wall
