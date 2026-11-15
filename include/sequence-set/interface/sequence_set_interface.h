//
// Created by arthur on 21/01/25.
//

#ifndef SEQUENCE_SET_INTERFACE_SEQUENCE_SET_INTERFACE_H
#define SEQUENCE_SET_INTERFACE_SEQUENCE_SET_INTERFACE_H

#include <cstddef>

#include <sequence-set/common/chunk/pair.h>

/// @brief Interface para o conjunto de sequências.
///
/// @tparam T Tipo dos dados armazenados no conjunto.
template <class T>
class SequenceSetInterface {
 public:
  virtual ~SequenceSetInterface() = default;

  virtual void insert(const std::size_t& key, const T& data) = 0;
  virtual Pair<std::size_t, T> remove(std::size_t key) = 0;

  [[nodiscard]] virtual bool contains(std::size_t key) const = 0;
  [[nodiscard]] virtual T find(std::size_t key) const = 0;

  [[nodiscard]] virtual std::size_t getCapacity() const = 0;
  [[nodiscard]] virtual std::size_t getSize() const = 0;
  [[nodiscard]] virtual std::size_t getChunkCount() const = 0;
  [[nodiscard]] virtual std::size_t getChunkSize() const = 0;
};

#endif  // SEQUENCE_SET_INTERFACE_SEQUENCE_SET_INTERFACE_H
