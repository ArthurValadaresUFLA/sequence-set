//
// Created by arthur on 21/01/25.
//

#ifndef SEQUENCE_SET_COMMON_CHUNK_INTERFACE_CHUNK_INTERFACE_H
#define SEQUENCE_SET_COMMON_CHUNK_INTERFACE_CHUNK_INTERFACE_H

#include <cstddef>

#include <sequence-set/common/chunk/pair.h>

/// @brief Interface genérica para representação e manipulação de chunks.
///
/// @tparam T Tipo de dado armazenado no chunk.
template <class T>
class ChunkInterface {
 public:
  virtual ~ChunkInterface() = default;

  /// Insere um novo elemento no chunk.
  virtual void insert(const std::size_t& key, const T& data) = 0;

  /// Remove o elemento associado a @p key e o retorna.
  virtual Pair<std::size_t, T> remove(const std::size_t& key) = 0;

  /// Retorna o primeiro par chave-valor do chunk.
  [[nodiscard]] virtual Pair<std::size_t, T> first() const = 0;

  /// Retorna o último par chave-valor do chunk.
  [[nodiscard]] virtual Pair<std::size_t, T> last() const = 0;

  /// Retorna o valor associado a @p key.
  [[nodiscard]] virtual T find(const std::size_t& key) const = 0;

  /// Verifica se o chunk contém @p key.
  [[nodiscard]] virtual bool contains(const std::size_t& key) const = 0;

  /// Retorna a capacidade total do chunk.
  [[nodiscard]] virtual std::size_t getCapacity() = 0;
  [[nodiscard]] virtual const std::size_t& getCapacity() const = 0;

  /// Retorna a quantidade atual de elementos do chunk.
  [[nodiscard]] virtual std::size_t getSize() = 0;
  [[nodiscard]] virtual const std::size_t& getSize() const = 0;

  /// Verifica se o chunk está cheio.
  [[nodiscard]] virtual bool isFull() const = 0;

  /// Retorna o tamanho mínimo desejável de um chunk.
  [[nodiscard]] virtual std::size_t getMinSize() const = 0;

  /// Acessa o par chave-valor na posição @p index.
  virtual Pair<std::size_t, T> operator[](const std::size_t& index) = 0;
  virtual const Pair<std::size_t, T>& operator[](const std::size_t& index) const = 0;
};

#endif  // SEQUENCE_SET_COMMON_CHUNK_INTERFACE_CHUNK_INTERFACE_H
