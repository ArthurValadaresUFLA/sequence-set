//
// Created by arthur on 19/06/24.
//

#ifndef SEQUENCE_SET_COMMON_NODE_INTERFACE_SINGLY_LINKED_NODE_INTERFACE_H
#define SEQUENCE_SET_COMMON_NODE_INTERFACE_SINGLY_LINKED_NODE_INTERFACE_H

#include <sequence-set/common/node/interface/node_interface.h>

/// @file
/// @brief Contrato para nós com encadeamento simples.

/// @brief Interface para um nó com encadeamento simples.
///
/// Define o acesso e a definição do próximo nó da cadeia. Cada nó conhece
/// apenas o seu sucessor, o que reduz o consumo de memória em relação ao
/// encadeamento duplo, ao custo de não permitir percurso para trás.
///
/// @tparam T Tipo de dado armazenado dentro do nó.
template <class T>
class SinglyLinkedNodeInterface : public NodeInterface<T> {
 public:
  /// @return Ponteiro para o próximo nó, ou nullptr no fim da cadeia.
  [[nodiscard]] virtual SinglyLinkedNodeInterface<T>* getNext() const = 0;

  /// Define o próximo nó da cadeia.
  /// @param next Ponteiro para o novo sucessor; nullptr encerra a cadeia.
  virtual void setNext(SinglyLinkedNodeInterface<T>* next) = 0;
};

#endif  // SEQUENCE_SET_COMMON_NODE_INTERFACE_SINGLY_LINKED_NODE_INTERFACE_H
