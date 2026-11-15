//
// Created by arthur on 19/06/24.
//

#ifndef SEQUENCE_SET_COMMON_NODE_ABSTRACT_NODE_H
#define SEQUENCE_SET_COMMON_NODE_ABSTRACT_NODE_H

#include <utility>

/// @file
/// @brief Base abstrata para nós que armazenam um valor.

/// @brief Base para os nós que armazenam um valor.
///
/// O construtor é protegido para impedir a instanciação direta da classe; os
/// herdeiros inicializam o valor armazenado. A herança é normalmente privada,
/// pois o valor é exposto pelos métodos definidos nas interfaces derivadas.
///
/// @tparam T Tipo de dado armazenado dentro do nó.
template <class T>
class AbstractNode {
 protected:
  /// Valor armazenado pelo nó.
  T _data;

  /// Inicializa o nó copiando @p data.
  /// @param data Valor a ser armazenado.
  explicit AbstractNode(const T& data) : _data(data) {}

  /// Inicializa o nó movendo @p data.
  /// @param data Valor a ser armazenado; fica em estado válido, mas
  /// indefinido, após a movimentação.
  explicit AbstractNode(T&& data) : _data(std::move(data)) {}

 public:
  /// Destrói o nó, liberando o valor armazenado.
  virtual ~AbstractNode() = default;
};

#endif  // SEQUENCE_SET_COMMON_NODE_ABSTRACT_NODE_H
