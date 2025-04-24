// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estrucutras de Datos Avanzadas
// Curso: 2º
// Práctica 5
// Autor: Diego García Hernández
// Correo: alu0101633732@ull.edu.es
// Fecha: 10/04/2025
// Archivo secuence.h
// Descripción: contiene la clase secuence

#ifndef SECUENCE_H_
#define SECUENCE_H_

#include <algorithm>

template <class Key>
class Sequence {
 public:
  virtual bool search(const Key&) const = 0;
  virtual bool insert(const Key&) = 0;
  virtual Key operator[](const unsigned) const = 0;
  virtual Key& operator[](const unsigned) = 0;
  virtual unsigned getSize() const = 0; 
  virtual ~Sequence() {}                
};


template <class Key>
class staticSequence : public Sequence<Key> {        
 public:
  staticSequence(unsigned n) : capacity_(n), size_(0), data_(new Key[n]) {}
  ~staticSequence() override {
    delete[] data_;
    data_ = nullptr; 
  }

  staticSequence(const staticSequence&) = delete;
  staticSequence& operator=(const staticSequence&) = delete;

  bool search(const Key& k) const override {
    for (unsigned i = 0; i < size_; ++i) {
      if (data_[i] == k) return true;
    }
    return false;
  }
  bool insert(const Key& k) override {
    if (size_ < capacity_ && !search(k)) {
      data_[size_++] = k;
      return true;
    }
    return false;
  }
  bool isFull() const { return size_ == capacity_; }
  Key operator[](const unsigned index) const override {
    if (index < size_) return data_[index];
    throw std::out_of_range(
        "Index out of range in staticSequence::operator[] const");
  }
  Key& operator[](const unsigned index) override {
    if (index < capacity_) {
      if (index >= size_) size_ = index + 1;
      return data_[index];
    }
    throw std::out_of_range("Index out of range in staticSequence::operator[]");
  }
  unsigned getSize() const override { return size_; }
  unsigned getCapacity() const { return capacity_; }
  void updateSize(unsigned newSize) {
    if (newSize <= capacity_) {
      size_ = newSize;
    } else {
      std::cerr << "Error al actualizar el size de la secuencia\n";
    }
  }

 private:
  unsigned capacity_;  
  unsigned size_;      
  Key* data_; 
};
#endif