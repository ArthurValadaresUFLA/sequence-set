//
// Created by arthur on 23/01/25.
//

#ifndef SEQUENCE_SET_COMMON_CHUNK_PAIR_H
#define SEQUENCE_SET_COMMON_CHUNK_PAIR_H

#include <cstddef>

/// @file
/// @brief Par chave-valor utilizado pelos chunks.

/// @brief Par chave-valor usado pelos chunks.
///
/// A classe mantém os membros públicos para permitir o uso de *structured
/// bindings* (`const auto &[key, value] : chunk`) sem a necessidade de
/// métodos de acesso adicionais. A ordenação do chunk é determinada pela
/// chave; o valor é o dado associado.
///
/// @tparam K Tipo da chave.
/// @tparam V Tipo do valor associado à chave.
template <class K, class V>
class Pair {
 public:
  /// Chave que ordena o elemento dentro do chunk.
  K key{};

  /// Valor associado à chave.
  V data{};

  /// Cria um par com chave e valor inicializados por padrão.
  Pair() = default;

  /// Cria um par a partir de uma chave e um valor.
  /// @param key Chave do elemento.
  /// @param data Valor associado à chave.
  Pair(const K& key, const V& data) : key(key), data(data) {}

  /// Copia a chave e o valor de @p other.
  Pair(const Pair&) = default;

  /// Move a chave e o valor de @p other.
  Pair(Pair&&) noexcept = default;

  /// Copia a chave e o valor de @p other.
  /// @return Referência para este par.
  Pair& operator=(const Pair&) = default;

  /// Move a chave e o valor de @p other.
  /// @return Referência para este par.
  Pair& operator=(Pair&&) noexcept = default;

  /// Destrói o par e seus membros.
  ~Pair() = default;

  /// Compara chave e valor de dois pares.
  /// @param rhs Par comparado.
  /// @return `true` se chave e valor forem iguais.
  [[nodiscard]] bool operator==(const Pair& rhs) const {
    return key == rhs.key && data == rhs.data;
  }

  /// @param rhs Par comparado.
  /// @return `true` se chave ou valor forem diferentes.
  [[nodiscard]] bool operator!=(const Pair& rhs) const { return !(*this == rhs); }
};

#endif  // SEQUENCE_SET_COMMON_CHUNK_PAIR_H
