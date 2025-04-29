// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estrucutras de Datos Avanzadas
// Curso: 2º
// Práctica 6
// Autor: Diego García Hernández
// Correo: alu0101633732@ull.edu.es
// Fecha: 30/04/2025
// Archivo ABB.h
// Descripción: contiene la clase ABB y AB

#ifndef ABB_H_
#define ABB_H_

#include <queue>

#include "nif.h"
#include "nodo.h"

template <class Key>
class AB {
 public:
  // Constructor
  AB() : raiz(nullptr) {}

  // Destructor
  virtual ~AB() { Podar(raiz); }

  // Métodos Virtuales
  virtual bool insertar(const Key& k) = 0;
  virtual bool buscar(const Key& k) const = 0;
  virtual bool eliminar(const Key& k) = 0;  // Opcional

  bool EsVacio() const { return raiz == nullptr; }

  void inorden() const {
    std::cout << "Recorrido Inorden: ";
    inordenRama(raiz);
    std::cout << std::endl;
  }

  // Sobrecarga del operador << para recorrido por niveles
  friend std::ostream& operator<<(std::ostream& os, const AB<Key>& arbol) {
    arbol.recorreN(os);
    return os;
  }

 protected:
  // Atributo raíz
  NodoB<Key>* raiz;

  // Métodos Auxiliares Protegidos
  void Podar(NodoB<Key>*& nodo) {
    if (nodo == nullptr) return;
    Podar(nodo->getIzdoRef());
    Podar(nodo->getDchoRef());
    delete nodo;
    nodo = nullptr;
  }

  bool EsHoja(const NodoB<Key>* nodo) const {
    return nodo != nullptr && nodo->getDcho() == nullptr &&
           nodo->getIzdo() == nullptr;
  }

  int TamRama(const NodoB<Key>* nodo) const {
    if (!nodo) return 0;
    return 1 + TamRama(nodo->getIzdo()) + TamRama(nodo->getDcho());
  }

  int AltN(const NodoB<Key>* nodo) const {
    if (nodo == nullptr) return 0;
    int alt_i = AltN(nodo->getIzdo());
    int alt_d = AltN(nodo->getDcho());
    return 1 + std::max(alt_i, alt_d);
  }

  // Recorrido Inorden Recursivo
  void inordenRama(NodoB<Key>* nodo) const {
    if (nodo == nullptr) return;
    inordenRama(nodo->getIzdo());
    std::cout << "[" << nodo->dato
              << "] ";  // Asumiendo que Key tiene sobrecargado <<
    inordenRama(nodo->getDcho());
  }

  // Recorrido por Niveles
  void recorreN(std::ostream& os) const {
    std::queue<std::pair<NodoB<Key>*, int>> Q;
    NodoB<Key>* nodo_actual;
    int nivel, nivel_actual = 0;

    os << "Recorrido por Niveles:" << std::endl;
    if (raiz == nullptr) {
      os << "Nivel 0: [.]" << std::endl;
      return;
    }

    Q.push({raiz, 0});
    os << "Nivel 0: ";

    while (!Q.empty()) {
      std::pair<NodoB<Key>*, int> par = Q.front();
      Q.pop();
      nodo_actual = par.first;
      nivel = par.second;

      if (nivel > nivel_actual) {
        nivel_actual = nivel;
        os << std::endl << "Nivel " << nivel_actual << ": ";
      }

      if (nodo_actual != nullptr) {
        os << "[" << nodo_actual->dato;  // Imprimir dato
        if (const NodoAVL<Key>* nodoAVL =
                dynamic_cast<const NodoAVL<Key>*>(nodo_actual)) {
          os << "(" << nodoAVL->GetBal() << ")";
        }
        os << "] ";
        Q.push({nodo_actual->getIzdo(), nivel + 1});
        Q.push({nodo_actual->getDcho(), nivel + 1});
      } else {
        os << "[.] ";
      }
    }
    os << std::endl;
  }

  virtual void Procesar(NodoB<Key>* nodo) const {
    std::cout << nodo->dato << " ";
  }
};

template <class Key>
class ABB : public AB<Key> {
 public:
  // Hereda constructor y destructor de AB

  // Implementación de métodos virtuales
  bool insertar(const Key& k) override {
    // Si ya existe, no inserta y devuelve false
    if (buscar(k)) {
      return false;
    }
    return insertarRama(this->raiz, k); 
  }

  bool buscar(const Key& k) const override {
    return buscarRama(this->raiz, k) != nullptr;
  }

  // Implementación de eliminar (opcional)
  bool eliminar(const Key& k) override { return eliminarRec(this->raiz, k); }

  bool eliminarRec(NodoB<Key>*& nodo, const Key& k) {
    if (!nodo) return false;

    if (k < nodo->getDato()) {
      return eliminarRec(nodo->getIzdoRef(), k);
    } else if (k > nodo->getDato()) {
      return eliminarRec(nodo->getDchoRef(), k);
    } else {  // Nodo encontrado
      if (!nodo->getIzdo() && !nodo->getDcho()) {
        delete nodo;
        nodo = nullptr;
      } else if (!nodo->getIzdo()) {
        NodoB<Key>* temp = nodo;
        nodo = nodo->getDcho();
        delete temp;
      } else if (!nodo->getDcho()) {
        NodoB<Key>* temp = nodo;
        nodo = nodo->getIzdo();
        delete temp;
      } else {
        NodoB<Key>* sucesor = minimo(nodo->getDcho());
        nodo->dato = sucesor->getDato();
        eliminarRec(nodo->getDchoRef(), sucesor->getDato());
      }
      return true;
    }
  }

  NodoB<Key>* minimo(NodoB<Key>* nodo) const {
    while (nodo->getIzdo()) nodo = nodo->getIzdo();
    return nodo;
  }

 protected:
  NodoB<Key>* buscarRama(NodoB<Key>* nodo, const Key& clave_dada) const {
    if (!nodo) return nullptr;

    if (clave_dada == nodo->getDato()) return nodo;

    if (clave_dada < nodo->getDato())
      return buscarRama(nodo->getIzdo(), clave_dada);

    return buscarRama(nodo->getDcho(), clave_dada);
  }

  bool insertarRama(NodoB<Key>*& nodo, const Key& clave_dada) {
    if (!nodo) {
      nodo = new NodoB<Key>(clave_dada);
      return true;
    }

    if (clave_dada < nodo->getDato()) {
      return insertarRama(nodo->getIzdoRef(), clave_dada);
    }

    if (clave_dada > nodo->getDato()) {
      return insertarRama(nodo->getDchoRef(), clave_dada);
    }

    return false;  // clave ya existe
  }
};

#endif