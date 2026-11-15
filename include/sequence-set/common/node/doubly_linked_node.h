//
// Created by arthur on 19/06/24.
//

#ifndef SEQUENCE_SET_COMMON_NODE_DOUBLY_LINKED_NODE_H
#define SEQUENCE_SET_COMMON_NODE_DOUBLY_LINKED_NODE_H

#include <tuple>
#include <utility>

#include <sequence-set/common/node/abstract_node.h>
#include <sequence-set/common/node/interface/doubly_linked_node_interface.h>

/// @file
/// @brief Implementação concreta do nó duplamente encadeado.

/// @brief Nó duplamente encadeado.
///
/// O nó herda privadamente de AbstractNode (o valor não é exposto como base) e
/// publicamente da interface, que define o contrato de encadeamento. Os
/// ponteiros de ligação pertencem à lista que contém o nó; o nó não gerencia a
/// vida útil dos vizinhos.
///
/// @tparam T Tipo de dado armazenado no nó.
template <class T>
class DoublyLinkedNode : private AbstractNode<T>, public DoublyLinkedNodeInterface<T> {
 private:
  /// Ponteiro para o próximo nó da cadeia.
  DoublyLinkedNodeInterface<T>* _next{};

  /// Ponteiro para o nó anterior da cadeia.
  DoublyLinkedNodeInterface<T>* _previous{};

 public:
  /// Cria um nó copiando @p data.
  /// @param data Valor a ser armazenado.
  explicit DoublyLinkedNode(const T& data) : AbstractNode<T>(data) {}

  /// Cria um nó movendo @p data.
  /// @param data Valor a ser armazenado.
  explicit DoublyLinkedNode(T&& data) : AbstractNode<T>(std::move(data)) {}

  /// Destrói o nó; os nós vizinhos não são afetados.
  ~DoublyLinkedNode() override = default;

  /// @return Ponteiro para o próximo nó, ou nullptr no fim da cadeia.
  [[nodiscard]] DoublyLinkedNodeInterface<T>* getNext() const override;

  /// @return Ponteiro para o nó anterior, ou nullptr no início da cadeia.
  [[nodiscard]] DoublyLinkedNodeInterface<T>* getPrevious() const override;

  /// @return Referência constante para o valor armazenado.
  [[nodiscard]] const T& getValue() const override;

  /// @return Referência mutável para o valor armazenado.
  [[nodiscard]] T& getValue() override;

  /// Define o nó anterior da cadeia.
  /// @param previous Ponteiro para o novo antecessor; nullptr inicia a cadeia.
  void setPrevious(DoublyLinkedNodeInterface<T>* previous) override;

  /// Define o próximo nó da cadeia.
  /// @param next Ponteiro para o novo sucessor; nullptr encerra a cadeia.
  void setNext(DoublyLinkedNodeInterface<T>* next) override;

  /// @return Tupla `(previous, next)`, com nullptr nas extremidades.
  [[nodiscard]] std::tuple<DoublyLinkedNodeInterface<T>*, DoublyLinkedNodeInterface<T>*> getBoth()
      const override;
};

#include <sequence-set/common/node/doubly_linked_node.tpp>

#endif  // SEQUENCE_SET_COMMON_NODE_DOUBLY_LINKED_NODE_H
