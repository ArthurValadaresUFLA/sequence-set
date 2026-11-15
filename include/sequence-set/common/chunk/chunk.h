//
// Created by arthur on 21/01/25.
//

#ifndef SEQUENCE_SET_COMMON_CHUNK_CHUNK_H
#define SEQUENCE_SET_COMMON_CHUNK_CHUNK_H

#include <cstddef>
#include <iterator>
#include <stdexcept>
#include <utility>

#include <sequence-set/common/chunk/abstract_chunk.h>
#include <sequence-set/common/chunk/interface/chunk_interface.h>
#include <sequence-set/common/chunk/pair.h>

/// @brief Contêiner genérico ordenado por chave.
///
/// Um chunk mantém os pares ordenados pela chave e possui capacidade fixa. As
/// operações de busca são lineares; a inserção e a remoção deslocam os
/// elementos necessários para preservar a ordenação.
///
/// @tparam T Tipo dos dados armazenados no chunk.
template <class T>
class Chunk : public AbstractChunk<T>, public ChunkInterface<T> {
 private:
  void checkCapacity() const;
  void insertAt(std::size_t index, const Pair<std::size_t, T>& pair);

 public:
  explicit Chunk(std::size_t capacity);
  Chunk(std::size_t capacity, const Pair<std::size_t, T>* data, std::size_t begin, std::size_t end);
  Chunk(std::size_t capacity, const Pair<std::size_t, T>* data, std::size_t end);

  ~Chunk() override = default;
  Chunk(const Chunk&) = default;
  Chunk(Chunk&&) noexcept = default;
  Chunk& operator=(const Chunk&) = default;
  Chunk& operator=(Chunk&&) noexcept = default;

  void insert(const std::size_t& key, const T& data) override;
  Pair<std::size_t, T> remove(const std::size_t& key) override;
  [[nodiscard]] T find(const std::size_t& key) const override;
  [[nodiscard]] bool contains(const std::size_t& key) const override;

  [[nodiscard]] std::size_t getCapacity() override;
  [[nodiscard]] const std::size_t& getCapacity() const override;
  [[nodiscard]] std::size_t getSize() override;
  [[nodiscard]] const std::size_t& getSize() const override;
  [[nodiscard]] std::size_t getMinSize() const override;
  [[nodiscard]] bool isFull() const override;
  [[nodiscard]] Pair<std::size_t, T> first() const override;
  [[nodiscard]] Pair<std::size_t, T> last() const override;

  Pair<std::size_t, T> operator[](const std::size_t& index) override;
  const Pair<std::size_t, T>& operator[](const std::size_t& index) const override;

  /// Divide o chunk em duas metades, preservando a ordenação.
  ///
  /// @throw std::logic_error Se o chunk tiver menos de dois elementos.
  std::pair<Chunk<T>, Chunk<T>> halve();

  [[nodiscard]] bool operator==(const Chunk<T>& other) const;

  /// Iterador mutável sobre os pares do chunk.
  class Iterator {
   public:
    using iterator_category = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = Pair<std::size_t, T>;
    using pointer = value_type*;
    using reference = value_type&;

    Iterator() = default;
    explicit Iterator(pointer ptr) : _ptr(ptr) {}

    [[nodiscard]] reference operator*() const { return *_ptr; }
    [[nodiscard]] pointer operator->() const { return _ptr; }

    Iterator& operator++() {
      ++_ptr;
      return *this;
    }

    Iterator operator++(int) {
      Iterator copy = *this;
      ++(*this);
      return copy;
    }

    friend bool operator==(const Iterator& lhs, const Iterator& rhs) {
      return lhs._ptr == rhs._ptr;
    }

    friend bool operator!=(const Iterator& lhs, const Iterator& rhs) { return !(lhs == rhs); }

   private:
    pointer _ptr{};
  };

  /// Iterador constante sobre os pares do chunk.
  class ConstIterator {
   public:
    using iterator_category = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = const Pair<std::size_t, T>;
    using pointer = value_type*;
    using reference = value_type&;

    ConstIterator() = default;
    explicit ConstIterator(pointer ptr) : _ptr(ptr) {}

    [[nodiscard]] reference operator*() const { return *_ptr; }
    [[nodiscard]] pointer operator->() const { return _ptr; }

    ConstIterator& operator++() {
      ++_ptr;
      return *this;
    }

    ConstIterator operator++(int) {
      ConstIterator copy = *this;
      ++(*this);
      return copy;
    }

    friend bool operator==(const ConstIterator& lhs, const ConstIterator& rhs) {
      return lhs._ptr == rhs._ptr;
    }

    friend bool operator!=(const ConstIterator& lhs, const ConstIterator& rhs) {
      return !(lhs == rhs);
    }

   private:
    pointer _ptr{};
  };

  using iterator = Iterator;
  using const_iterator = ConstIterator;

  [[nodiscard]] Iterator begin() { return Iterator(this->_data); }
  [[nodiscard]] ConstIterator begin() const { return ConstIterator(this->_data); }
  [[nodiscard]] Iterator end() { return Iterator(this->_data + this->_size); }
  [[nodiscard]] ConstIterator end() const { return ConstIterator(this->_data + this->_size); }
};

#include <sequence-set/common/chunk/chunk.tpp>

#endif  // SEQUENCE_SET_COMMON_CHUNK_CHUNK_H
