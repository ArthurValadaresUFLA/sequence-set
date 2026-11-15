//
// Created by arthur on 21/01/25.
//

#ifndef SEQUENCE_SET_SEQUENCE_SET_TPP
#define SEQUENCE_SET_SEQUENCE_SET_TPP

#include <stdexcept>
#include <utility>

/// @file
/// @brief Definições dos métodos do conjunto de sequências.

/// Cria um conjunto vazio.
/// @param chunkSize Capacidade de cada chunk (mínimo 2).
/// @throw std::invalid_argument Se @p chunkSize for menor que 2.
template <class T>
SequenceSet<T>::SequenceSet(std::size_t chunkSize)
    : DoublyLinkedList<Chunk<T>>(), _chunkSize(chunkSize) {
  if (chunkSize < 2) {
    throw std::invalid_argument("o tamanho do chunk deve ser no mínimo 2");
  }
}

/// Cria uma cópia profunda de @p other.
/// @param other Conjunto de origem.
template <class T>
SequenceSet<T>::SequenceSet(const SequenceSet& other)
    : DoublyLinkedList<Chunk<T>>(other), _chunkSize(other._chunkSize) {}

/// Transfere os chunks de @p other, deixando-o vazio.
/// @param other Conjunto de origem.
template <class T>
SequenceSet<T>::SequenceSet(SequenceSet&& other) noexcept
    : DoublyLinkedList<Chunk<T>>(std::move(other)), _chunkSize(other._chunkSize) {}

/// Copia os chunks e a configuração de @p other.
/// @param other Conjunto de origem.
/// @return Referência para este conjunto.
template <class T>
SequenceSet<T>& SequenceSet<T>::operator=(const SequenceSet& other) {
  if (this != &other) {
    DoublyLinkedList<Chunk<T>>::operator=(other);
    _chunkSize = other._chunkSize;
  }
  return *this;
}

/// Transfere os chunks e a configuração de @p other.
/// @param other Conjunto de origem.
/// @return Referência para este conjunto.
template <class T>
SequenceSet<T>& SequenceSet<T>::operator=(SequenceSet&& other) noexcept {
  if (this != &other) {
    DoublyLinkedList<Chunk<T>>::operator=(std::move(other));
    _chunkSize = other._chunkSize;
  }
  return *this;
}

/// Insere um par no conjunto, dividindo o chunk quando necessário.
///
/// A chave é comparada com a primeira chave de cada chunk para localizar a
/// posição correta. Se o chunk estiver cheio, ele é dividido ao meio e o novo
/// elemento é inserido na metade que contém o intervalo adequado.
///
/// @param key Chave do elemento.
/// @param data Valor associado à chave.
/// @throw std::invalid_argument Se a chave já estiver presente.
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

/// Remove o elemento associado a @p key.
/// @param key Chave do elemento a remover.
/// @return Par removido.
/// @throw std::range_error Se a chave não estiver presente.
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

/// Verifica se o conjunto contém @p key.
/// @param key Chave procurada.
/// @return `true` se a chave estiver presente.
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

/// Retorna o valor associado a @p key.
/// @param key Chave procurada.
/// @return Cópia do valor associado.
/// @throw std::runtime_error Se a chave não estiver presente.
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

/// @return Soma das capacidades de todos os chunks.
template <class T>
std::size_t SequenceSet<T>::getCapacity() const {
  std::size_t total = 0;
  for (const DoublyLinkedNodeInterface<Chunk<T>>* node = this->_begin; node != nullptr;
       node = node->getNext()) {
    total += node->getValue().getCapacity();
  }
  return total;
}

/// @return Soma das quantidades de elementos de todos os chunks.
template <class T>
std::size_t SequenceSet<T>::getSize() const {
  std::size_t total = 0;
  for (const DoublyLinkedNodeInterface<Chunk<T>>* node = this->_begin; node != nullptr;
       node = node->getNext()) {
    total += node->getValue().getSize();
  }
  return total;
}

/// @return Quantidade de chunks que compõem o conjunto.
template <class T>
std::size_t SequenceSet<T>::getChunkCount() const {
  return this->_size;
}

/// @return Capacidade configurada para cada chunk.
template <class T>
std::size_t SequenceSet<T>::getChunkSize() const {
  return _chunkSize;
}

#endif  // SEQUENCE_SET_SEQUENCE_SET_TPP
