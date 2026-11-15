//
// Created by arthur on 21/01/25.
//

#ifndef SEQUENCE_SET_INTERFACE_SEQUENCE_SET_INTERFACE_H
#define SEQUENCE_SET_INTERFACE_SEQUENCE_SET_INTERFACE_H

#include <cstddef>

#include <sequence-set/common/chunk/pair.h>

/// @file
/// @brief Contrato para o conjunto de sequências.

/// @brief Interface para o conjunto de sequências.
///
/// O conjunto mantém pares chave-valor distribuídos em chunks ordenados,
/// expondo operações de busca, inserção e remoção por chave. A implementação
/// concreta gerencia a divisão de chunks cheios.
///
/// @tparam T Tipo dos dados armazenados no conjunto.
template <class T>
class SequenceSetInterface {
 public:
  /// Destrói a interface; a posse dos chunks é da implementação.
  virtual ~SequenceSetInterface() = default;

  /// Insere um par no conjunto, preservando a ordenação.
  /// @param key Chave do elemento.
  /// @param data Valor associado à chave.
  virtual void insert(const std::size_t& key, const T& data) = 0;

  /// Remove o elemento associado a @p key.
  /// @param key Chave do elemento a remover.
  /// @return Par removido.
  virtual Pair<std::size_t, T> remove(std::size_t key) = 0;

  /// Verifica se o conjunto contém @p key.
  /// @param key Chave procurada.
  /// @return `true` se a chave estiver presente.
  [[nodiscard]] virtual bool contains(std::size_t key) const = 0;

  /// Retorna o valor associado a @p key.
  /// @param key Chave procurada.
  /// @return Cópia do valor associado.
  [[nodiscard]] virtual T find(std::size_t key) const = 0;

  /// @return Soma das capacidades de todos os chunks.
  [[nodiscard]] virtual std::size_t getCapacity() const = 0;

  /// @return Soma das quantidades de elementos de todos os chunks.
  [[nodiscard]] virtual std::size_t getSize() const = 0;

  /// @return Quantidade de chunks que compõem o conjunto.
  [[nodiscard]] virtual std::size_t getChunkCount() const = 0;

  /// @return Capacidade configurada para cada chunk.
  [[nodiscard]] virtual std::size_t getChunkSize() const = 0;
};

#endif  // SEQUENCE_SET_INTERFACE_SEQUENCE_SET_INTERFACE_H
