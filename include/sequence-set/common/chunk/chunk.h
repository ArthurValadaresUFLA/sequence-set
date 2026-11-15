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

/// @file
/// @brief Contêiner ordenado de pares chave-valor com capacidade fixa.

/// @brief Contêiner genérico ordenado por chave.
///
/// Um chunk mantém os pares ordenados pela chave e possui capacidade fixa. As
/// operações de busca são lineares; a inserção e a remoção deslocam os
/// elementos necessários para preservar a ordenação. Quando um chunk fica
/// cheio, `halve()` o divide em duas metades utilizáveis pelo SequenceSet.
///
/// @tparam T Tipo dos dados armazenados no chunk.
template <class T>
class Chunk : public AbstractChunk<T>, public ChunkInterface<T> {
 private:
  /// Verifica se há espaço disponível para uma nova inserção.
  /// @throw std::runtime_error Se o chunk estiver cheio.
  void checkCapacity() const;

  /// Insere um par em uma posição específica, deslocando os sucessores.
  /// @param index Posição de inserção.
  /// @param pair Par a ser inserido.
  /// @throw std::out_of_range Se @p index for maior que o tamanho atual.
  /// @throw std::runtime_error Se o chunk estiver cheio.
  void insertAt(std::size_t index, const Pair<std::size_t, T>& pair);

 public:
  /// Cria um chunk vazio com a capacidade informada.
  /// @param capacity Capacidade máxima de elementos.
  explicit Chunk(std::size_t capacity);

  /// Copia os elementos do intervalo inclusivo [@p begin, @p end].
  /// @param capacity Capacidade máxima do novo chunk.
  /// @param data Array de origem.
  /// @param begin Índice inicial do intervalo.
  /// @param end Índice final do intervalo.
  Chunk(std::size_t capacity, const Pair<std::size_t, T>* data, std::size_t begin, std::size_t end);

  /// Copia os elementos do intervalo inclusivo [0, @p end].
  /// @param capacity Capacidade máxima do novo chunk.
  /// @param data Array de origem.
  /// @param end Índice final do intervalo.
  Chunk(std::size_t capacity, const Pair<std::size_t, T>* data, std::size_t end);

  /// Destrói o chunk e libera o array de elementos.
  ~Chunk() override = default;

  /// Copia profundamente @p other.
  Chunk(const Chunk&) = default;

  /// Transfere os elementos de @p other, deixando-o vazio.
  Chunk(Chunk&&) noexcept = default;

  /// Copia profundamente @p other.
  /// @return Referência para este chunk.
  Chunk& operator=(const Chunk&) = default;

  /// Transfere os elementos de @p other, deixando-o vazio.
  /// @return Referência para este chunk.
  Chunk& operator=(Chunk&&) noexcept = default;

  /// Insere um elemento, preservando a ordenação.
  /// @param key Chave do elemento.
  /// @param data Valor associado à chave.
  /// @throw std::runtime_error Se o chunk estiver cheio.
  /// @throw std::invalid_argument Se a chave já estiver presente.
  void insert(const std::size_t& key, const T& data) override;

  /// Remove o elemento associado a @p key.
  /// @param key Chave do elemento a remover.
  /// @return Par removido.
  /// @throw std::range_error Se a chave não estiver presente.
  Pair<std::size_t, T> remove(const std::size_t& key) override;

  /// Retorna o valor associado a @p key.
  /// @param key Chave procurada.
  /// @return Cópia do valor associado.
  /// @throw std::range_error Se a chave não estiver presente.
  [[nodiscard]] T find(const std::size_t& key) const override;

  /// Verifica se o chunk contém @p key.
  /// @param key Chave procurada.
  /// @return `true` se a chave estiver presente.
  [[nodiscard]] bool contains(const std::size_t& key) const override;

  /// @return Capacidade máxima de elementos.
  [[nodiscard]] std::size_t getCapacity() override;

  /// @return Capacidade máxima de elementos.
  [[nodiscard]] const std::size_t& getCapacity() const override;

  /// @return Quantidade de elementos armazenados.
  [[nodiscard]] std::size_t getSize() override;

  /// @return Quantidade de elementos armazenados.
  [[nodiscard]] const std::size_t& getSize() const override;

  /// @return Metade da capacidade do chunk.
  [[nodiscard]] std::size_t getMinSize() const override;

  /// @return `true` se o chunk não puder receber novos elementos.
  [[nodiscard]] bool isFull() const override;

  /// Retorna o primeiro par chave-valor.
  /// @return Cópia do primeiro par.
  /// @throw std::range_error Se o chunk estiver vazio.
  [[nodiscard]] Pair<std::size_t, T> first() const override;

  /// Retorna o último par chave-valor.
  /// @return Cópia do último par.
  /// @throw std::range_error Se o chunk estiver vazio.
  [[nodiscard]] Pair<std::size_t, T> last() const override;

  /// Acessa o par na posição @p index.
  /// @param index Posição do elemento.
  /// @return Cópia do par armazenado.
  /// @throw std::out_of_range Se @p index for maior ou igual ao tamanho.
  Pair<std::size_t, T> operator[](const std::size_t& index) override;

  /// Acessa o par na posição @p index.
  /// @param index Posição do elemento.
  /// @return Referência constante para o par armazenado.
  /// @throw std::out_of_range Se @p index for maior ou igual ao tamanho.
  const Pair<std::size_t, T>& operator[](const std::size_t& index) const override;

  /// Divide o chunk em duas metades, preservando a ordenação.
  ///
  /// A primeira metade recebe os `size() / 2` primeiros elementos e a segunda
  /// os elementos restantes. O chunk original não é alterado.
  ///
  /// @return Par `(metade esquerda, metade direita)`.
  /// @throw std::logic_error Se o chunk tiver menos de dois elementos.
  std::pair<Chunk<T>, Chunk<T>> halve();

  /// Compara capacidade, tamanho e elementos de dois chunks.
  /// @param other Chunk comparado.
  /// @return `true` se os chunks forem iguais.
  [[nodiscard]] bool operator==(const Chunk<T>& other) const;

  /// Iterador mutável sobre os pares do chunk.
  ///
  /// Percorre o array interno na ordem das chaves, de `begin()` até `end()`.
  class Iterator {
   public:
    /// Categoria do iterador (forward iterator).
    using iterator_category = std::forward_iterator_tag;

    /// Tipo da diferença entre iteradores.
    using difference_type = std::ptrdiff_t;

    /// Tipo do elemento apontado.
    using value_type = Pair<std::size_t, T>;

    /// Tipo do ponteiro para o elemento.
    using pointer = value_type*;

    /// Tipo da referência para o elemento.
    using reference = value_type&;

    /// Cria um iterador não associado a nenhum elemento.
    Iterator() = default;

    /// Cria um iterador apontando para @p ptr.
    /// @param ptr Ponteiro para o elemento inicial.
    explicit Iterator(pointer ptr) : _ptr(ptr) {}

    /// @return Referência mutável para o elemento atual.
    [[nodiscard]] reference operator*() const { return *_ptr; }

    /// @return Ponteiro para o elemento atual.
    [[nodiscard]] pointer operator->() const { return _ptr; }

    /// Avança para o próximo elemento.
    /// @return Referência para este iterador.
    Iterator& operator++() {
      ++_ptr;
      return *this;
    }

    /// Avança para o próximo elemento, retornando o valor anterior.
    /// @return Cópia do iterador antes do avanço.
    Iterator operator++(int) {
      Iterator copy = *this;
      ++(*this);
      return copy;
    }

    /// @param lhs Iterador da esquerda.
    /// @param rhs Iterador da direita.
    /// @return `true` se ambos apontarem para o mesmo elemento.
    friend bool operator==(const Iterator& lhs, const Iterator& rhs) {
      return lhs._ptr == rhs._ptr;
    }

    /// @param lhs Iterador da esquerda.
    /// @param rhs Iterador da direita.
    /// @return `true` se os iteradores apontarem para elementos distintos.
    friend bool operator!=(const Iterator& lhs, const Iterator& rhs) { return !(lhs == rhs); }

   private:
    /// Ponteiro para o elemento atual.
    pointer _ptr{};
  };

  /// Iterador constante sobre os pares do chunk.
  ///
  /// Percorre o array interno na ordem das chaves sem permitir alterações.
  class ConstIterator {
   public:
    /// Categoria do iterador (forward iterator).
    using iterator_category = std::forward_iterator_tag;

    /// Tipo da diferença entre iteradores.
    using difference_type = std::ptrdiff_t;

    /// Tipo do elemento apontado.
    using value_type = const Pair<std::size_t, T>;

    /// Tipo do ponteiro para o elemento.
    using pointer = value_type*;

    /// Tipo da referência para o elemento.
    using reference = value_type&;

    /// Cria um iterador não associado a nenhum elemento.
    ConstIterator() = default;

    /// Cria um iterador apontando para @p ptr.
    /// @param ptr Ponteiro para o elemento inicial.
    explicit ConstIterator(pointer ptr) : _ptr(ptr) {}

    /// @return Referência constante para o elemento atual.
    [[nodiscard]] reference operator*() const { return *_ptr; }

    /// @return Ponteiro constante para o elemento atual.
    [[nodiscard]] pointer operator->() const { return _ptr; }

    /// Avança para o próximo elemento.
    /// @return Referência para este iterador.
    ConstIterator& operator++() {
      ++_ptr;
      return *this;
    }

    /// Avança para o próximo elemento, retornando o valor anterior.
    /// @return Cópia do iterador antes do avanço.
    ConstIterator operator++(int) {
      ConstIterator copy = *this;
      ++(*this);
      return copy;
    }

    /// @param lhs Iterador da esquerda.
    /// @param rhs Iterador da direita.
    /// @return `true` se ambos apontarem para o mesmo elemento.
    friend bool operator==(const ConstIterator& lhs, const ConstIterator& rhs) {
      return lhs._ptr == rhs._ptr;
    }

    /// @param lhs Iterador da esquerda.
    /// @param rhs Iterador da direita.
    /// @return `true` se os iteradores apontarem para elementos distintos.
    friend bool operator!=(const ConstIterator& lhs, const ConstIterator& rhs) {
      return !(lhs == rhs);
    }

   private:
    /// Ponteiro para o elemento atual.
    pointer _ptr{};
  };

  /// Nome público do iterador mutável.
  using iterator = Iterator;

  /// Nome público do iterador constante.
  using const_iterator = ConstIterator;

  /// @return Iterador para o primeiro elemento.
  [[nodiscard]] Iterator begin() { return Iterator(this->_data); }

  /// @return Iterador constante para o primeiro elemento.
  [[nodiscard]] ConstIterator begin() const { return ConstIterator(this->_data); }

  /// @return Iterador para o fim do chunk.
  [[nodiscard]] Iterator end() { return Iterator(this->_data + this->_size); }

  /// @return Iterador constante para o fim do chunk.
  [[nodiscard]] ConstIterator end() const { return ConstIterator(this->_data + this->_size); }
};

#include <sequence-set/common/chunk/chunk.tpp>

#endif  // SEQUENCE_SET_COMMON_CHUNK_CHUNK_H
