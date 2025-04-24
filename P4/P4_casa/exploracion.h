// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estrucutras de Datos Avanzadas
// Curso: 2º
// Práctica 4
// Autor: Diego García Hernández
// Correo: alu0101633732@ull.edu.es
// Fecha: 27/03/2025
// Archivo exploracion.h
// Descripción: contiene la clase exploracion

#ifndef EXPLORACION_H_
#define EXPLORACION_H_

// Clase base abstracta para la función de exploración
template <class Key>
class ExplorationFunction {
 public:
  //metodo virtual
  virtual unsigned operator()(const Key&, unsigned) const = 0;
  //destructor virtual
  virtual ~ExplorationFunction() {}
};

// Exploración lineal
template <class Key>
class LinearExploration : public ExplorationFunction<Key> {
 public:
  //operador() heredado de la clase ExplorationFunction
  inline unsigned operator()(const Key&, unsigned i) const override {return i;}
};

#endif