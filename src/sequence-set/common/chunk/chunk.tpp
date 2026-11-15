//
// Created by arthur on 21/01/25.
//

#ifndef SEQUENCE_SET_COMMON_CHUNK_CHUNK_TPP
#define SEQUENCE_SET_COMMON_CHUNK_CHUNK_TPP

#include <stdexcept>

template <class T>
Chunk<T>::Chunk(std::size_t capacity) : AbstractChunk<T>(capacity) {}

template <class T>
Chunk<T>::Chunk(std::size_t capacity, const Pair<std::size_t, T>* data, std::size_t begin,
                std::size_t end)
    : AbstractChunk<T>(capacity, data, begin, end) {}

template <class T>
Chunk<T>::Chunk(std::size_t capacity, const Pair<std::size_t, T>* data, std::size_t end)
    : AbstractChunk<T>(capacity, data, end) {}

template <class T>
void Chunk<T>::checkCapacity() const {
  if (this->_size >= this->_capacity) {
    throw std::runtime_error("não é possível inserir: o chunk está cheio");
  }
}

template <class T>
void Chunk<T>::insertAt(std::size_t index, const Pair<std::size_t, T>& pair) {
  if (index > this->_size) {
    throw std::out_of_range("índice de inserção fora dos limites");
  }
  if (this->_size >= this->_capacity) {
    throw std::runtime_error("não é possível inserir: o chunk está cheio");
  }

  for (std::size_t i = this->_size; i > index; --i) {
    this->_data[i] = this->_data[i - 1];
  }
  this->_data[index] = pair;
  ++this->_size;
}

template <class T>
void Chunk<T>::insert(const std::size_t& key, const T& data) {
  checkCapacity();

  std::size_t index = 0;
  while (index < this->_size && this->_data[index].key < key) {
    ++index;
  }

  if (index < this->_size && this->_data[index].key == key) {
    throw std::invalid_argument("o chunk já contém a chave informada");
  }

  insertAt(index, Pair<std::size_t, T>(key, data));
}

template <class T>
Pair<std::size_t, T> Chunk<T>::remove(const std::size_t& key) {
  std::size_t index = 0;
  while (index < this->_size && this->_data[index].key < key) {
    ++index;
  }

  if (index >= this->_size || this->_data[index].key != key) {
    throw std::range_error("este chunk não contém a chave fornecida");
  }

  Pair<std::size_t, T> removed = this->_data[index];
  for (std::size_t i = index; i + 1 < this->_size; ++i) {
    this->_data[i] = this->_data[i + 1];
  }
  --this->_size;
  return removed;
}

template <class T>
T Chunk<T>::find(const std::size_t& key) const {
  std::size_t index = 0;
  while (index < this->_size && this->_data[index].key < key) {
    ++index;
  }

  if (index < this->_size && this->_data[index].key == key) {
    return this->_data[index].data;
  }

  throw std::range_error("este chunk não contém a chave fornecida");
}

template <class T>
bool Chunk<T>::contains(const std::size_t& key) const {
  std::size_t index = 0;
  while (index < this->_size && this->_data[index].key < key) {
    ++index;
  }

  return index < this->_size && this->_data[index].key == key;
}

template <class T>
std::size_t Chunk<T>::getCapacity() {
  return this->_capacity;
}

template <class T>
const std::size_t& Chunk<T>::getCapacity() const {
  return this->_capacity;
}

template <class T>
std::size_t Chunk<T>::getSize() {
  return this->_size;
}

template <class T>
const std::size_t& Chunk<T>::getSize() const {
  return this->_size;
}

template <class T>
std::size_t Chunk<T>::getMinSize() const {
  return this->_capacity / 2;
}

template <class T>
bool Chunk<T>::isFull() const {
  return this->_size >= this->_capacity;
}

template <class T>
Pair<std::size_t, T> Chunk<T>::first() const {
  if (this->_size == 0) {
    throw std::range_error("o chunk está vazio");
  }
  return this->_data[0];
}

template <class T>
Pair<std::size_t, T> Chunk<T>::last() const {
  if (this->_size == 0) {
    throw std::range_error("o chunk está vazio");
  }
  return this->_data[this->_size - 1];
}

template <class T>
Pair<std::size_t, T> Chunk<T>::operator[](const std::size_t& index) {
  if (index >= this->_size) {
    throw std::out_of_range("índice fora dos limites do chunk");
  }
  return this->_data[index];
}

template <class T>
const Pair<std::size_t, T>& Chunk<T>::operator[](const std::size_t& index) const {
  if (index >= this->_size) {
    throw std::out_of_range("índice fora dos limites do chunk");
  }
  return this->_data[index];
}

template <class T>
std::pair<Chunk<T>, Chunk<T>> Chunk<T>::halve() {
  if (this->_size < 2) {
    throw std::logic_error(
        "não é possível dividir um chunk com menos de dois "
        "elementos");
  }

  const std::size_t half = this->_size / 2;
  return {Chunk<T>(this->_capacity, this->_data, 0, half - 1),
          Chunk<T>(this->_capacity, this->_data, half, this->_size - 1)};
}

template <class T>
bool Chunk<T>::operator==(const Chunk<T>& other) const {
  if (this->_capacity != other._capacity || this->_size != other._size) {
    return false;
  }

  for (std::size_t i = 0; i < this->_size; ++i) {
    if (this->_data[i] != other._data[i]) {
      return false;
    }
  }
  return true;
}

#endif  // SEQUENCE_SET_COMMON_CHUNK_CHUNK_TPP
