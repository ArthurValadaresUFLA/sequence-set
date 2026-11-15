//
// Created by arthur on 23/01/25.
//

#ifndef SEQUENCE_SET_COMMON_CHUNK_PAIR_H
#define SEQUENCE_SET_COMMON_CHUNK_PAIR_H

#include <cstddef>

/// @brief Par chave-valor usado pelos chunks.
///
/// A classe mantém os membros públicos para permitir o uso de *structured
/// bindings* (`const auto &[key, value] : chunk`) sem a necessidade de
/// métodos de acesso adicionais.
///
/// @tparam K Tipo da chave.
/// @tparam V Tipo do valor associado à chave.
template <class K, class V>
class Pair {
 public:
  K key{};
  V data{};

  Pair() = default;
  Pair(const K& key, const V& data) : key(key), data(data) {}
  Pair(const Pair&) = default;
  Pair(Pair&&) noexcept = default;
  Pair& operator=(const Pair&) = default;
  Pair& operator=(Pair&&) noexcept = default;
  ~Pair() = default;

  [[nodiscard]] bool operator==(const Pair& rhs) const {
    return key == rhs.key && data == rhs.data;
  }

  [[nodiscard]] bool operator!=(const Pair& rhs) const { return !(*this == rhs); }
};

#endif  // SEQUENCE_SET_COMMON_CHUNK_PAIR_H
