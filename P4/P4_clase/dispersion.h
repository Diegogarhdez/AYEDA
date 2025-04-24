// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estrucutras de Datos Avanzadas
// Curso: 2º
// Práctica 4
// Autor: Diego García Hernández
// Correo: alu0101633732@ull.edu.es
// Fecha: 27/03/2025
// Archivo dispersion.h
// Descripción: contiene la clase dispersion


#ifndef DISPERSION_H_
#define DISPERSION_H_

// Clase base abstracta para la función de dispersión
template <class Key>
class DispersionFunction {
 public:
  //operador virtual
  virtual unsigned operator()(const Key&) const = 0;
  //destructor virtual
  virtual ~DispersionFunction() {}
};

// Función de dispersión por módulo
template <class Key>
class ModuloFunction : public DispersionFunction<Key> {
 public:
  //constructor parametrizado
  ModuloFunction(unsigned size) : tableSize(size) {}
  // operador() heredado
  inline unsigned operator()(const Key& k) const override { return static_cast<unsigned>(k) % tableSize;}
 private:  
  unsigned tableSize;
};


#endif