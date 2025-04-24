// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estrucutras de Datos Avanzadas
// Curso: 2º
// Práctica 4
// Autor: Diego García Hernández
// Correo: alu0101633732@ull.edu.es
// Fecha: 27/03/2025
// Archivo nif.h
// Descripción: contiene la clase nif

#ifndef NIF_H_
#define NIF_H_

#include <iostream>
#include <random>

// Tipo de dato nif
class nif {
public:
  //constructor aleatorio
  nif() : value(rand() % 100000000) {}
  //constructor con un valor ya generado
  nif(long v) : value(v) {}
  //operador de comparación de dos nif
  bool operator==(const nif& other) const { return value == other.value; }
  //operador long
  operator long() const { return value; }
 private: 
  long value;
};

#endif