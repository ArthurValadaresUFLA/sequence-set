//
// Created by arthur on 19/06/24.
//

#ifndef SEQUENCE_SET_COMMON_NODE_INTERFACE_SINGLY_LINKED_NODE_INTERFACE_H
#define SEQUENCE_SET_COMMON_NODE_INTERFACE_SINGLY_LINKED_NODE_INTERFACE_H

#include <sequence-set/common/node/interface/node_interface.h>

/// @brief Interface para um nó com encadeamento simples.
///
/// Define o acesso e a definição do próximo nó da cadeia.
///
/// @tparam T Tipo de dado armazenado dentro do nó.
template <class T>
class SinglyLinkedNodeInterface : public NodeInterface<T> {
 public:
  [[nodiscard]] virtual SinglyLinkedNodeInterface<T>* getNext() const = 0;
  virtual void setNext(SinglyLinkedNodeInterface<T>* next) = 0;
};

#endif  // SEQUENCE_SET_COMMON_NODE_INTERFACE_SINGLY_LINKED_NODE_INTERFACE_H
