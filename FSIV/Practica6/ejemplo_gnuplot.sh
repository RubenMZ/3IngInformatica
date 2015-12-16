#!/bin/bash

cat << _end_ | gnuplot
set terminal postscript eps color
set output "cambios3"
set key right bottom
set xlabel "Cambio (cents)"
set ylabel "Tiempos (microsegundos)"
plot 'salida.txt' w l
_end_
