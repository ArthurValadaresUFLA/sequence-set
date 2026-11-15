//
// Created by arthur on 19/06/24.
//

#ifndef SEQUENCE_SET_COMMON_NODE_DOUBLY_LINKED_NODE_H
#define SEQUENCE_SET_COMMON_NODE_DOUBLY_LINKED_NODE_H

#include <tuple>
#include <utility>

#include <sequence-set/common/node/abstract_node.h>
#include <sequence-set/common/node/interface/doubly_linked_node_interface.h>

/// @brief Nó duplamente encadeado.
///
/// O nó herda privadamente de AbstractNode (o valor não é exposto como base) e
/// publicamente da interface, que define o contrato de encadeamento.
///
/// @tparam T Tipo de dado armazenado no nó.
template <class T>
class DoublyLinkedNode : private AbstractNode<T>, public DoublyLinkedNodeInterface<T> {
 private:
  DoublyLinkedNodeInterface<T>* _next{};
  DoublyLinkedNodeInterface<T>* _previous{};

 public:
  explicit DoublyLinkedNode(const T& data) : AbstractNode<T>(data) {}
  explicit DoublyLinkedNode(T&& data) : AbstractNode<T>(std::move(data)) {}

  ~DoublyLinkedNode() override = default;

  [[nodiscard]] DoublyLinkedNodeInterface<T>* getNext() const override;
  [[nodiscard]] DoublyLinkedNodeInterface<T>* getPrevious() const override;

  [[nodiscard]] const T& getValue() const override;
  [[nodiscard]] T& getValue() override;

  void setPrevious(DoublyLinkedNodeInterface<T>* previous) override;
  void setNext(DoublyLinkedNodeInterface<T>* next) override;

  [[nodiscard]] std::tuple<DoublyLinkedNodeInterface<T>*, DoublyLinkedNodeInterface<T>*> getBoth()
      const override;
};

#include <sequence-set/common/node/doubly_linked_node.tpp>

#endif  // SEQUENCE_SET_COMMON_NODE_DOUBLY_LINKED_NODE_H
