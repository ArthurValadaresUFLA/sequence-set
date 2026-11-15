//
// Created by arthur on 21/01/25.
//

#ifndef SEQUENCE_SET_COMMON_CHUNK_ABSTRACT_CHUNK_H
#define SEQUENCE_SET_COMMON_CHUNK_ABSTRACT_CHUNK_H

#include <algorithm>
#include <cstddef>
#include <stdexcept>
#include <utility>

#include <sequence-set/common/chunk/pair.h>

/// @brief Armazenamento contíguo de pares chave-valor usado por Chunk.
///
/// A classe implementa a regra dos cinco: a memória é alocada no construtor e
/// liberada no destrutor; a cópia é profunda e a movimentação transfere a
/// propriedade do array, deixando a origem vazia.
///
/// @tparam T Tipo de dado armazenado nos elementos do chunk.
template <class T>
class AbstractChunk {
 protected:
  std::size_t _capacity{};
  std::size_t _size{};
  Pair<std::size_t, T>* _data{};

  static Pair<std::size_t, T>* allocate(std::size_t capacity) {
    return capacity == 0 ? nullptr : new Pair<std::size_t, T>[capacity];
  }

 public:
  /// Cria um chunk vazio com a capacidade informada.
  explicit AbstractChunk(std::size_t capacity)
      : _capacity(capacity), _size(0), _data(allocate(capacity)) {}

  /// Copia os elementos do intervalo inclusivo [@p begin, @p end].
  AbstractChunk(std::size_t capacity, const Pair<std::size_t, T>* data, std::size_t begin,
                std::size_t end)
      : _capacity(capacity), _size(0), _data(allocate(capacity)) {
    if (begin > end) {
      throw std::invalid_argument("begin não pode ser maior que end");
    }

    _size = end - begin + 1;
    if (_size > _capacity) {
      throw std::invalid_argument("o intervalo excede a capacidade do chunk");
    }

    if (data == nullptr) {
      throw std::invalid_argument("data não pode ser nulo");
    }

    std::copy(data + begin, data + end + 1, _data);
  }

  /// Copia os elementos do intervalo inclusivo [0, @p end].
  AbstractChunk(std::size_t capacity, const Pair<std::size_t, T>* data, std::size_t end)
      : AbstractChunk(capacity, data, 0, end) {}

  AbstractChunk(const AbstractChunk& other)
      : _capacity(other._capacity), _size(other._size), _data(allocate(other._capacity)) {
    if (_size != 0) {
      std::copy(other._data, other._data + other._size, _data);
    }
  }

  AbstractChunk(AbstractChunk&& other) noexcept
      : _capacity(std::exchange(other._capacity, 0)),
        _size(std::exchange(other._size, 0)),
        _data(std::exchange(other._data, nullptr)) {}

  AbstractChunk& operator=(const AbstractChunk& other) {
    if (this != &other) {
      AbstractChunk copy(other);
      swap(copy);
    }
    return *this;
  }

  AbstractChunk& operator=(AbstractChunk&& other) noexcept {
    if (this != &other) {
      AbstractChunk moved(std::move(other));
      swap(moved);
    }
    return *this;
  }

  virtual ~AbstractChunk() { delete[] _data; }

  void swap(AbstractChunk& other) noexcept {
    std::swap(_capacity, other._capacity);
    std::swap(_size, other._size);
    std::swap(_data, other._data);
  }
};

#endif  // SEQUENCE_SET_COMMON_CHUNK_ABSTRACT_CHUNK_H
