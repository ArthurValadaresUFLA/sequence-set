//
// Created by arthur on 19/06/24.
//

#ifndef SEQUENCE_SET_LIST_INTERFACE_LIST_INTERFACE_H
#define SEQUENCE_SET_LIST_INTERFACE_LIST_INTERFACE_H

#include <cstddef>
#include <functional>

/// @file
/// @brief Contrato para listas encadeadas.

/// @brief Interface para uma lista encadeada.
///
/// Define as operações de inserção, remoção, acesso e busca comuns às
/// implementações de lista. A posição 0 corresponde ao início da lista e a
/// posição `size()` ao fim.
///
/// @tparam T Tipo de dados armazenados na lista.
template <class T>
class ListInterface {
 public:
  /// Destrói a interface; a posse dos elementos é da implementação.
  virtual ~ListInterface() = default;

  /// Insere @p data no início da lista.
  /// @param data Valor a ser inserido.
  virtual void push(const T& data) = 0;

  /// Insere @p data no fim da lista.
  /// @param data Valor a ser inserido.
  virtual void pushBack(const T& data) = 0;

  /// Insere @p data na posição @p index.
  /// @param index Posição de inserção; deve estar em `[0, size()]`.
  /// @param data Valor a ser inserido.
  virtual void insertAt(std::size_t index, const T& data) = 0;

  /// Remove e retorna o primeiro elemento da lista.
  /// @return Cópia do elemento removido.
  virtual T removeOnBegin() = 0;

  /// Remove e retorna o último elemento da lista.
  /// @return Cópia do elemento removido.
  virtual T removeAtEnd() = 0;

  /// Remove e retorna o elemento da posição @p position.
  /// @param position Posição do elemento a remover.
  /// @return Cópia do elemento removido.
  virtual T removeAt(std::size_t position) = 0;

  /// @return `true` se a lista não contiver elementos.
  [[nodiscard]] virtual bool isEmpty() const = 0;

  /// Retorna a posição da primeira ocorrência de @p data, ou size() caso o
  /// valor não esteja presente.
  /// @param data Valor procurado.
  /// @return Índice da primeira ocorrência ou `size()`.
  [[nodiscard]] virtual std::size_t find(const T& data) const = 0;

  /// @return Quantidade de elementos armazenados.
  [[nodiscard]] virtual std::size_t size() const = 0;

  /// @param data Valor procurado.
  /// @return `true` se @p data estiver presente na lista.
  [[nodiscard]] virtual bool contains(const T& data) const = 0;

  /// Acessa o elemento da posição @p index com permissão de alteração.
  /// @param index Posição do elemento.
  /// @return Referência mutável para o elemento.
  virtual T& operator[](std::size_t index) = 0;

  /// Acessa o elemento da posição @p index sem permissão de alteração.
  /// @param index Posição do elemento.
  /// @return Referência constante para o elemento.
  [[nodiscard]] virtual const T& operator[](std::size_t index) const = 0;

  /// Remove os elementos para os quais @p predicate retorna `true`.
  /// @param predicate Função avaliada com o índice e o valor de cada elemento.
  virtual void removeWhere(std::function<bool(std::size_t index, T value)> predicate) = 0;
};

#endif  // SEQUENCE_SET_LIST_INTERFACE_LIST_INTERFACE_H
