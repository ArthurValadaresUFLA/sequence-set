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

/// @file
/// @brief Armazenamento contíguo de pares chave-valor.

/// @brief Armazenamento contíguo de pares chave-valor usado por Chunk.
///
/// A classe implementa a regra dos cinco: a memória é alocada no construtor e
/// liberada no destrutor; a cópia é profunda e a movimentação transfere a
/// propriedade do array, deixando a origem vazia. A ordenação das chaves é
/// responsabilidade da classe derivada.
///
/// @tparam T Tipo de dado armazenado nos elementos do chunk.
template <class T>
class AbstractChunk {
 protected:
  /// Capacidade máxima de elementos do array.
  std::size_t _capacity{};

  /// Quantidade de elementos atualmente armazenados.
  std::size_t _size{};

  /// Array contíguo de pares chave-valor.
  Pair<std::size_t, T>* _data{};

  /// Aloca um array de @p capacity pares.
  /// @param capacity Quantidade de elementos a alocar.
  /// @return Ponteiro para o array, ou nullptr quando @p capacity é zero.
  static Pair<std::size_t, T>* allocate(std::size_t capacity) {
    return capacity == 0 ? nullptr : new Pair<std::size_t, T>[capacity];
  }

 public:
  /// Cria um chunk vazio com a capacidade informada.
  /// @param capacity Capacidade máxima de elementos.
  explicit AbstractChunk(std::size_t capacity)
      : _capacity(capacity), _size(0), _data(allocate(capacity)) {}

  /// Copia os elementos do intervalo inclusivo [@p begin, @p end].
  /// @param capacity Capacidade máxima do novo chunk.
  /// @param data Array de origem.
  /// @param begin Índice inicial do intervalo (inclusivo).
  /// @param end Índice final do intervalo (inclusivo).
  /// @throw std::invalid_argument Se o intervalo for inválido, exceder a
  /// capacidade ou se @p data for nulo.
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
  /// @param capacity Capacidade máxima do novo chunk.
  /// @param data Array de origem.
  /// @param end Índice final do intervalo (inclusivo).
  /// @throw std::invalid_argument Se o intervalo for inválido, exceder a
  /// capacidade ou se @p data for nulo.
  AbstractChunk(std::size_t capacity, const Pair<std::size_t, T>* data, std::size_t end)
      : AbstractChunk(capacity, data, 0, end) {}

  /// Cria uma cópia profunda de @p other.
  /// @param other Chunk de origem.
  AbstractChunk(const AbstractChunk& other)
      : _capacity(other._capacity), _size(other._size), _data(allocate(other._capacity)) {
    if (_size != 0) {
      std::copy(other._data, other._data + other._size, _data);
    }
  }

  /// Transfere o array de @p other, deixando-a vazia.
  /// @param other Chunk de origem.
  AbstractChunk(AbstractChunk&& other) noexcept
      : _capacity(std::exchange(other._capacity, 0)),
        _size(std::exchange(other._size, 0)),
        _data(std::exchange(other._data, nullptr)) {}

  /// Copia os elementos de @p other usando a técnica copy-and-swap.
  /// @param other Chunk de origem.
  /// @return Referência para este chunk.
  AbstractChunk& operator=(const AbstractChunk& other) {
    if (this != &other) {
      AbstractChunk copy(other);
      swap(copy);
    }
    return *this;
  }

  /// Move os elementos de @p other usando a técnica move-and-swap.
  /// @param other Chunk de origem.
  /// @return Referência para este chunk.
  AbstractChunk& operator=(AbstractChunk&& other) noexcept {
    if (this != &other) {
      AbstractChunk moved(std::move(other));
      swap(moved);
    }
    return *this;
  }

  /// Libera o array de elementos.
  virtual ~AbstractChunk() { delete[] _data; }

  /// Troca capacidade, tamanho e array com @p other em tempo constante.
  /// @param other Chunk com o qual o estado será trocado.
  void swap(AbstractChunk& other) noexcept {
    std::swap(_capacity, other._capacity);
    std::swap(_size, other._size);
    std::swap(_data, other._data);
  }
};

#endif  // SEQUENCE_SET_COMMON_CHUNK_ABSTRACT_CHUNK_H
