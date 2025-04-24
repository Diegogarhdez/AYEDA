// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estrucutras de Datos Avanzadas
// Curso: 2º
// Práctica 6
// Autor: Diego García Hernández
// Correo: alu0101633732@ull.edu.es
// Fecha: 30/04/2025
// Archivo nodoB.h
// Descripción: contiene la clase nodoB

#ifndef NODOB_H_
#define NODOB_H_

template <typename Key>
class NodoB {
 public:
  NodoB(const Key& data, NodoB<Key>* i = nullptr, NodoB<Key>* d = nullptr)
      : dato(data), izdo(i), dcho(d) {}

  Key getDato() const { return dato; }
  NodoB<Key>* getIzdo() const { return izdo; }
  NodoB<Key>* getDcho() const { return dcho; }

  void setIzdo(NodoB<Key>* i) { izdo = i; }
  void setDcho(NodoB<Key>* d) { dcho = d; }

 protected:
  Key dato;
  NodoB<Key>* izdo;
  NodoB<Key>* dcho;
};

#endif