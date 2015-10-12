#!/bin/bash

cat << _end_ | gnuplot
set terminal postscript eps color
set output "ajustes"
set key right bottom
set xlabel "Numero de elementos"
set ylabel "Tiempos (microsegundos)"
plot 'Datos.txt' using 1:2 t "Tiempo Medio Insercion" w l, 'Datos.txt' using 1:3 t "Tiempo Estimado Insercion" w l, 'Datos.txt' using 1:4 t "Tiempo Medio Shell" w l, 'Datos.txt' using 1:5 t "Tiempo Estimado Shell" w l
set output "ajusteInsercionBinaria"
plot 'Datos.txt' using 1:2 t "Tiempo Medio Insercion" w l, 'Datos.txt' using 1:3 t "Tiempo Estimado Insercion" w l
set output "ajusteShell"
plot 'Datos.txt' using 1:4 t "Tiempo Medio Shell" w l, 'Datos.txt' using 1:5 t "Tiempo Estimado Shell" w l
_end_
