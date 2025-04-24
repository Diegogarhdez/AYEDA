// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estrucutras de Datos Avanzadas
// Curso: 2º
// Práctica 4
// Autor: Diego García Hernández
// Correo: alu0101633732@ull.edu.es
// Fecha: 27/03/2025
// Archivo secuence.h
// Descripción: contiene la clase secuence

#ifndef SECUENCE_H_
#define SECUENCE_H_

#include <algorithm>

//clase secuence
template <class Key>
class Sequence {
 public:
  //metodos virtuales de la clase
  virtual bool search(const Key&) const = 0;
  virtual bool insert(const Key&) = 0;
  virtual ~Sequence() {}
};

// Secuencia dinámica para dispersión abierta
template <class Key>
class dynamicSequence : public Sequence<Key> {
 public:
  //constructor parametrizado por defecto
  dynamicSequence() : data() {}
  //metodo search
  bool search(const Key& k) const override {
    return std::find(data.begin(), data.end(), k) != data.end();
  }
  //metodo insert
  bool insert(const Key& k) override {
    if (!search(k)) {
      data.push_back(k);
      return true;
    }
    return false;
  }

 private:
  std::list<Key> data;
};

// Secuencia estática para dispersión cerrada
template <class Key, unsigned blockSize>
class staticSequence : public Sequence<Key> {
 public:
  //constructor parametrizado por defecto
  staticSequence() : count(0) {}
  //metodo search
  bool search(const Key& k) const override {
    for (unsigned i = 0; i < count; ++i) {
      if (data[i] == k) return true;
    }
    return false;
  }
  //metodo insertar 
  bool insert(const Key& k) override {
    if (count < blockSize && !search(k)) {
      data[count++] = k;
      return true;
    }
    return false;
  }
  //metodo para comprobar si esta llena la secuencia
  bool isFull() const { return count == blockSize; }

 private:
  Key data[blockSize];
  unsigned count;
};

#endif