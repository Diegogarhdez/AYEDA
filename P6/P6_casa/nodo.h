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

#include "nif.h"

template <class Key>
class NodoB {
 public:
  // Constructor
  NodoB(const Key dat, NodoB<Key>* izq = nullptr, NodoB<Key>* der = nullptr)
      : dato(dat), izdo(izq), dcho(der) {}

  // Destructor (virtual por si se hereda)
  virtual ~NodoB() {}

  Key getDato() const { return dato; }

  // Getters y setters clásicos
  NodoB<Key>* getIzdo() const { return izdo; }
  NodoB<Key>* getDcho() const { return dcho; }
  void setIzdo(NodoB<Key>* i) { izdo = i; }
  void setDcho(NodoB<Key>* d) { dcho = d; }

  // Referencias para modificar punteros en ABB/AVL
  NodoB<Key>*& getIzdoRef() { return izdo; }
  NodoB<Key>*& getDchoRef() { return dcho; }

  void setDato(const Key& d) { dato = d; }
  // Miembros (protegidos para acceso desde clases derivadas)
 protected:
  Key dato;
  NodoB<Key>* izdo;
  NodoB<Key>* dcho;

  // Amistad para que las clases de Árbol puedan acceder
  template <class T>
  friend class AB;
  template <class T>
  friend class ABB;
  template <class T>
  friend class AVL;  // AVL necesita acceder a izdo/dcho
};

template <class Key>
class NodoAVL : public NodoB<Key> {
 public:
  // Constructor
  NodoAVL(const Key dat, NodoAVL<Key>* iz = nullptr, NodoAVL<Key>* de = nullptr)
      : NodoB<Key>(dat, iz, de), bal(0) {}  // Llama al constructor base

  // Destructor
  ~NodoAVL() {}
  int GetBal() const { return bal;}
  // Miembro adicional (privado con getter/setter o protegido)
 protected:
  int bal;  // Factor de balanceo

  // Amistad para que la clase AVL pueda acceder/modificar bal
  template <class T>
  friend class AVL;
};

#endif