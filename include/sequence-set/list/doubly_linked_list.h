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

/// @file
/// @brief Implementação da lista duplamente encadeada.

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
  /// Cria uma lista vazia.
  DoublyLinkedList() : AbstractDoublyLinkedList<T>(nullptr, nullptr) {}

  /// Cria uma cópia profunda de @p other.
  /// @param other Lista de origem.
  DoublyLinkedList(const DoublyLinkedList& other);

  /// Transfere os nós de @p other, deixando-a vazia.
  /// @param other Lista de origem.
  DoublyLinkedList(DoublyLinkedList&& other) noexcept;

  /// Atribuição por cópia e por movimentação (copy-and-swap).
  /// @param other Lista a ser atribuída; é consumida pela troca.
  /// @return Referência para esta lista.
  DoublyLinkedList& operator=(DoublyLinkedList other) noexcept;

  /// Libera todos os nós da lista.
  ~DoublyLinkedList() override;

  /// Troca o conteúdo desta lista com o de @p other em tempo constante.
  /// @param other Lista com a qual o conteúdo será trocado.
  void swap(DoublyLinkedList& other) noexcept;

  /// Remove todos os nós da lista.
  void clear() noexcept;

  /// Acessa o elemento da posição @p index com permissão de alteração.
  /// @param index Posição do elemento.
  /// @return Referência mutável para o elemento.
  [[nodiscard]] T& operator[](std::size_t index) override;

  /// Acessa o elemento da posição @p index sem permissão de alteração.
  /// @param index Posição do elemento.
  /// @return Referência constante para o elemento.
  [[nodiscard]] const T& operator[](std::size_t index) const override;

  /// Retorna a posição da primeira ocorrência de @p data.
  /// @param data Valor procurado.
  /// @return Índice da primeira ocorrência ou `size()` caso ausente.
  [[nodiscard]] std::size_t find(const T& data) const override;

  /// @return Quantidade de elementos armazenados.
  [[nodiscard]] std::size_t size() const override;

  /// @param data Valor procurado.
  /// @return `true` se @p data estiver presente na lista.
  [[nodiscard]] bool contains(const T& data) const override;

  /// Insere @p data no início da lista.
  /// @param data Valor a ser inserido.
  void push(const T& data) override;

  /// Insere @p data no fim da lista.
  /// @param data Valor a ser inserido.
  void pushBack(const T& data) override;

  /// Insere @p data na posição @p index.
  /// @param index Posição de inserção; deve estar em `[0, size()]`.
  /// @param data Valor a ser inserido.
  void insertAt(std::size_t index, const T& data) override;

  /// Remove e retorna o primeiro elemento da lista.
  /// @return Cópia do elemento removido.
  T removeOnBegin() override;

  /// Remove e retorna o último elemento da lista.
  /// @return Cópia do elemento removido.
  T removeAtEnd() override;

  /// Remove e retorna o elemento da posição @p position.
  /// @param position Posição do elemento a remover.
  /// @return Cópia do elemento removido.
  T removeAt(std::size_t position) override;

  /// @return `true` se a lista não contiver elementos.
  [[nodiscard]] bool isEmpty() const override;

  /// Remove os elementos para os quais @p predicate retorna `true`.
  /// @param predicate Função avaliada com o índice e o valor de cada elemento.
  void removeWhere(std::function<bool(std::size_t index, T value)> predicate) override;
};

#include <sequence-set/list/doubly_linked_list.tpp>

#endif  // SEQUENCE_SET_LIST_DOUBLY_LINKED_LIST_H
