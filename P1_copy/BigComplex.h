// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estrucutras de Datos Avanzadas
// Curso: 2º
// Práctica 1
// Autor: Diego García Hernández
// Correo: alu0101633732@ull.edu.es
// Fecha: 13/02/2025
// Archivo BigComplex.h
// Descripción: contiene la definición de la clase BigComplex


#ifndef BIGCOMPLEX_H_
#define BIGCOMPLEX_H_

#include <iostream>

#include "BigInteger.h"

//clase BigComplex
class BigComplex {
 public:
  BigComplex(const BigInteger&, const BigInteger&);
  BigComplex(int n = 0, int m = 0);
  BigComplex operator+(const BigComplex&);
  BigInteger GetReal() const { return parte_real_; }
  BigInteger GetImaginario() const { return parte_imaginaria_;}
 private:
  BigInteger parte_real_;
  BigInteger parte_imaginaria_;
};

std::ostream& operator<<(std::ostream&, const BigComplex&);

#endif