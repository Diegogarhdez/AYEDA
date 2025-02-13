// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estrucutras de Datos Avanzadas
// Curso: 2º
// Práctica 1
// Autor: Diego García Hernández
// Correo: alu0101633732@ull.edu.es
// Fecha: 13/02/2025
// Archivo BigComplex.cc
// Descripción: contiene la implementación de la clase BigComplex


#include "BigComplex.h"

//constructor parametrizado con BigInteger
BigComplex::BigComplex(const BigInteger& real, const BigInteger& imaginario) : parte_real_(real), parte_imaginaria_(imaginario) { }

//constructor parametrizado con enteros
BigComplex::BigComplex(int n, int m) : parte_real_(BigInteger(n)), parte_imaginaria_(BigInteger(m)) { }

/**
 * @brief Esta función define el operador de suma para la clase BigComplex
 * @param complejo1 
 * @return retorna la suma de dos BigComplex
 */
BigComplex BigComplex::operator+(const BigComplex& complejo1) {
  return BigComplex(complejo1.GetReal() + parte_real_, complejo1.GetImaginario() + parte_imaginaria_);
}

/**
 * @brief Esta función define el operador de salida para la clase BigComplex
 * @param os 
 * @param complejo 
 * @return el número complejo por pantalla
 */
std::ostream& operator<<(std::ostream& os, const BigComplex& complejo) {
  os << complejo.GetReal() << " ";
  if (complejo.GetImaginario().GetSigno() == false) os << "+ ";
  os << complejo.GetImaginario() << "i";
  return os;
}
