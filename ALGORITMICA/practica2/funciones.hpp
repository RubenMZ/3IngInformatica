#ifndef FUNCIONES_HPP
#define FUNCIONES_HPP

#include "matriz.hpp"


template <class T>
T determinanteIterativo (const Matriz <T> &m);

template <class T>
T determinanteRecursivo(const Matriz <T> &m);

template <class T>
void rellenaMatriz(const Matriz <T> &m, const int &fil, const int &col);