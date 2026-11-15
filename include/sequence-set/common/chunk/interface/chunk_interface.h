//
// Created by arthur on 21/01/25.
//

#ifndef SEQUENCE_SET_COMMON_CHUNK_INTERFACE_CHUNK_INTERFACE_H
#define SEQUENCE_SET_COMMON_CHUNK_INTERFACE_CHUNK_INTERFACE_H

#include <cstddef>

#include <sequence-set/common/chunk/pair.h>

/// @file
/// @brief Contrato para representação e manipulação de chunks.

/// @brief Interface genérica para representação e manipulação de chunks.
///
/// Um chunk é um contêiner de capacidade fixa que mantém pares chave-valor
/// ordenados pela chave. A interface expõe as operações usadas pelo
/// SequenceSet para localizar, inserir e remover elementos.
///
/// @tparam T Tipo de dado armazenado no chunk.
template <class T>
class ChunkInterface {
 public:
  /// Destrói a interface; a posse dos elementos é da implementação.
  virtual ~ChunkInterface() = default;

  /// Insere um novo elemento no chunk, preservando a ordenação.
  /// @param key Chave do elemento.
  /// @param data Valor associado à chave.
  virtual void insert(const std::size_t& key, const T& data) = 0;

  /// Remove o elemento associado a @p key e o retorna.
  /// @param key Chave do elemento a remover.
  /// @return Par removido.
  virtual Pair<std::size_t, T> remove(const std::size_t& key) = 0;

  /// Retorna o primeiro par chave-valor do chunk.
  /// @return Cópia do primeiro par.
  [[nodiscard]] virtual Pair<std::size_t, T> first() const = 0;

  /// Retorna o último par chave-valor do chunk.
  /// @return Cópia do último par.
  [[nodiscard]] virtual Pair<std::size_t, T> last() const = 0;

  /// Retorna o valor associado a @p key.
  /// @param key Chave procurada.
  /// @return Cópia do valor associado.
  [[nodiscard]] virtual T find(const std::size_t& key) const = 0;

  /// Verifica se o chunk contém @p key.
  /// @param key Chave procurada.
  /// @return `true` se a chave estiver presente.
  [[nodiscard]] virtual bool contains(const std::size_t& key) const = 0;

  /// Retorna a capacidade total do chunk.
  /// @return Capacidade máxima de elementos.
  [[nodiscard]] virtual std::size_t getCapacity() = 0;

  /// @return Capacidade máxima de elementos.
  [[nodiscard]] virtual const std::size_t& getCapacity() const = 0;

  /// Retorna a quantidade atual de elementos do chunk.
  /// @return Quantidade de elementos armazenados.
  [[nodiscard]] virtual std::size_t getSize() = 0;

  /// @return Quantidade de elementos armazenados.
  [[nodiscard]] virtual const std::size_t& getSize() const = 0;

  /// Verifica se o chunk está cheio.
  /// @return `true` se não houver espaço para novos elementos.
  [[nodiscard]] virtual bool isFull() const = 0;

  /// Retorna o tamanho mínimo desejável de um chunk.
  /// @return Metade da capacidade, usada como limite após uma divisão.
  [[nodiscard]] virtual std::size_t getMinSize() const = 0;

  /// Acessa o par chave-valor na posição @p index.
  /// @param index Posição do elemento.
  /// @return Cópia do par armazenado.
  virtual Pair<std::size_t, T> operator[](const std::size_t& index) = 0;

  /// Acessa o par chave-valor na posição @p index.
  /// @param index Posição do elemento.
  /// @return Referência constante para o par armazenado.
  virtual const Pair<std::size_t, T>& operator[](const std::size_t& index) const = 0;
};

#endif  // SEQUENCE_SET_COMMON_CHUNK_INTERFACE_CHUNK_INTERFACE_H
