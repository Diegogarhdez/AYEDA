// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estrucutras de Datos Avanzadas
// Curso: 2º
// Práctica 1
// Autor: Diego García Hernández
// Correo: alu0101633732@ull.edu.es
// Fecha: 13/02/2025
// Archivo BigUnsigned.h
// Descripción: contiene la clase BigUnsigned


#ifndef BIGUNSIGNED_H_
#define BIGUNSIGNED_H_

#include <iostream>
#include <vector>

//clase BigUnsigned
class BigUnsigned {
 public:
  BigUnsigned(unsigned n = 0);
  BigUnsigned(const unsigned char* );
  BigUnsigned(const BigUnsigned&);

  //operadores
  BigUnsigned& operator=(const BigUnsigned&);
  bool operator==(const BigUnsigned&) const;
  bool operator<(const BigUnsigned&) const;
  BigUnsigned& operator++(); // Pre-incremento
  BigUnsigned operator++(int); // Post-incremento
  BigUnsigned& operator--(); // Pre-decremento
  BigUnsigned operator--(int); // Post-decremento
  BigUnsigned operator%(const BigUnsigned&) const;
  BigUnsigned operator-(const BigUnsigned&) const;
  BigUnsigned operator*(const BigUnsigned&) const;
  BigUnsigned operator+(const BigUnsigned&) const;
  BigUnsigned operator/(const BigUnsigned&) const;

  //getters y setters
  inline std::vector<unsigned char> GetNumerin() const { return numerin_;}
  inline std::vector<unsigned char> GetNumerin() { return numerin_;}
  inline void SetNumerin(const std::vector<unsigned char> otro) {numerin_ = otro;}
 private:
  std::vector<unsigned char> numerin_;
};

std::ostream& operator<<(std::ostream&, const BigUnsigned&);
std::istream& operator>>(std::istream&, BigUnsigned&);


#endif