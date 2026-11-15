//
// Created by arthur on 21/01/25.
//

#ifndef SEQUENCE_SET_SEQUENCE_SET_H
#define SEQUENCE_SET_SEQUENCE_SET_H

#include <cstddef>

#include <sequence-set/common/chunk/chunk.h>
#include <sequence-set/common/node/interface/doubly_linked_node_interface.h>
#include <sequence-set/interface/sequence_set_interface.h>
#include <sequence-set/list/doubly_linked_list.h>

/// @brief Conjunto de sequências armazenado em chunks ordenados.
///
/// A estrutura herda de DoublyLinkedList de forma protegida: os chunks são
/// gerenciados internamente e o usuário acessa o conjunto pela interface
/// pública. Chunks cheios são divididos ao meio durante a inserção.
///
/// @tparam T Tipo dos dados armazenados nos chunks.
template <class T>
class SequenceSet : protected DoublyLinkedList<Chunk<T>>, public SequenceSetInterface<T> {
 private:
  std::size_t _chunkSize;

 public:
  /// @param chunkSize Capacidade de cada chunk (mínimo 2).
  explicit SequenceSet(std::size_t chunkSize = 5);

  ~SequenceSet() override = default;

  SequenceSet(const SequenceSet& other);
  SequenceSet(SequenceSet&& other) noexcept;
  SequenceSet& operator=(const SequenceSet& other);
  SequenceSet& operator=(SequenceSet&& other) noexcept;

  void insert(const std::size_t& key, const T& data) override;
  Pair<std::size_t, T> remove(std::size_t key) override;

  [[nodiscard]] bool contains(std::size_t key) const override;
  [[nodiscard]] T find(std::size_t key) const override;

  [[nodiscard]] std::size_t getCapacity() const override;
  [[nodiscard]] std::size_t getSize() const override;
  [[nodiscard]] std::size_t getChunkCount() const override;
  [[nodiscard]] std::size_t getChunkSize() const override;

  using DoublyLinkedList<Chunk<T>>::operator[];
  using DoublyLinkedList<Chunk<T>>::pushBack;

  /// Iterador mutável sobre os chunks do conjunto.
  class Iterator {
   private:
    DoublyLinkedNodeInterface<Chunk<T>>* _node{};

   public:
    Iterator() = default;
    explicit Iterator(DoublyLinkedNodeInterface<Chunk<T>>* node) : _node(node) {}

    [[nodiscard]] Chunk<T>& operator*() const { return _node->getValue(); }
    [[nodiscard]] Chunk<T>* operator->() const { return &_node->getValue(); }

    Iterator& operator++() {
      _node = _node->getNext();
      return *this;
    }

    Iterator operator++(int) {
      Iterator copy = *this;
      ++(*this);
      return copy;
    }

    friend bool operator==(const Iterator& lhs, const Iterator& rhs) {
      return lhs._node == rhs._node;
    }

    friend bool operator!=(const Iterator& lhs, const Iterator& rhs) { return !(lhs == rhs); }
  };

  /// Iterador constante sobre os chunks do conjunto.
  class ConstIterator {
   private:
    const DoublyLinkedNodeInterface<Chunk<T>>* _node{};

   public:
    ConstIterator() = default;
    explicit ConstIterator(const DoublyLinkedNodeInterface<Chunk<T>>* node) : _node(node) {}

    [[nodiscard]] const Chunk<T>& operator*() const { return _node->getValue(); }
    [[nodiscard]] const Chunk<T>* operator->() const { return &_node->getValue(); }

    ConstIterator& operator++() {
      _node = _node->getNext();
      return *this;
    }

    ConstIterator operator++(int) {
      ConstIterator copy = *this;
      ++(*this);
      return copy;
    }

    friend bool operator==(const ConstIterator& lhs, const ConstIterator& rhs) {
      return lhs._node == rhs._node;
    }

    friend bool operator!=(const ConstIterator& lhs, const ConstIterator& rhs) {
      return !(lhs == rhs);
    }
  };

  using iterator = Iterator;
  using const_iterator = ConstIterator;

  [[nodiscard]] Iterator begin() { return Iterator(this->_begin); }
  [[nodiscard]] ConstIterator begin() const { return ConstIterator(this->_begin); }
  [[nodiscard]] Iterator end() { return Iterator(nullptr); }
  [[nodiscard]] ConstIterator end() const { return ConstIterator(nullptr); }
};

#include <sequence-set/sequence_set.tpp>

#endif  // SEQUENCE_SET_SEQUENCE_SET_H
