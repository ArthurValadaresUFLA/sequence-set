//
// Created by arthur on 23/01/25.
//

#ifndef SEQUENCE_SET_ENTRY_ENTRY_H
#define SEQUENCE_SET_ENTRY_ENTRY_H

#include <format>
#include <ostream>
#include <regex>
#include <stdexcept>
#include <string>
#include <utility>

/// @file
/// @brief Modelo de um registro do arquivo CSV.

/// @brief Registro de uma transação/entrada do arquivo CSV.
///
/// A classe agrupa os campos lidos do arquivo, fornece conversão para CSV e
/// mantém a semântica de valor (cópia profunda das strings). A igualdade
/// compara todos os campos, o que permite usar Entry em comparações de
/// chunks e listas.
class Entry {
 private:
  /// Referência temporal do registro.
  int time_ref_{};

  /// Valor monetário associado ao registro.
  double value_{};

  /// Indicador de status do registro (um caractere).
  char status_{};

  /// Conta associada ao registro.
  std::string account_;

  /// Código do produto ou da transação.
  std::string code_;

  /// Código do país de origem/destino.
  std::string country_code_;

  /// Tipo do produto negociado.
  std::string product_type_;

 public:
  /// Cria um registro com todos os campos zerados/vazios.
  Entry() = default;

  /// Cria um registro com os campos informados.
  /// @param time_ref Referência temporal.
  /// @param account Conta associada.
  /// @param code Código do produto ou da transação.
  /// @param country_code Código do país.
  /// @param product_type Tipo do produto.
  /// @param value Valor monetário.
  /// @param status Indicador de status.
  Entry(int time_ref, std::string account, std::string code, std::string country_code,
        std::string product_type, double value, char status);

  /// Copia todos os campos de @p other.
  Entry(const Entry&) = default;

  /// Move os campos de @p other.
  Entry(Entry&&) noexcept = default;

  /// Destrói o registro e suas strings.
  ~Entry() = default;

  /// Copia todos os campos de @p other.
  /// @return Referência para este registro.
  Entry& operator=(const Entry&) = default;

  /// Move os campos de @p other.
  /// @return Referência para este registro.
  Entry& operator=(Entry&&) noexcept = default;

  /// Compara todos os campos de dois registros.
  /// @param other Registro comparado.
  /// @return `true` se todos os campos forem iguais.
  [[nodiscard]] bool operator==(const Entry& other) const;

  /// Cria um Entry a partir de uma linha CSV.
  /// @param csvLine Linha no formato do arquivo de origem.
  /// @return Registro construído a partir dos campos extraídos.
  /// @throw std::runtime_error Se o formato da linha for inválido.
  static Entry fromCSV(const std::string& csvLine);

  /// Converte o Entry para uma linha CSV.
  /// @return Linha CSV com os campos entre aspas quando necessário.
  [[nodiscard]] std::string toCSV() const;

  /// Escreve os campos do registro em @p os, um por linha.
  /// @param os Fluxo de saída.
  /// @param entry Registro a ser impresso.
  /// @return Referência para o fluxo de saída.
  friend std::ostream& operator<<(std::ostream& os, const Entry& entry);

  /// @return Referência constante para a referência temporal.
  [[nodiscard]] const int& getTimeRef() const;

  /// @return Referência constante para o valor monetário.
  [[nodiscard]] const double& getValue() const;

  /// @return Referência constante para o indicador de status.
  [[nodiscard]] const char& getStatus() const;

  /// @return Referência constante para a conta associada.
  [[nodiscard]] const std::string& getAccount() const;

  /// @return Referência constante para o código do produto/transação.
  [[nodiscard]] const std::string& getCode() const;

  /// @return Referência constante para o código do país.
  [[nodiscard]] const std::string& getCountryCode() const;

  /// @return Referência constante para o tipo do produto.
  [[nodiscard]] const std::string& getProductType() const;
};

#endif  // SEQUENCE_SET_ENTRY_ENTRY_H
