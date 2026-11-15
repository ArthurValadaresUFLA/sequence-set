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

/// @brief Registro de uma transação/entrada do arquivo CSV.
///
/// A classe agrupa os campos lidos do arquivo, fornece conversão para CSV e
/// mantém a semântica de valor (cópia profunda das strings).
class Entry {
 private:
  int time_ref_{};
  double value_{};
  char status_{};

  std::string account_;
  std::string code_;
  std::string country_code_;
  std::string product_type_;

 public:
  Entry() = default;

  Entry(int time_ref, std::string account, std::string code, std::string country_code,
        std::string product_type, double value, char status);

  Entry(const Entry&) = default;
  Entry(Entry&&) noexcept = default;
  ~Entry() = default;
  Entry& operator=(const Entry&) = default;
  Entry& operator=(Entry&&) noexcept = default;

  [[nodiscard]] bool operator==(const Entry& other) const;

  /// Cria um Entry a partir de uma linha CSV.
  /// @throw std::runtime_error Se o formato da linha for inválido.
  static Entry fromCSV(const std::string& csvLine);

  /// Converte o Entry para uma linha CSV.
  [[nodiscard]] std::string toCSV() const;

  friend std::ostream& operator<<(std::ostream& os, const Entry& entry);

  [[nodiscard]] const int& getTimeRef() const;
  [[nodiscard]] const double& getValue() const;
  [[nodiscard]] const char& getStatus() const;
  [[nodiscard]] const std::string& getAccount() const;
  [[nodiscard]] const std::string& getCode() const;
  [[nodiscard]] const std::string& getCountryCode() const;
  [[nodiscard]] const std::string& getProductType() const;
};

#endif  // SEQUENCE_SET_ENTRY_ENTRY_H
