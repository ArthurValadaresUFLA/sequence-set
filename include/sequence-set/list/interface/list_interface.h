//
// Created by arthur on 19/06/24.
//

#ifndef SEQUENCE_SET_LIST_INTERFACE_LIST_INTERFACE_H
#define SEQUENCE_SET_LIST_INTERFACE_LIST_INTERFACE_H

#include <cstddef>
#include <functional>

/// @brief Interface para uma lista encadeada.
///
/// @tparam T Tipo de dados armazenados na lista.
template <class T>
class ListInterface {
 public:
  virtual ~ListInterface() = default;

  virtual void push(const T& data) = 0;
  virtual void pushBack(const T& data) = 0;
  virtual void insertAt(std::size_t index, const T& data) = 0;

  virtual T removeOnBegin() = 0;
  virtual T removeAtEnd() = 0;
  virtual T removeAt(std::size_t position) = 0;

  [[nodiscard]] virtual bool isEmpty() const = 0;

  /// Retorna a posição da primeira ocorrência de @p data, ou size() caso o
  /// valor não esteja presente.
  [[nodiscard]] virtual std::size_t find(const T& data) const = 0;

  [[nodiscard]] virtual std::size_t size() const = 0;
  [[nodiscard]] virtual bool contains(const T& data) const = 0;

  virtual T& operator[](std::size_t index) = 0;
  [[nodiscard]] virtual const T& operator[](std::size_t index) const = 0;

  virtual void removeWhere(std::function<bool(std::size_t index, T value)> predicate) = 0;
};

#endif  // SEQUENCE_SET_LIST_INTERFACE_LIST_INTERFACE_H
