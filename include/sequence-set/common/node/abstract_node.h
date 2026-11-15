//
// Created by arthur on 19/06/24.
//

#ifndef SEQUENCE_SET_COMMON_NODE_ABSTRACT_NODE_H
#define SEQUENCE_SET_COMMON_NODE_ABSTRACT_NODE_H

#include <utility>

/// @brief Base para os nós que armazenam um valor.
///
/// O construtor é protegido para impedir a instanciação direta da classe; os
/// herdeiros inicializam o valor armazenado.
///
/// @tparam T Tipo de dado armazenado dentro do nó.
template <class T>
class AbstractNode {
 protected:
  T _data;

  explicit AbstractNode(const T& data) : _data(data) {}
  explicit AbstractNode(T&& data) : _data(std::move(data)) {}

 public:
  virtual ~AbstractNode() = default;
};

#endif  // SEQUENCE_SET_COMMON_NODE_ABSTRACT_NODE_H
