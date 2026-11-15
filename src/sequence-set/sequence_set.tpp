//
// Created by arthur on 21/01/25.
//

#ifndef SEQUENCE_SET_SEQUENCE_SET_TPP
#define SEQUENCE_SET_SEQUENCE_SET_TPP

#include <stdexcept>
#include <utility>

template <class T>
SequenceSet<T>::SequenceSet(std::size_t chunkSize)
    : DoublyLinkedList<Chunk<T>>(), _chunkSize(chunkSize) {
  if (chunkSize < 2) {
    throw std::invalid_argument("o tamanho do chunk deve ser no mínimo 2");
  }
}

template <class T>
SequenceSet<T>::SequenceSet(const SequenceSet& other)
    : DoublyLinkedList<Chunk<T>>(other), _chunkSize(other._chunkSize) {}

template <class T>
SequenceSet<T>::SequenceSet(SequenceSet&& other) noexcept
    : DoublyLinkedList<Chunk<T>>(std::move(other)), _chunkSize(other._chunkSize) {}

template <class T>
SequenceSet<T>& SequenceSet<T>::operator=(const SequenceSet& other) {
  if (this != &other) {
    DoublyLinkedList<Chunk<T>>::operator=(other);
    _chunkSize = other._chunkSize;
  }
  return *this;
}

template <class T>
SequenceSet<T>& SequenceSet<T>::operator=(SequenceSet&& other) noexcept {
  if (this != &other) {
    DoublyLinkedList<Chunk<T>>::operator=(std::move(other));
    _chunkSize = other._chunkSize;
  }
  return *this;
}

template <class T>
void SequenceSet<T>::insert(const std::size_t& key, const T& data) {
  if (this->contains(key)) {
    throw std::invalid_argument("o conjunto já contém a chave informada");
  }

  if (this->isEmpty()) {
    Chunk<T> chunk(_chunkSize);
    chunk.insert(key, data);
    DoublyLinkedList<Chunk<T>>::pushBack(chunk);
    return;
  }

  // Localiza o último chunk cuja primeira chave é menor ou igual à chave.
  DoublyLinkedNodeInterface<Chunk<T>>* node = this->_begin;
  while (node->getNext() != nullptr && node->getNext()->getValue().first().key <= key) {
    node = node->getNext();
  }

  Chunk<T>& chunk = node->getValue();
  if (!chunk.isFull()) {
    chunk.insert(key, data);
    return;
  }

  // O chunk está cheio: divide-o e insere o novo elemento na metade correta.
  auto [left, right] = chunk.halve();
  node->getValue() = std::move(left);

  auto* rightNode = new DoublyLinkedNode<Chunk<T>>(std::move(right));
  rightNode->setPrevious(node);
  rightNode->setNext(node->getNext());
  if (node->getNext() != nullptr) {
    node->getNext()->setPrevious(rightNode);
  } else {
    this->_end = rightNode;
  }
  node->setNext(rightNode);
  ++this->_size;

  if (key <= node->getValue().last().key) {
    node->getValue().insert(key, data);
  } else {
    rightNode->getValue().insert(key, data);
  }
}

template <class T>
Pair<std::size_t, T> SequenceSet<T>::remove(std::size_t key) {
  for (DoublyLinkedNodeInterface<Chunk<T>>* node = this->_begin; node != nullptr;
       node = node->getNext()) {
    Chunk<T>& chunk = node->getValue();
    if (chunk.contains(key)) {
      return chunk.remove(key);
    }
  }

  throw std::range_error("este conjunto não contém a chave fornecida");
}

template <class T>
bool SequenceSet<T>::contains(std::size_t key) const {
  for (const DoublyLinkedNodeInterface<Chunk<T>>* node = this->_begin; node != nullptr;
       node = node->getNext()) {
    if (node->getValue().contains(key)) {
      return true;
    }
  }
  return false;
}

template <class T>
T SequenceSet<T>::find(std::size_t key) const {
  for (const DoublyLinkedNodeInterface<Chunk<T>>* node = this->_begin; node != nullptr;
       node = node->getNext()) {
    const Chunk<T>& chunk = node->getValue();
    if (chunk.contains(key)) {
      return chunk.find(key);
    }
  }

  throw std::runtime_error("este conjunto não contém a chave fornecida");
}

template <class T>
std::size_t SequenceSet<T>::getCapacity() const {
  std::size_t total = 0;
  for (const DoublyLinkedNodeInterface<Chunk<T>>* node = this->_begin; node != nullptr;
       node = node->getNext()) {
    total += node->getValue().getCapacity();
  }
  return total;
}

template <class T>
std::size_t SequenceSet<T>::getSize() const {
  std::size_t total = 0;
  for (const DoublyLinkedNodeInterface<Chunk<T>>* node = this->_begin; node != nullptr;
       node = node->getNext()) {
    total += node->getValue().getSize();
  }
  return total;
}

template <class T>
std::size_t SequenceSet<T>::getChunkCount() const {
  return this->_size;
}

template <class T>
std::size_t SequenceSet<T>::getChunkSize() const {
  return _chunkSize;
}

#endif  // SEQUENCE_SET_SEQUENCE_SET_TPP
