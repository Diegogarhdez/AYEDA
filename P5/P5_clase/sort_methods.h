// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estrucutras de Datos Avanzadas
// Curso: 2º
// Práctica 5
// Autor: Diego García Hernández
// Correo: alu0101633732@ull.edu.es
// Fecha: 10/04/2025
// Archivo sort_methods.h
// Descripción: contiene las clases correspondientes a los métodos de ordenación

#ifndef SORT_METHODS_H_
#define SORT_METHODS_H_

#include <iostream>
#include <string>
#include <vector>

#include "secuence.h"  // Necesitamos la definición de Sequence/staticSequence

template <class Key>
class SortMethod {
 protected:
  void printSequence(const staticSequence<Key>& sequence,
                     const std::string& message = "") const {
    if (!message.empty()) {
      std::cout << message << ": ";
    }
    for (unsigned i = 0; i < sequence.getSize(); ++i) {
      std::cout << sequence[i] << " ";
    }
    std::cout << std::endl;
  }

  void swap(Key& a, Key& b) { 
    Key temp = a;
    a = b;
    b = temp;
  }

 public:
  virtual void Sort(staticSequence<Key>& sequence, bool trace) = 0;
  virtual ~SortMethod() {}
};

template <class Key>
class InsertionSort : public SortMethod<Key> {
 public:
  void Sort(staticSequence<Key>& sequence, bool trace) override {
    unsigned n = sequence.getSize();
    if (n <= 1) return;  // Nada que ordenar
    if (trace) this->printSequence(sequence, "Inicial");

    for (unsigned i = 1; i < n; ++i) {
      Key current_key = sequence[i];
      int j = i - 1;
      // Desplazar elementos mayores que current_key hacia la derecha
      while (j >= 0 && sequence[j] > current_key) {
        sequence[j + 1] = sequence[j];
        j--;
      }
      sequence[j + 1] = current_key;  // Insertar en la posición correcta
      if (trace) {
        this->printSequence(sequence, "Iter " + std::to_string(i));
      }
    }
    if (trace) this->printSequence(sequence, "Final");
  }
};

template <class Key>
class ShakerSort : public SortMethod<Key> {
 public:
  void Sort(staticSequence<Key>& sequence, bool trace) override {
    unsigned n = sequence.getSize();
    if (n <= 1) return;
    unsigned left = 0;
    unsigned right = n - 1;
    bool swapped = true;
    int iteration = 0;

    if (trace) this->printSequence(sequence, "Inicial");

    while (swapped && left < right) {
      swapped = false;
      iteration++;

      // Pasada de izquierda a derecha (como Bubble Sort)
      for (unsigned i = left; i < right; ++i) {
        // Asume operator> para Key (nif)
        if (sequence[i] > sequence[i + 1]) {
          this->swap(sequence[i], sequence[i + 1]);
          swapped = true;
        }
      }
      right--;              // El último elemento está en su lugar
      if (!swapped) break;  // Si no hubo intercambios, está ordenado
      if (trace) {
        this->printSequence(sequence,
                            "Iter " + std::to_string(iteration) + " (L->R)");
      }
      swapped = false;  // Resetear para la siguiente pasada

      // Pasada de derecha a izquierda
      for (unsigned i = right; i > left; --i) {
        // Asume operator< para Key (nif)
        if (sequence[i] < sequence[i - 1]) {
          this->swap(sequence[i], sequence[i - 1]);
          swapped = true;
        }
      }
      left++;  // El primer elemento está en su lugar

      if (trace && swapped) {  // Solo imprimir si hubo cambios
        this->printSequence(sequence,
                            "Iter " + std::to_string(iteration) + " (R->L)");
      }
    }
    if (trace) this->printSequence(sequence, "Final");
  }
};

template <class Key>
class QuickSort : public SortMethod<Key> {
 public:
  void Sort(staticSequence<Key>& sequence, bool trace) override {
    unsigned n = sequence.getSize();
    if (n <= 1) return;
    if (trace) this->printSequence(sequence, "Initial");
    QuickSortRecursive(sequence, 0, n - 1, trace);
    if (trace) this->printSequence(sequence, "Final");
  }

 private:
  // Función recursiva auxiliar
  void QuickSortRecursive(staticSequence<Key>& sequence, int low, int high,
                          bool trace) {
    if (low < high) {
      int pivot_index = Partition(sequence, low, high, trace);

      if (trace) {
        this->printSequence(sequence, "After partition (pivot=" +
                                          std::to_string(pivot_index) + ")");
      }

      QuickSortRecursive(sequence, low, pivot_index - 1, trace);
      QuickSortRecursive(sequence, pivot_index + 1, high, trace);
    }
  }

  // Función para particionar la secuencia
  int Partition(staticSequence<Key>& sequence, int low, int high,
                bool trace) {
    // Estrategia de pivote simple: último elemento
    Key pivot = sequence[high];
    int i = (low - 1);  // Índice del elemento más pequeño

    for (int j = low; j <= high - 1; ++j) {
      // Si el elemento actual es menor o igual al pivote
      // Asume operator<= para Key (nif)
      if (sequence[j] <= pivot) {
        i++;
        this->swap(sequence[i], sequence[j]);
      }
    }
    // Colocar el pivote en su posición correcta
    this->swap(sequence[i + 1], sequence[high]);
    return (i + 1);  // Devolver índice del pivote
  }
};

template <class Key>
class HeapSort : public SortMethod<Key> {
 public:
  void Sort(staticSequence<Key>& sequence, bool trace) override {
    unsigned n = sequence.getSize();
    if (n <= 1) return;
    if (trace) this->printSequence(sequence, "Initial");

    // Empezamos desde el último nodo no-hoja (n/2 - 1)
    for (int i = n / 2 - 1; i >= 0; --i) {
      downHeap(sequence, n, i, trace);
    }

    if (trace) this->printSequence(sequence, "After building heap");

    for (int i = n - 1; i > 0; --i) {
      // Mover la raíz actual (el máximo) al final del array ordenado
      this->swap(sequence[0], sequence[i]);

      if (trace) {
        this->printSequence(
            sequence, "After swapping root with element " + std::to_string(i));
      }
      // Llamar a downHeap en el heap reducido (tamaño i)
      downHeap(sequence, i, 0, trace);
      if (trace) {
        this->printSequence(sequence, "After heapify root (heap size " +
                                          std::to_string(i) + ")");
      }
    }
    if (trace) this->printSequence(sequence, "Final");
  }

 private:
  // Función para mantener la propiedad de Max-Heap (montículo máximo)
  // n es el tamaño del heap, i es el índice raíz del subárbol
  void downHeap(staticSequence<Key>& sequence, unsigned n, unsigned i,
                bool trace) {
    unsigned largest = i;        // Inicializar largest como raíz
    unsigned left = 2 * i + 1;   // Índice hijo izquierdo
    unsigned right = 2 * i + 2;  // Índice hijo derecho

    // Si el hijo izquierdo es más grande que la raíz
    if (left < n && sequence[left] > sequence[largest]) {
      largest = left;
    }

    // Si el hijo derecho es más grande que el 'largest' hasta ahora
    if (right < n && sequence[right] > sequence[largest]) {
      largest = right;
    }

    // Si 'largest' no es la raíz original
    if (largest != i) {
      this->swap(sequence[i], sequence[largest]);

      // Recursivamente aplicar downHeap al subárbol afectado
      downHeap(sequence, n, largest, trace);
    }
  }
};

template <class Key>
class ShellSort : public SortMethod<Key> {
 public:
  // Constructor para recibir alpha
  ShellSort(double alpha) : alpha_(alpha) {
    if (alpha <= 0 || alpha >= 1) {
      // Valor por defecto o lanzar excepción si alpha es inválido
      std::cerr << "Warning: Número no valido para ShellSort (" << alpha
                << "). Se usará por defecto 0.5.\n";
      alpha_ = 0.5;
    }
  }

  void Sort(staticSequence<Key>& sequence, bool trace) override {
    unsigned n = sequence.getSize();
    if (n <= 1) return;

    if (trace) this->printSequence(sequence, "Inicio");

    // Calcular el gap inicial
    unsigned gap = n;
    if (alpha_ >
        0) {  // Evitar división por cero si alpha es 0 (aunque ya validado)
      gap = static_cast<unsigned>(floor(n * alpha_));
      if (gap == 0)
        gap = 1;  // Asegurar al menos un gap de 1 si n*alpha es muy pequeño
    } else {
      gap = n / 2;  // Fallback si alpha es inválido
    }

    // Empezar con el gap más grande y reducirlo
    while (gap > 0) {
      if (trace) {
        std::cout << "--- iteración de la traza de ShellSort con gap = " << gap
                  << " ---\n";
      }

      // Realizar Insertion Sort con el gap actual
      // Iterar desde el gap-ésimo elemento hasta el final
      for (unsigned i = gap; i < n; ++i) {
        // Guardar el elemento actual y crear un hueco en la posición i
        Key temp = sequence[i];
        unsigned j = i;

        // Desplazar elementos anteriores (a distancia 'gap') que sean mayores
        while (j >= gap && sequence[j - gap] > temp) {
          sequence[j] = sequence[j - gap];
          j -= gap;
        }
        // Poner temp (el elemento original sequence[i]) en su posición correcta
        sequence[j] = temp;
      }

      if (trace) {
        this->printSequence(sequence,
                            "Después de pasar con gap = " + std::to_string(gap));
      }

      // Calcular el siguiente gap
      if (gap == 1) {  // Condición de salida alternativa
        gap = 0;
      } else {
        gap = static_cast<unsigned>(floor(gap * alpha_));
        if (gap == 0) gap = 1;  // Asegurar que la última pasada sea con gap=1
      }
    }
    if (trace) this->printSequence(sequence, "Final");
  }

 private:
  double alpha_;  // Constante de reducción
};

#endif  // SORT_METHODS_H
