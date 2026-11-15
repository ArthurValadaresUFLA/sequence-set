//
// Created by arthur on 20/06/24.
//

#ifndef SEQUENCE_SET_LIST_DOUBLY_LINKED_LIST_TPP
#define SEQUENCE_SET_LIST_DOUBLY_LINKED_LIST_TPP

#include <stdexcept>
#include <utility>

/// @file
/// @brief Definições dos métodos da lista duplamente encadeada.

/// Cria uma cópia profunda de @p other, duplicando cada nó.
/// @param other Lista de origem.
/// @note Em caso de falha de alocação, os nós já criados são liberados.
template <class T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList& other)
    : AbstractDoublyLinkedList<T>(nullptr, nullptr) {
  try {
    for (const DoublyLinkedNodeInterface<T>* current = other._begin; current != nullptr;
         current = current->getNext()) {
      pushBack(current->getValue());
    }
  } catch (...) {
    clear();
    throw;
  }
}

/// Transfere os nós de @p other, deixando-a vazia.
/// @param other Lista de origem.
template <class T>
DoublyLinkedList<T>::DoublyLinkedList(DoublyLinkedList&& other) noexcept
    : AbstractDoublyLinkedList<T>(other._begin, other._end) {
  this->_size = other._size;
  other._begin = nullptr;
  other._end = nullptr;
  other._size = 0;
}

/// Atribuição por cópia e por movimentação (copy-and-swap).
/// @param other Lista a ser atribuída; é consumida pela troca.
/// @return Referência para esta lista.
template <class T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(DoublyLinkedList other) noexcept {
  swap(other);
  return *this;
}

/// Libera todos os nós da lista.
template <class T>
DoublyLinkedList<T>::~DoublyLinkedList() {
  clear();
}

/// Troca o conteúdo desta lista com o de @p other em tempo constante.
/// @param other Lista com a qual o conteúdo será trocado.
template <class T>
void DoublyLinkedList<T>::swap(DoublyLinkedList& other) noexcept {
  std::swap(this->_begin, other._begin);
  std::swap(this->_end, other._end);
  std::swap(this->_size, other._size);
}

/// Remove todos os nós da lista.
/// @note A operação não lança exceções; os nós são liberados um a um.
template <class T>
void DoublyLinkedList<T>::clear() noexcept {
  DoublyLinkedNodeInterface<T>* current = this->_begin;
  while (current != nullptr) {
    DoublyLinkedNodeInterface<T>* next = current->getNext();
    delete current;
    current = next;
  }
  this->_begin = nullptr;
  this->_end = nullptr;
  this->_size = 0;
}

/// Acessa o elemento da posição @p index com permissão de alteração.
/// @param index Posição do elemento.
/// @return Referência mutável para o elemento.
/// @throw std::out_of_range Se @p index for maior ou igual a size().
template <class T>
T& DoublyLinkedList<T>::operator[](std::size_t index) {
  if (index >= this->_size) {
    throw std::out_of_range("índice fora dos limites da lista");
  }

  DoublyLinkedNodeInterface<T>* current = this->_begin;
  for (std::size_t i = 0; i < index; ++i) {
    current = current->getNext();
  }
  return current->getValue();
}

/// Acessa o elemento da posição @p index sem permissão de alteração.
/// @param index Posição do elemento.
/// @return Referência constante para o elemento.
/// @throw std::out_of_range Se @p index for maior ou igual a size().
template <class T>
const T& DoublyLinkedList<T>::operator[](std::size_t index) const {
  if (index >= this->_size) {
    throw std::out_of_range("índice fora dos limites da lista");
  }

  const DoublyLinkedNodeInterface<T>* current = this->_begin;
  for (std::size_t i = 0; i < index; ++i) {
    current = current->getNext();
  }
  return current->getValue();
}

/// Retorna a posição da primeira ocorrência de @p data.
/// @param data Valor procurado.
/// @return Índice da primeira ocorrência ou `size()` caso ausente.
template <class T>
std::size_t DoublyLinkedList<T>::find(const T& data) const {
  const DoublyLinkedNodeInterface<T>* current = this->_begin;
  std::size_t index = 0;

  while (current != nullptr) {
    if (current->getValue() == data) {
      return index;
    }
    current = current->getNext();
    ++index;
  }

  return this->_size;
}

/// @return Quantidade de elementos armazenados.
template <class T>
std::size_t DoublyLinkedList<T>::size() const {
  return this->_size;
}

/// @param data Valor procurado.
/// @return `true` se @p data estiver presente na lista.
template <class T>
bool DoublyLinkedList<T>::contains(const T& data) const {
  return find(data) != this->_size;
}

/// Insere @p data no início da lista.
/// @param data Valor a ser inserido.
template <class T>
void DoublyLinkedList<T>::push(const T& data) {
  auto* node = new DoublyLinkedNode<T>(data);

  node->setNext(this->_begin);
  if (this->_begin == nullptr) {
    this->_end = node;
  } else {
    this->_begin->setPrevious(node);
  }
  this->_begin = node;
  ++this->_size;
}

/// Insere @p data no fim da lista.
/// @param data Valor a ser inserido.
template <class T>
void DoublyLinkedList<T>::pushBack(const T& data) {
  auto* node = new DoublyLinkedNode<T>(data);

  node->setPrevious(this->_end);
  if (this->_end == nullptr) {
    this->_begin = node;
  } else {
    this->_end->setNext(node);
  }
  this->_end = node;
  ++this->_size;
}

/// Insere @p data na posição @p index.
/// @param index Posição de inserção; deve estar em `[0, size()]`.
/// @param data Valor a ser inserido.
/// @throw std::out_of_range Se @p index for maior que size().
template <class T>
void DoublyLinkedList<T>::insertAt(std::size_t index, const T& data) {
  if (index > this->_size) {
    throw std::out_of_range("índice de inserção fora dos limites da lista");
  }
  if (index == 0) {
    push(data);
    return;
  }
  if (index == this->_size) {
    pushBack(data);
    return;
  }

  DoublyLinkedNodeInterface<T>* current = this->_begin;
  for (std::size_t i = 0; i < index; ++i) {
    current = current->getNext();
  }

  auto* node = new DoublyLinkedNode<T>(data);
  DoublyLinkedNodeInterface<T>* previous = current->getPrevious();
  node->setPrevious(previous);
  node->setNext(current);
  previous->setNext(node);
  current->setPrevious(node);
  ++this->_size;
}

/// Remove e retorna o primeiro elemento da lista.
/// @return Cópia do elemento removido.
/// @throw std::runtime_error Se a lista estiver vazia.
template <class T>
T DoublyLinkedList<T>::removeOnBegin() {
  if (this->isEmpty()) {
    throw std::runtime_error("não é possível remover: a lista está vazia");
  }

  DoublyLinkedNodeInterface<T>* removed = this->_begin;
  T value = removed->getValue();

  this->_begin = removed->getNext();
  if (this->_begin == nullptr) {
    this->_end = nullptr;
  } else {
    this->_begin->setPrevious(nullptr);
  }
  --this->_size;

  delete removed;
  return value;
}

/// Remove e retorna o último elemento da lista.
/// @return Cópia do elemento removido.
/// @throw std::runtime_error Se a lista estiver vazia.
template <class T>
T DoublyLinkedList<T>::removeAtEnd() {
  if (this->isEmpty()) {
    throw std::runtime_error("não é possível remover: a lista está vazia");
  }

  DoublyLinkedNodeInterface<T>* removed = this->_end;
  T value = removed->getValue();

  this->_end = removed->getPrevious();
  if (this->_end == nullptr) {
    this->_begin = nullptr;
  } else {
    this->_end->setNext(nullptr);
  }
  --this->_size;

  delete removed;
  return value;
}

/// Remove e retorna o elemento da posição @p position.
/// @param position Posição do elemento a remover.
/// @return Cópia do elemento removido.
/// @throw std::out_of_range Se @p position for maior ou igual a size().
template <class T>
T DoublyLinkedList<T>::removeAt(std::size_t position) {
  if (position >= this->_size) {
    throw std::out_of_range("índice de remoção fora dos limites da lista");
  }
  if (position == 0) {
    return removeOnBegin();
  }
  if (position == this->_size - 1) {
    return removeAtEnd();
  }

  DoublyLinkedNodeInterface<T>* current = this->_begin;
  for (std::size_t i = 0; i < position; ++i) {
    current = current->getNext();
  }

  DoublyLinkedNodeInterface<T>* previous = current->getPrevious();
  DoublyLinkedNodeInterface<T>* next = current->getNext();
  T value = current->getValue();

  previous->setNext(next);
  next->setPrevious(previous);
  --this->_size;

  delete current;
  return value;
}

/// @return `true` se a lista não contiver elementos.
template <class T>
bool DoublyLinkedList<T>::isEmpty() const {
  return this->_size == 0;
}

/// Remove os elementos para os quais @p predicate retorna `true`.
/// @param predicate Função avaliada com o índice e o valor de cada elemento.
/// @note O índice passado ao predicado é a posição original do elemento, mesmo
/// que remoções anteriores tenham alterado a lista.
template <class T>
void DoublyLinkedList<T>::removeWhere(std::function<bool(std::size_t, T)> predicate) {
  std::size_t index = 0;
  DoublyLinkedNodeInterface<T>* current = this->_begin;

  while (current != nullptr) {
    DoublyLinkedNodeInterface<T>* next = current->getNext();

    if (predicate(index, current->getValue())) {
      DoublyLinkedNodeInterface<T>* previous = current->getPrevious();

      if (previous == nullptr) {
        this->_begin = next;
      } else {
        previous->setNext(next);
      }
      if (next == nullptr) {
        this->_end = previous;
      } else {
        next->setPrevious(previous);
      }
      --this->_size;

      delete current;
    }

    current = next;
    ++index;
  }
}

#endif  // SEQUENCE_SET_LIST_DOUBLY_LINKED_LIST_TPP
