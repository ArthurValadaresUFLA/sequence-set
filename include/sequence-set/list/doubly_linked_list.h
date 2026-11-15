//
// Created by arthur on 20/06/24.
//

#ifndef SEQUENCE_SET_LIST_DOUBLY_LINKED_LIST_H
#define SEQUENCE_SET_LIST_DOUBLY_LINKED_LIST_H

#include <cstddef>
#include <functional>

#include <sequence-set/common/node/doubly_linked_node.h>
#include <sequence-set/list/abstract_doubly_linked_list.h>
#include <sequence-set/list/interface/list_interface.h>

/// @brief Lista duplamente encadeada.
///
/// A lista é dona dos nós que armazena: todos são alocados dinamicamente e
/// liberados pelo destrutor, pelas remoções e pela atribuição. A classe segue
/// a regra dos cinco: a cópia é profunda e a movimentação transfere a posse dos
/// nós, deixando a origem vazia.
///
/// @tparam T Tipo dos elementos armazenados na lista.
template <class T>
class DoublyLinkedList : protected AbstractDoublyLinkedList<T>, public ListInterface<T> {
 public:
  DoublyLinkedList() : AbstractDoublyLinkedList<T>(nullptr, nullptr) {}

  DoublyLinkedList(const DoublyLinkedList& other);
  DoublyLinkedList(DoublyLinkedList&& other) noexcept;

  /// Atribuição por cópia e por movimentação (copy-and-swap).
  DoublyLinkedList& operator=(DoublyLinkedList other) noexcept;

  ~DoublyLinkedList() override;

  /// Troca o conteúdo desta lista com o de @p other em tempo constante.
  void swap(DoublyLinkedList& other) noexcept;

  /// Remove todos os nós da lista.
  void clear() noexcept;

  [[nodiscard]] T& operator[](std::size_t index) override;
  [[nodiscard]] const T& operator[](std::size_t index) const override;

  [[nodiscard]] std::size_t find(const T& data) const override;
  [[nodiscard]] std::size_t size() const override;
  [[nodiscard]] bool contains(const T& data) const override;

  void push(const T& data) override;
  void pushBack(const T& data) override;
  void insertAt(std::size_t index, const T& data) override;

  T removeOnBegin() override;
  T removeAtEnd() override;
  T removeAt(std::size_t position) override;

  [[nodiscard]] bool isEmpty() const override;

  void removeWhere(std::function<bool(std::size_t index, T value)> predicate) override;
};

#include <sequence-set/list/doubly_linked_list.tpp>

#endif  // SEQUENCE_SET_LIST_DOUBLY_LINKED_LIST_H
