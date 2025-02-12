// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estrucutras de Datos Avanzadas
// Curso: 2º
// Práctica 1
// Autor: Diego García Hernández
// Correo: alu0101633732@ull.edu.es
// Fecha: 13/02/2025
// Archivo BigInteger.h
// Descripción: contiene la clase BigInteger

#ifndef BIGINTEGER_H_
#define BIGINTEGER_H_

#include <iostream>
#include <vector>

#include "BigUnsigned.h"

class BigInteger {
 public:
  BigInteger(int n = 0);
  BigInteger(const BigUnsigned&);
  BigInteger(const BigInteger& otro);

  BigInteger operator+(const BigInteger&) const;
  BigInteger operator-(const BigInteger&) const;
  BigInteger operator/(const BigInteger&) const;
  BigInteger operator*(const BigInteger&) const;
  BigInteger operator%(const BigInteger&) const;
  BigInteger& operator++(); //pre-incremento
  BigInteger operator++(int); //post-incremento
  BigInteger& operator--(); //pre-incremento
  BigInteger operator--(int); //post-incremento
  BigInteger& operator=(const BigInteger&);
  bool operator==(const BigInteger&) const;
  bool operator<(const BigInteger&) const;

  inline BigUnsigned GetNumero() const { return numero_; }
  inline bool GetSigno() const { return signo_; }
  inline void SetNumero(const BigUnsigned& otro) { numero_ = otro; }
  inline void SetSigno(const bool& otro_signo) { signo_ = otro_signo; }
 private:
  BigUnsigned numero_;
  bool signo_;
};
 
std::ostream& operator<<(std::ostream&, const BigInteger&);
std::istream& operator>>(std::istream&, BigInteger&);

BigInteger mcd(const BigInteger&, const BigInteger&);

#endif