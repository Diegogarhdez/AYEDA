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

//clase persona
class Persona {
 public:
  //constructores
  Persona(const nif& NIF, const std::string& nombre, const int& edad) : NIF_(NIF), edad_(edad), nombre_(nombre) { }
  Persona(long v) : NIF_(v), edad_(0), nombre_("NombreGenerico") { }
  Persona() : NIF_(rand() % 100000000), edad_(0), nombre_("NombreGenerico") { }
  //getters
  nif GetNIF() const { return NIF_; }
  std::string GetNombre() const { return nombre_;}
  int GetEdad() const { return edad_; }
  //operador long para clase Persona
  operator long() const { return NIF_;}
  //operador de igualdad
  bool operator==(const Persona& persona) const { return NIF_ == persona.NIF_; }
 private:
  nif NIF_;
  std::string nombre_;
  int edad_;
};

//operador de salida para la clase persona
std::ostream& operator<<(std::ostream& os, const Persona& persona) {
  os << " NIF:" << persona.GetNIF() << ", Nombre:" << persona.GetNombre() << ", Edad:" << persona.GetEdad();
  return os;
}

#endif