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

#include "ABB.h"
#include "nif.h"
#include "nodo.h"

#ifndef AVL_H_
#define AVL_H_

template <class Key>
class AVL : public ABB<Key> {  // Deriva de ABB
 public:
  // Constructor y destructor heredados
  AVL(bool modo_traza = false) : ABB<Key>(), traza(modo_traza) {}

  // Redefinición de insertar para incluir balanceo
  bool insertar(const Key& k) override {
    if (this->buscar(k)) {
      return false;  // No se permiten duplicados
    }
    NodoAVL<Key>* nuevo_nodo = new NodoAVL<Key>(k);  // Crea un NodoAVL
    bool crece = false;
    return inserta_bal(reinterpret_cast<NodoAVL<Key>*&>(this->raiz), nuevo_nodo,
                       crece);
  }

  bool buscar(const Key& k) const override {
    return buscarAVL(reinterpret_cast<NodoAVL<Key>*>(this->raiz), k) != nullptr;
  }

 private:
  bool traza;

  // Métodos de Rotación
  void rotacion_II(NodoAVL<Key>*& nodo) {
    NodoAVL<Key>* nodo1 = static_cast<NodoAVL<Key>*>(nodo->getIzdo());
    nodo->setIzdo(nodo1->getDcho());
    nodo1->setDcho(nodo);
    if (nodo1->bal == 1) {
      nodo->bal = 0;
      nodo1->bal = 0;
    } else {  // nodo1->bal == 0
      nodo->bal = 1;
      nodo1->bal = -1;
    }
    nodo = nodo1;
  }

  void rotacion_DD(NodoAVL<Key>*& nodo) {
    NodoAVL<Key>* nodo1 = static_cast<NodoAVL<Key>*>(nodo->getDcho());
    nodo->setDcho(nodo1->getIzdo());
    nodo1->setIzdo(nodo);
    if (nodo1->bal == -1) {
      nodo->bal = 0;
      nodo1->bal = 0;
    } else {  // nodo1->bal == 0
      nodo->bal = -1;
      nodo1->bal = 1;
    }
    nodo = nodo1;
  }

  void rotacion_ID(NodoAVL<Key>*& nodo) {
    NodoAVL<Key>* nodo1 = static_cast<NodoAVL<Key>*>(nodo->getIzdo());
    NodoAVL<Key>* nodo2 = static_cast<NodoAVL<Key>*>(nodo1->getDcho());
    nodo->setIzdo(nodo2->getDcho());
    nodo2->setDcho(nodo);
    nodo1->setDcho(nodo2->getIzdo());
    nodo2->setIzdo(nodo1);
    if (nodo2->bal == -1)
      nodo1->bal = 1;
    else
      nodo1->bal = 0;
    if (nodo2->bal == 1)
      nodo->bal = -1;
    else
      nodo->bal = 0;
    nodo2->bal = 0;
    nodo = nodo2;
  }

  void rotacion_DI(NodoAVL<Key>*& nodo) {
    NodoAVL<Key>* nodo1 = static_cast<NodoAVL<Key>*>(nodo->getDcho());
    NodoAVL<Key>* nodo2 = static_cast<NodoAVL<Key>*>(nodo1->getIzdo());
    nodo->setDcho(nodo2->getIzdo());
    nodo2->setIzdo(nodo);
    nodo1->setIzdo(nodo2->getDcho());
    nodo2->setDcho(nodo1);
    if (nodo2->bal == 1)
      nodo1->bal = -1;
    else
      nodo1->bal = 0;
    if (nodo2->bal == -1)
      nodo->bal = 1;
    else
      nodo->bal = 0;
    nodo2->bal = 0;
    nodo = nodo2;
  }

  // Métodos de Inserción y Rebalanceo
  bool inserta_bal(NodoAVL<Key>*& nodo, NodoAVL<Key>* nuevo, bool& crece) {
    if (nodo == nullptr) {
      nodo = nuevo;
      crece = true;
      return true;
    }

    bool insertado = false;

    if (nuevo->getDato() < nodo->getDato()) {
      NodoAVL<Key>*& izdo = reinterpret_cast<NodoAVL<Key>*&>(nodo->getIzdoRef());
      insertado = inserta_bal(izdo, nuevo, crece);
      if (crece) insert_re_balancea_izda(nodo, crece);
    } else if (nuevo->getDato() > nodo->getDato()) {
      NodoAVL<Key>*& dcho = reinterpret_cast<NodoAVL<Key>*&>(nodo->getDchoRef());
      insertado = inserta_bal(dcho, nuevo, crece);
      if (crece) insert_re_balancea_dcha(nodo, crece);
    }

    return insertado;
  }

  void insert_re_balancea_izda(NodoAVL<Key>*& nodo, bool& crece) {
    switch (nodo->bal) {
      case -1:
        nodo->bal = 0;
        crece = false;
        break;
      case 0:
        nodo->bal = 1;
        break;
      case 1:  // Se desbalancea hacia la izquierda
        if (traza) mostrar_desbalanceo("II o ID", nodo);
        NodoAVL<Key>* nodo1 = static_cast<NodoAVL<Key>*>(nodo->getIzdo());
        if (nodo1->bal == 1) {  // Rotación II
          rotacion_II(nodo);
        } else {  // Rotación ID (nodo1->bal == -1)
          rotacion_ID(nodo);
        }
        crece = false;  // La altura no cambia después de rotar
        break;
    }
  }

  void insert_re_balancea_dcha(NodoAVL<Key>*& nodo, bool& crece) {
    switch (nodo->bal) {
      case 1:
        nodo->bal = 0;
        crece = false;
        break;
      case 0:
        nodo->bal = -1;
        break;
      case -1:  // Se desbalancea hacia la derecha
        if (traza) mostrar_desbalanceo("DD o DI", nodo);
        NodoAVL<Key>* nodo1 = static_cast<NodoAVL<Key>*>(nodo->getDcho());
        if (nodo1->bal == -1) {  // Rotación DD
          rotacion_DD(nodo);
        } else {  // Rotación DI (nodo1->bal == 1)
          rotacion_DI(nodo);
        }
        crece = false;  // La altura no cambia después de rotar
        if (traza) imprimir_con_balanceo();
        break;
    }
  }

  // Método Auxiliar para Traza
  void mostrar_desbalanceo(const std::string& tipo_rotacion,
                           NodoAVL<Key>* nodo_desbalanceado) {
    std::cout << "\n------------------------------------\n";
    std::cout << "Desbalanceo detectado en nodo [" << nodo_desbalanceado->dato
              << "]\n";
    std::cout << "Árbol ANTES de la rotación (" << tipo_rotacion
              << " necesaria):\n";
    imprimir_con_balanceo();
    std::cout << "Aplicando rotación " << tipo_rotacion << " en nodo ["
              << nodo_desbalanceado->dato << "]...\n";
    std::cout << "------------------------------------\n";
  }

  // Función auxiliar hipotética para imprimir con balance
  void imprimir_con_balanceo() const {
    std::cout
        << "(Visualización con balanceo no implementada en este ejemplo)\n";
    std::queue<std::pair<NodoAVL<Key>*, int>> Q;
    NodoAVL<Key>* nodo_actual;
    int nivel, nivel_actual = 0;

    std::cout << "Recorrido por Niveles (con Balanceo):" << std::endl;
    if (this->raiz == nullptr) {  // Acceder a raiz de la clase base
      std::cout << "Nivel 0: [.]" << std::endl;
      return;
    }

    // Empezar con la raíz casteada a NodoAVL*
    Q.push({static_cast<NodoAVL<Key>*>(this->raiz), 0});
    std::cout << "Nivel 0: ";

    while (!Q.empty()) {
      std::pair<NodoAVL<Key>*, int> par = Q.front();
      Q.pop();
      nodo_actual = par.first;
      nivel = par.second;

      if (nivel > nivel_actual) {
        nivel_actual = nivel;
        std::cout << std::endl << "Nivel " << nivel_actual << ": ";
      }

      if (nodo_actual != nullptr) {
        std::cout << "[" << nodo_actual->dato << "(" << nodo_actual->bal
                  << ")] ";
        Q.push({static_cast<NodoAVL<Key>*>(nodo_actual->getIzdo()), nivel + 1});
        Q.push({static_cast<NodoAVL<Key>*>(nodo_actual->getDcho()), nivel + 1});
      } else {
        std::cout << "[.] ";
      }
    }
    std::cout << std::endl;
  }

  NodoAVL<Key>* buscarAVL(NodoAVL<Key>* nodo, const Key& clave_dada) const {
    if (!nodo) return nullptr;
    if (clave_dada == nodo->getDato()) return nodo;
    if (clave_dada < nodo->getDato())
      return buscarAVL(static_cast<NodoAVL<Key>*>(nodo->getIzdo()), clave_dada);
    else
      return buscarAVL(static_cast<NodoAVL<Key>*>(nodo->getDcho()), clave_dada);
  }
};

#endif