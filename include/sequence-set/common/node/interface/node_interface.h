//
// Created by arthur on 19/06/24.
//

#ifndef SEQUENCE_SET_COMMON_NODE_INTERFACE_NODE_INTERFACE_H
#define SEQUENCE_SET_COMMON_NODE_INTERFACE_NODE_INTERFACE_H

/// @brief Interface para um nó de encadeamento.
///
/// Todo nó armazena um valor e permite acesso ao mesmo por referência
/// constante ou mutável.
///
/// @tparam T Tipo de dado armazenado dentro do nó.
template <class T>
class NodeInterface {
 public:
  virtual ~NodeInterface() = default;

  [[nodiscard]] virtual const T& getValue() const = 0;
  [[nodiscard]] virtual T& getValue() = 0;
};

#endif  // SEQUENCE_SET_COMMON_NODE_INTERFACE_NODE_INTERFACE_H
