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

template <typename Key>
class AB {
 public:
  AB() : raiz(nullptr) {}
  virtual ~AB() {}

  virtual bool insertar(const Key& k) = 0;
  virtual bool buscar(const Key& k) const = 0;
  void inorden() const {
    inordenRec(raiz);
    std::cout << std::endl;
  }

  friend std::ostream& operator<<(std::ostream& os, const AB<Key>& arbol) {
    arbol.imprimirNivel();
    return os;
  }

 protected:

  void inordenRec(NodoB<Key>* nodo) const {
    if (nodo) {
      inordenRec(nodo->getIzdo());
      std::cout << nodo->getDato() << " ";
      inordenRec(nodo->getDcho());
    }
  }

  void imprimirNivel() const {
    if (!raiz) {
      std::cout << "Nivel 0: [.] \n";
      return;
    }

    std::queue<NodoB<Key>*> q;
    q.push(raiz);
    int nivel = 0;

    while (!q.empty()) {
      int nivelSize = q.size();
      std::cout << "Nivel " << nivel++ << ": ";
      for (int i = 0; i < nivelSize; ++i) {
        NodoB<Key>* nodo = q.front();
        q.pop();
        if (nodo) {
          std::cout << "[" << nodo->getDato() << "] ";
          q.push(nodo->getIzdo());
          q.push(nodo->getDcho());
        } else {
          std::cout << "[.] ";
          q.push(nullptr);
          q.push(nullptr);
        }
      }
      std::cout << "\n";
      // Salimos si todos son nullptr
      if (std::all_of(q.front(), q.back(),
                      [](NodoB<Key>* n) { return n == nullptr; }))
        break;
    }
  }

 private:
  NodoB<Key>* raiz;
};

template <typename Key>
class ABB : public AB<Key> {
 public:
  bool insertar(const Key& k) override { return insertarRec(this->raiz, k); }
  bool buscar(const Key& k) const override { return buscarRec(this->raiz, k); }

 private:
  bool insertarRec(NodoB<Key>*& nodo, const Key& k) {
    if (!nodo) {
      nodo = new NodoB<Key>(k);
      return true;
    }
    if (k < nodo->getDato())
      return insertarRec(nodo->getIzdo(), k);
    else if (k > nodo->getDato())
      return insertarRec(nodo->getDcho(), k);
    else
      return false;
  }

  bool buscarRec(NodoB<Key>* nodo, const Key& k) const {
    if (!nodo) return false;
    if (k == nodo->getDato()) return true;
    if (k < nodo->getDato())
      return buscarRec(nodo->getIzdo(), k);
    else
      return buscarRec(nodo->getDcho(), k);
  }
};

template <typename Key>
class NodoAVL : public NodoB<Key> {
 public:
  NodoAVL(const Key& d, NodoAVL<Key>* i = nullptr, NodoAVL<Key>* dch = nullptr,
          int b = 0)
      : NodoB<Key>(d, i, dch), bal(b) {}

  int getBal() const { return bal; }
  void setBal(int b) { bal = b; }

 private:
  int bal;  // Factor de balanceo
};

#endif