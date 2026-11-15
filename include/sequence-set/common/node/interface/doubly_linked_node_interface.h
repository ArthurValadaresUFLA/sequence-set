//
// Created by arthur on 19/06/24.
//

#ifndef SEQUENCE_SET_COMMON_NODE_INTERFACE_DOUBLY_LINKED_NODE_INTERFACE_H
#define SEQUENCE_SET_COMMON_NODE_INTERFACE_DOUBLY_LINKED_NODE_INTERFACE_H

#include <tuple>

#include <sequence-set/common/node/interface/node_interface.h>

/// @file
/// @brief Contrato para nós com encadeamento duplo.

/// @brief Interface para um nó duplamente encadeado.
///
/// Além do valor, o nó mantém ponteiros para o próximo e para o nó anterior da
/// cadeia, permitindo percurso nos dois sentidos e remoção em tempo constante
/// quando o nó já é conhecido.
///
/// @tparam T Tipo de dado armazenado dentro do nó.
template <class T>
class DoublyLinkedNodeInterface : public NodeInterface<T> {
 public:
  /// @return Ponteiro para o próximo nó, ou nullptr no fim da cadeia.
  [[nodiscard]] virtual DoublyLinkedNodeInterface<T>* getNext() const = 0;

  /// Define o próximo nó da cadeia.
  /// @param next Ponteiro para o novo sucessor; nullptr encerra a cadeia.
  virtual void setNext(DoublyLinkedNodeInterface<T>* next) = 0;

  /// @return Ponteiro para o nó anterior, ou nullptr no início da cadeia.
  [[nodiscard]] virtual DoublyLinkedNodeInterface<T>* getPrevious() const = 0;

  /// Define o nó anterior da cadeia.
  /// @param previous Ponteiro para o novo antecessor; nullptr inicia a cadeia.
  virtual void setPrevious(DoublyLinkedNodeInterface<T>* previous) = 0;

  /// Retorna simultaneamente os ponteiros para o nó anterior e para o próximo.
  /// @return Tupla `(previous, next)`, com nullptr nas extremidades.
  [[nodiscard]] virtual std::tuple<DoublyLinkedNodeInterface<T>*, DoublyLinkedNodeInterface<T>*>
  getBoth() const = 0;
};

#endif  // SEQUENCE_SET_COMMON_NODE_INTERFACE_DOUBLY_LINKED_NODE_INTERFACE_H
