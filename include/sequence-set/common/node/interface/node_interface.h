//
// Created by arthur on 19/06/24.
//

#ifndef SEQUENCE_SET_COMMON_NODE_INTERFACE_NODE_INTERFACE_H
#define SEQUENCE_SET_COMMON_NODE_INTERFACE_NODE_INTERFACE_H

/// @file
/// @brief Contrato comum aos nós de estruturas encadeadas.

/// @brief Interface para um nó de encadeamento.
///
/// Todo nó armazena um valor e permite acesso ao mesmo por referência
/// constante ou mutável. O encadeamento em si é definido pelas interfaces
/// derivadas, de modo que implementações simplesmente e duplamente encadeadas
/// compartilhem o mesmo contrato de acesso ao valor.
///
/// @tparam T Tipo de dado armazenado dentro do nó.
template <class T>
class NodeInterface {
 public:
  /// Destrói a interface; a posse do nó pertence à estrutura que o contém.
  virtual ~NodeInterface() = default;

  /// Acessa o valor armazenado sem permissão de alteração.
  /// @return Referência constante para o valor do nó.
  [[nodiscard]] virtual const T& getValue() const = 0;

  /// Acessa o valor armazenado com permissão de alteração.
  /// @return Referência mutável para o valor do nó.
  [[nodiscard]] virtual T& getValue() = 0;
};

#endif  // SEQUENCE_SET_COMMON_NODE_INTERFACE_NODE_INTERFACE_H
