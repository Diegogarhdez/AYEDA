// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estrucutras de Datos Avanzadas
// Curso: 2º
// Práctica 6
// Autor: Diego García Hernández
// Correo: alu0101633732@ull.edu.es
// Fecha: 30/04/2025
// Archivo AVL.h
// Descripción: contiene las clases relacionados con el AVL

#include <algorithm>
#include <iostream>
#include <queue>

#include "nodoB.h"
#include "ABB.h"

#ifndef AVL_H_
#define AVL_H_

template <typename Key>
class AVL : public ABB<Key> {
 public:
  AVL(bool traza_activada = false) : traza(traza_activada) {}

  bool insertar(const Key& k) override {
    bool crece = false;
    this->raiz = insertarAVL((NodoAVL<Key>*&)this->raiz, k, crece);
    return crece;
  }

 private:
  bool traza;

  NodoAVL<Key>* insertarAVL(NodoAVL<Key>*& nodo, const Key& k, bool& crece) {
    if (!nodo) {
      nodo = new NodoAVL<Key>(k);
      crece = true;
      return nodo;
    }

    if (k == nodo->getDato()) {
      crece = false;
      return nodo;
    }

    if (k < nodo->getDato()) {
      nodo->setIzdo(insertarAVL((NodoAVL<Key>*&)nodo->getIzdo(), k, crece));
      if (crece) nodo = balanceaIzquierda(nodo, crece);
    } else {
      nodo->setDcho(insertarAVL((NodoAVL<Key>*&)nodo->getDcho(), k, crece));
      if (crece) nodo = balanceaDerecha(nodo, crece);
    }

    return nodo;
  }

  NodoAVL<Key>* balanceaIzquierda(NodoAVL<Key>* nodo, bool& crece) {
    NodoAVL<Key>* izdo = (NodoAVL<Key>*)nodo->getIzdo();

    switch (nodo->getBal()) {
      case -1:
        nodo->setBal(0);
        crece = false;
        break;
      case 0:
        nodo->setBal(1);
        break;
      case 1:
        if (traza) mostrarTraza("II", nodo);
        if (izdo->getBal() == 1) {
          nodo = rotacionII(nodo);
        } else {
          nodo = rotacionID(nodo);
        }
        crece = false;
        break;
    }

    return nodo;
  }

  NodoAVL<Key>* balanceaDerecha(NodoAVL<Key>* nodo, bool& crece) {
    NodoAVL<Key>* dcho = (NodoAVL<Key>*)nodo->getDcho();

    switch (nodo->getBal()) {
      case 1:
        nodo->setBal(0);
        crece = false;
        break;
      case 0:
        nodo->setBal(-1);
        break;
      case -1:
        if (traza) mostrarTraza("DD", nodo);
        if (dcho->getBal() == -1) {
          nodo = rotacionDD(nodo);
        } else {
          nodo = rotacionDI(nodo);
        }
        crece = false;
        break;
    }

    return nodo;
  }

  NodoAVL<Key>* rotacionII(NodoAVL<Key>* nodo) {
    NodoAVL<Key>* izdo = (NodoAVL<Key>*)nodo->getIzdo();
    nodo->setIzdo(izdo->getDcho());
    izdo->setDcho(nodo);
    nodo->setBal(0);
    izdo->setBal(0);
    return izdo;
  }

  NodoAVL<Key>* rotacionDD(NodoAVL<Key>* nodo) {
    NodoAVL<Key>* dcho = (NodoAVL<Key>*)nodo->getDcho();
    nodo->setDcho(dcho->getIzdo());
    dcho->setIzdo(nodo);
    nodo->setBal(0);
    dcho->setBal(0);
    return dcho;
  }

  NodoAVL<Key>* rotacionID(NodoAVL<Key>* nodo) {
    NodoAVL<Key>* izdo = (NodoAVL<Key>*)nodo->getIzdo();
    NodoAVL<Key>* nuevo = (NodoAVL<Key>*)izdo->getDcho();

    izdo->setDcho(nuevo->getIzdo());
    nuevo->setIzdo(izdo);
    nodo->setIzdo(nuevo->getDcho());
    nuevo->setDcho(nodo);

    switch (nuevo->getBal()) {
      case 1:
        nodo->setBal(-1);
        izdo->setBal(0);
        break;
      case -1:
        nodo->setBal(0);
        izdo->setBal(1);
        break;
      case 0:
        nodo->setBal(0);
        izdo->setBal(0);
        break;
    }

    nuevo->setBal(0);
    return nuevo;
  }

  NodoAVL<Key>* rotacionDI(NodoAVL<Key>* nodo) {
    NodoAVL<Key>* dcho = (NodoAVL<Key>*)nodo->getDcho();
    NodoAVL<Key>* nuevo = (NodoAVL<Key>*)dcho->getIzdo();

    dcho->setIzdo(nuevo->getDcho());
    nuevo->setDcho(dcho);
    nodo->setDcho(nuevo->getIzdo());
    nuevo->setIzdo(nodo);

    switch (nuevo->getBal()) {
      case 1:
        nodo->setBal(0);
        dcho->setBal(-1);
        break;
      case -1:
        nodo->setBal(1);
        dcho->setBal(0);
        break;
      case 0:
        nodo->setBal(0);
        dcho->setBal(0);
        break;
    }

    nuevo->setBal(0);
    return nuevo;
  }

  void mostrarTraza(const std::string& tipo, NodoAVL<Key>* nodo) {
    std::cout << "Desbalanceo:\n" << *this;
    std::cout << "Rotación " << tipo << " en [" << nodo->getDato() << "("
              << nodo->getBal() << ")]:\n";
  }
};

#endif