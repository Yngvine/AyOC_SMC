: cmpSimulador cmpTraza cmpCola

cmpSimulador: cmpCola
  gcc SimuladorCache.c colaDirecciones.o -o SimuladorCache -Wall

cmpCola:
  gcc colaDirecciones.c -c -Wall

cmpTraza: creaTrazaTXT.c
  gcc creaTrazaTXT.c -o creaTrazaTXT -Wall
