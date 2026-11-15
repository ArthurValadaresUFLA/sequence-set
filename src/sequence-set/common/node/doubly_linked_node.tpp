//
// Created by arthur on 19/06/24.
//

#ifndef SEQUENCE_SET_COMMON_NODE_DOUBLY_LINKED_NODE_TPP
#define SEQUENCE_SET_COMMON_NODE_DOUBLY_LINKED_NODE_TPP

/// @file
/// @brief Definições dos métodos do nó duplamente encadeado.

/// @return Ponteiro para o próximo nó, ou nullptr no fim da cadeia.
template <class T>
DoublyLinkedNodeInterface<T>* DoublyLinkedNode<T>::getNext() const {
  return _next;
}

/// @return Ponteiro para o nó anterior, ou nullptr no início da cadeia.
template <class T>
DoublyLinkedNodeInterface<T>* DoublyLinkedNode<T>::getPrevious() const {
  return _previous;
}

/// @return Referência constante para o valor armazenado.
template <class T>
const T& DoublyLinkedNode<T>::getValue() const {
  return this->_data;
}

/// @return Referência mutável para o valor armazenado.
template <class T>
T& DoublyLinkedNode<T>::getValue() {
  return this->_data;
}

/// Define o nó anterior da cadeia.
/// @param previous Ponteiro para o novo antecessor; nullptr inicia a cadeia.
template <class T>
void DoublyLinkedNode<T>::setPrevious(DoublyLinkedNodeInterface<T>* previous) {
  _previous = previous;
}

/// Define o próximo nó da cadeia.
/// @param next Ponteiro para o novo sucessor; nullptr encerra a cadeia.
template <class T>
void DoublyLinkedNode<T>::setNext(DoublyLinkedNodeInterface<T>* next) {
  _next = next;
}

/// @return Tupla `(previous, next)`, com nullptr nas extremidades.
template <class T>
std::tuple<DoublyLinkedNodeInterface<T>*, DoublyLinkedNodeInterface<T>*>
DoublyLinkedNode<T>::getBoth() const {
  return std::make_tuple(_previous, _next);
}

#endif  // SEQUENCE_SET_COMMON_NODE_DOUBLY_LINKED_NODE_TPP
