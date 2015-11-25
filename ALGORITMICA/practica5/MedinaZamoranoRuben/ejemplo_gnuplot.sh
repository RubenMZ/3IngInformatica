#!/bin/bash

cat << _end_ | gnuplot
set terminal postscript eps color
set output "cambios"
set key right bottom
set xlabel "Cambio (cents)"
set ylabel "Tiempos (microsegundos)"
plot 'tiemposGuardados.txt' using 1:2 t "Tiempos AlgoritmoVoraz" w l, 'tiemposGuardados.txt' using 1:3 t "Tiempos AlgoritmoDinamico" w l
set output "cambioVoraz"
plot 'tiemposGuardados.txt' using 1:2 t "Tiempos AlgoritmoVoraz" w l
set output "cambioDinamico"
plot 'tiemposGuardados.txt' using 1:3 t "Tiempos AlgoritmoDinamico" w l
_end_
