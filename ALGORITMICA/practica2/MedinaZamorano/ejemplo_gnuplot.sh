#!/bin/bash

cat << _end_ | gnuplot
set terminal postscript eps color
set output "ajustes"
set key right bottom
set xlabel "Orden Matriz"
set ylabel "Tiempos (microsegundos)"
plot 'Datos.txt' using 1:2 t "Tiempo Medio Iterativo" w l, 'Datos.txt' using 1:3 t "Tiempo Estimado Iterativo" w l, 'Datos.txt' using 1:4 t "Tiempo Medio Recursivo" w l, 'Datos.txt' using 1:5 t "Tiempo Estimado Recursivo" w l
set output "ajusteIterativo"
plot 'Datos.txt' using 1:2 t "Tiempo Medio Iterativo" w l, 'Datos.txt' using 1:3 t "Tiempo Estimado Iterativo" w l
set output "ajusteRecursivo"
plot 'Datos.txt' using 1:4 t "Tiempo Medio Recursivo" w l, 'Datos.txt' using 1:5 t "Tiempo Estimado Recursivo" w l
_end_
