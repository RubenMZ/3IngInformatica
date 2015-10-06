#!/bin/bash

cat << _end_ | gnuplot
set terminal postscript eps color
set output "ajustes.eps"
set key right bottom
set xlabel "Numero de elementos"
set ylabel "Tiempos (microsegundos)"
plot 'Datos2.txt' using 1:2 t "Tiempo Medio Insercion" w l, 'Datos2.txt' using 1:3 t "Tiempo Estimado Insercion" w l, 'Datos2.txt' using 1:4 t "Tiempo Medio Shell" w l, 'Datos2.txt' using 1:5 t "Tiempo Estimado Shell" w l
_end_
