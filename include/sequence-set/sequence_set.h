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

/// @file
/// @brief Conjunto de sequências implementado sobre chunks encadeados.

/// @brief Conjunto de sequências armazenado em chunks ordenados.
///
/// A estrutura herda de DoublyLinkedList de forma protegida: os chunks são
/// gerenciados internamente e o usuário acessa o conjunto pela interface
/// pública. Chunks cheios são divididos ao meio durante a inserção, e a
/// ordenação global é preservada pela ordem dos chunks na lista e das chaves
/// dentro de cada chunk.
///
/// @tparam T Tipo dos dados armazenados nos chunks.
template <class T>
class SequenceSet : protected DoublyLinkedList<Chunk<T>>, public SequenceSetInterface<T> {
 private:
  /// Capacidade configurada para cada chunk do conjunto.
  std::size_t _chunkSize;

 public:
  /// Cria um conjunto vazio.
  /// @param chunkSize Capacidade de cada chunk (mínimo 2).
  /// @throw std::invalid_argument Se @p chunkSize for menor que 2.
  explicit SequenceSet(std::size_t chunkSize = 5);

  /// Destrói o conjunto e libera os chunks encadeados.
  ~SequenceSet() override = default;

  /// Cria uma cópia profunda de @p other.
  /// @param other Conjunto de origem.
  SequenceSet(const SequenceSet& other);

  /// Transfere os chunks de @p other, deixando-o vazio.
  /// @param other Conjunto de origem.
  SequenceSet(SequenceSet&& other) noexcept;

  /// Copia os chunks e a configuração de @p other.
  /// @param other Conjunto de origem.
  /// @return Referência para este conjunto.
  SequenceSet& operator=(const SequenceSet& other);

  /// Transfere os chunks e a configuração de @p other.
  /// @param other Conjunto de origem.
  /// @return Referência para este conjunto.
  SequenceSet& operator=(SequenceSet&& other) noexcept;

  /// Insere um par no conjunto, dividindo o chunk quando necessário.
  /// @param key Chave do elemento.
  /// @param data Valor associado à chave.
  /// @throw std::invalid_argument Se a chave já estiver presente.
  void insert(const std::size_t& key, const T& data) override;

  /// Remove o elemento associado a @p key.
  /// @param key Chave do elemento a remover.
  /// @return Par removido.
  /// @throw std::range_error Se a chave não estiver presente.
  Pair<std::size_t, T> remove(std::size_t key) override;

  /// Verifica se o conjunto contém @p key.
  /// @param key Chave procurada.
  /// @return `true` se a chave estiver presente.
  [[nodiscard]] bool contains(std::size_t key) const override;

  /// Retorna o valor associado a @p key.
  /// @param key Chave procurada.
  /// @return Cópia do valor associado.
  /// @throw std::runtime_error Se a chave não estiver presente.
  [[nodiscard]] T find(std::size_t key) const override;

  /// @return Soma das capacidades de todos os chunks.
  [[nodiscard]] std::size_t getCapacity() const override;

  /// @return Soma das quantidades de elementos de todos os chunks.
  [[nodiscard]] std::size_t getSize() const override;

  /// @return Quantidade de chunks que compõem o conjunto.
  [[nodiscard]] std::size_t getChunkCount() const override;

  /// @return Capacidade configurada para cada chunk.
  [[nodiscard]] std::size_t getChunkSize() const override;

  /// Torna público o acesso ao chunk na posição @p index.
  using DoublyLinkedList<Chunk<T>>::operator[];

  /// Torna público o acréscimo de um chunk ao fim do conjunto.
  using DoublyLinkedList<Chunk<T>>::pushBack;

  /// Iterador mutável sobre os chunks do conjunto.
  ///
  /// Percorre os nós da lista encadeada; cada iteração entrega um chunk
  /// completo, cujos pares podem ser percorridos pelos iteradores de Chunk.
  class Iterator {
   private:
    /// Nó da lista que contém o chunk atual.
    DoublyLinkedNodeInterface<Chunk<T>>* _node{};

   public:
    /// Cria um iterador não associado a nenhum chunk.
    Iterator() = default;

    /// Cria um iterador apontando para @p node.
    /// @param node Nó do chunk inicial.
    explicit Iterator(DoublyLinkedNodeInterface<Chunk<T>>* node) : _node(node) {}

    /// @return Referência mutável para o chunk atual.
    [[nodiscard]] Chunk<T>& operator*() const { return _node->getValue(); }

    /// @return Ponteiro para o chunk atual.
    [[nodiscard]] Chunk<T>* operator->() const { return &_node->getValue(); }

    /// Avança para o próximo chunk.
    /// @return Referência para este iterador.
    Iterator& operator++() {
      _node = _node->getNext();
      return *this;
    }

    /// Avança para o próximo chunk, retornando o valor anterior.
    /// @return Cópia do iterador antes do avanço.
    Iterator operator++(int) {
      Iterator copy = *this;
      ++(*this);
      return copy;
    }

    /// @param lhs Iterador da esquerda.
    /// @param rhs Iterador da direita.
    /// @return `true` se ambos apontarem para o mesmo chunk.
    friend bool operator==(const Iterator& lhs, const Iterator& rhs) {
      return lhs._node == rhs._node;
    }

    /// @param lhs Iterador da esquerda.
    /// @param rhs Iterador da direita.
    /// @return `true` se os iteradores apontarem para chunks distintos.
    friend bool operator!=(const Iterator& lhs, const Iterator& rhs) { return !(lhs == rhs); }
  };

  /// Iterador constante sobre os chunks do conjunto.
  ///
  /// Percorre os nós da lista sem permitir alterações nos chunks.
  class ConstIterator {
   private:
    /// Nó da lista que contém o chunk atual.
    const DoublyLinkedNodeInterface<Chunk<T>>* _node{};

   public:
    /// Cria um iterador não associado a nenhum chunk.
    ConstIterator() = default;

    /// Cria um iterador apontando para @p node.
    /// @param node Nó do chunk inicial.
    explicit ConstIterator(const DoublyLinkedNodeInterface<Chunk<T>>* node) : _node(node) {}

    /// @return Referência constante para o chunk atual.
    [[nodiscard]] const Chunk<T>& operator*() const { return _node->getValue(); }

    /// @return Ponteiro constante para o chunk atual.
    [[nodiscard]] const Chunk<T>* operator->() const { return &_node->getValue(); }

    /// Avança para o próximo chunk.
    /// @return Referência para este iterador.
    ConstIterator& operator++() {
      _node = _node->getNext();
      return *this;
    }

    /// Avança para o próximo chunk, retornando o valor anterior.
    /// @return Cópia do iterador antes do avanço.
    ConstIterator operator++(int) {
      ConstIterator copy = *this;
      ++(*this);
      return copy;
    }

    /// @param lhs Iterador da esquerda.
    /// @param rhs Iterador da direita.
    /// @return `true` se ambos apontarem para o mesmo chunk.
    friend bool operator==(const ConstIterator& lhs, const ConstIterator& rhs) {
      return lhs._node == rhs._node;
    }

    /// @param lhs Iterador da esquerda.
    /// @param rhs Iterador da direita.
    /// @return `true` se os iteradores apontarem para chunks distintos.
    friend bool operator!=(const ConstIterator& lhs, const ConstIterator& rhs) {
      return !(lhs == rhs);
    }
  };

  /// Nome público do iterador mutável.
  using iterator = Iterator;

  /// Nome público do iterador constante.
  using const_iterator = ConstIterator;

  /// @return Iterador para o primeiro chunk.
  [[nodiscard]] Iterator begin() { return Iterator(this->_begin); }

  /// @return Iterador constante para o primeiro chunk.
  [[nodiscard]] ConstIterator begin() const { return ConstIterator(this->_begin); }

  /// @return Iterador para o fim do conjunto.
  [[nodiscard]] Iterator end() { return Iterator(nullptr); }

  /// @return Iterador constante para o fim do conjunto.
  [[nodiscard]] ConstIterator end() const { return ConstIterator(nullptr); }
};

#include <sequence-set/sequence_set.tpp>

#endif  // SEQUENCE_SET_SEQUENCE_SET_H
