//
// Created by arthur on 20/06/24.
//

#ifndef SEQUENCE_SET_LIST_ABSTRACT_DOUBLY_LINKED_LIST_H
#define SEQUENCE_SET_LIST_ABSTRACT_DOUBLY_LINKED_LIST_H

#include <cstddef>

#include <sequence-set/common/node/interface/doubly_linked_node_interface.h>

/// @file
/// @brief Base comum para listas duplamente encadeadas.

/// @brief Base comum para listas duplamente encadeadas.
///
/// Mantém os ponteiros para o primeiro e o último nó, além do tamanho atual da
/// lista. A posse dos nós é responsabilidade da classe derivada, que deve
/// liberá-los no destrutor.
///
/// @tparam T Tipo dos elementos armazenados na lista.
template <class T>
class AbstractDoublyLinkedList {
 protected:
  /// Ponteiro para o primeiro nó da lista.
  DoublyLinkedNodeInterface<T>* _begin{};

  /// Ponteiro para o último nó da lista.
  DoublyLinkedNodeInterface<T>* _end{};

  /// Quantidade de nós presentes na lista.
  std::size_t _size{};

  /// Inicializa a lista com as extremidades informadas.
  /// @param begin Ponteiro para o primeiro nó (ou nullptr).
  /// @param end Ponteiro para o último nó (ou nullptr).
  AbstractDoublyLinkedList(DoublyLinkedNodeInterface<T>* begin, DoublyLinkedNodeInterface<T>* end)
      : _begin(begin), _end(end) {}

 public:
  /// Destrói a base; os nós não são liberados automaticamente.
  virtual ~AbstractDoublyLinkedList() = default;
};

#endif  // SEQUENCE_SET_LIST_ABSTRACT_DOUBLY_LINKED_LIST_H
