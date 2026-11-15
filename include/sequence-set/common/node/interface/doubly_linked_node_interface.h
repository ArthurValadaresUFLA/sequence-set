//
// Created by arthur on 19/06/24.
//

#ifndef SEQUENCE_SET_COMMON_NODE_INTERFACE_DOUBLY_LINKED_NODE_INTERFACE_H
#define SEQUENCE_SET_COMMON_NODE_INTERFACE_DOUBLY_LINKED_NODE_INTERFACE_H

#include <tuple>

#include <sequence-set/common/node/interface/node_interface.h>

/// @brief Interface para um nó duplamente encadeado.
///
/// Além do valor, o nó mantém ponteiros para o próximo e para o nó anterior da
/// cadeia.
///
/// @tparam T Tipo de dado armazenado dentro do nó.
template <class T>
class DoublyLinkedNodeInterface : public NodeInterface<T> {
 public:
  [[nodiscard]] virtual DoublyLinkedNodeInterface<T>* getNext() const = 0;
  virtual void setNext(DoublyLinkedNodeInterface<T>* next) = 0;

  [[nodiscard]] virtual DoublyLinkedNodeInterface<T>* getPrevious() const = 0;
  virtual void setPrevious(DoublyLinkedNodeInterface<T>* previous) = 0;

  /// Retorna simultaneamente os ponteiros para o nó anterior e para o próximo.
  [[nodiscard]] virtual std::tuple<DoublyLinkedNodeInterface<T>*, DoublyLinkedNodeInterface<T>*>
  getBoth() const = 0;
};

#endif  // SEQUENCE_SET_COMMON_NODE_INTERFACE_DOUBLY_LINKED_NODE_INTERFACE_H
