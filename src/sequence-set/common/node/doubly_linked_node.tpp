//
// Created by arthur on 19/06/24.
//

#ifndef SEQUENCE_SET_COMMON_NODE_DOUBLY_LINKED_NODE_TPP
#define SEQUENCE_SET_COMMON_NODE_DOUBLY_LINKED_NODE_TPP

template <class T>
DoublyLinkedNodeInterface<T>* DoublyLinkedNode<T>::getNext() const {
  return _next;
}

template <class T>
DoublyLinkedNodeInterface<T>* DoublyLinkedNode<T>::getPrevious() const {
  return _previous;
}

template <class T>
const T& DoublyLinkedNode<T>::getValue() const {
  return this->_data;
}

template <class T>
T& DoublyLinkedNode<T>::getValue() {
  return this->_data;
}

template <class T>
void DoublyLinkedNode<T>::setPrevious(DoublyLinkedNodeInterface<T>* previous) {
  _previous = previous;
}

template <class T>
void DoublyLinkedNode<T>::setNext(DoublyLinkedNodeInterface<T>* next) {
  _next = next;
}

template <class T>
std::tuple<DoublyLinkedNodeInterface<T>*, DoublyLinkedNodeInterface<T>*>
DoublyLinkedNode<T>::getBoth() const {
  return std::make_tuple(_previous, _next);
}

#endif  // SEQUENCE_SET_COMMON_NODE_DOUBLY_LINKED_NODE_TPP
