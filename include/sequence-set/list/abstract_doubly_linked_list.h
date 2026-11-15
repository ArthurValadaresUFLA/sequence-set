//
// Created by arthur on 20/06/24.
//

#ifndef SEQUENCE_SET_LIST_ABSTRACT_DOUBLY_LINKED_LIST_H
#define SEQUENCE_SET_LIST_ABSTRACT_DOUBLY_LINKED_LIST_H

#include <cstddef>

#include <sequence-set/common/node/interface/doubly_linked_node_interface.h>

/// @brief Base comum para listas duplamente encadeadas.
///
/// Mantém os ponteiros para o primeiro e o último nó, além do tamanho atual da
/// lista. A posse dos nós é responsabilidade da classe derivada.
///
/// @tparam T Tipo dos elementos armazenados na lista.
template <class T>
class AbstractDoublyLinkedList {
 protected:
  DoublyLinkedNodeInterface<T>* _begin{};
  DoublyLinkedNodeInterface<T>* _end{};
  std::size_t _size{};

  AbstractDoublyLinkedList(DoublyLinkedNodeInterface<T>* begin, DoublyLinkedNodeInterface<T>* end)
      : _begin(begin), _end(end) {}

 public:
  virtual ~AbstractDoublyLinkedList() = default;
};

#endif  // SEQUENCE_SET_LIST_ABSTRACT_DOUBLY_LINKED_LIST_H
