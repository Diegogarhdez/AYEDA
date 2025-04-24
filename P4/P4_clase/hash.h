// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estrucutras de Datos Avanzadas
// Curso: 2º
// Práctica 4
// Autor: Diego García Hernández
// Correo: alu0101633732@ull.edu.es
// Fecha: 27/03/2025
// Archivo hash.h
// Descripción: contiene la clase HashTable

#ifndef HASH_H_
#define HASH_H_

#include "dispersion.h"
#include "exploracion.h"
#include "secuence.h"

#define DISABLE_COPY_AND_ASSIGN(Class) \
  Class(const Class&) = delete;        \
  Class& operator=(const Class&) = delete;

//clase HashTable  
template <class Key, class Container = staticSequence<Key, 5>>
class HashTable {
  DISABLE_COPY_AND_ASSIGN(HashTable)
 public:
  //constructor parametrizado
  HashTable(unsigned size, DispersionFunction<Key>& dispFunc,
            ExplorationFunction<Key>& expFunc, unsigned bSize = 5)
      : tableSize(size),
        table(new Container*[size]),
        blockSize(bSize),
        fd(dispFunc),
        fe(expFunc) {  
    for (unsigned i = 0; i < tableSize; ++i) {
      table[i] = new Container();
    }
  }
  //destructor para liberar la memoria
  ~HashTable() {
    for (unsigned i = 0; i < tableSize; ++i) delete table[i];
    delete[] table;
  }

  //metodo para insertar un elemento en la tabla hash
  bool insert(const Key& k) {
    unsigned pos = fd(k);
    unsigned i = 0;
    while (i < tableSize) {
      unsigned newPos = (pos + fe(k, i)) % tableSize;
      if (table[newPos]->insert(k)) return true;
      if constexpr (std::is_base_of_v<staticSequence<Key, 5>, Container>) {
        if (table[newPos]->isFull()) return false;
      }
      ++i;
    }
    return false;
  }

  //metodo para buscar dentro de la tabla hash
  bool search(const Key& k) const {
    unsigned pos = fd(k);
    unsigned i = 0;
    while (i < tableSize) {
      unsigned newPos = (pos + fe(k, i)) % tableSize;
      if (table[newPos]->search(k)) return true;
      ++i;
    }
    return false;
  }

 private:
  unsigned tableSize;
  Container** table;
  DispersionFunction<Key>& fd;
  ExplorationFunction<Key>& fe;
  unsigned blockSize;
};

#endif