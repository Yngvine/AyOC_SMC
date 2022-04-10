# AyOC_SMC (Arquitectura y Organizacion de Computadores: Simulador de Memoria Cache)
### Igor Vons y Odei Tarragona
El programa se compila con archivo Makefile adjunto. Este compila el simulador con cmpSimulador,
compila la libreria auxiliar con cmpCola y compila el programa de generacion de trazas con cmpTraza.
Para compilar todos se puede asar all.

Para la ejecucion de SimuladorCache se tienen que encontrar en la misma carpeta el archivo de configuracion
(por defecto config.txt) y de trazas (por defecto traza.txt). Para ejecutar la simulacion basta con ./SimuladorCache 
. Se mostrara el resultado en el siguiente formato:


>>Accesos realizados
> 
>>Fallos encontrados
> 
>>Tasa de fallos

La libreria colaDiracciones es usada por SimuladorCache. Sus funcionalidades se detallan dentro de los archivos
SimuladorCache.c y colaDirecciones.h.
***
El programa creTrazaTXT se ejecuta simplemente ./creTrazaTXT y generara un traza.txt en la misma carpeta
en funcion de la opcion seleccionada del menu que aparecera.
