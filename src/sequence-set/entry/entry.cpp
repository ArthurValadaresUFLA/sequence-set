//
// Created by arthur on 23/01/25.
//

#include <sequence-set/entry/entry.h>

/// @file
/// @brief Implementação do modelo de registro do CSV.

/// Cria um registro com os campos informados.
/// @param time_ref Referência temporal.
/// @param account Conta associada.
/// @param code Código do produto ou da transação.
/// @param country_code Código do país.
/// @param product_type Tipo do produto.
/// @param value Valor monetário.
/// @param status Indicador de status.
Entry::Entry(int time_ref, std::string account, std::string code, std::string country_code,
             std::string product_type, double value, char status)
    : time_ref_(time_ref),
      value_(value),
      status_(status),
      account_(std::move(account)),
      code_(std::move(code)),
      country_code_(std::move(country_code)),
      product_type_(std::move(product_type)) {}

/// Compara todos os campos de dois registros.
/// @param other Registro comparado.
/// @return `true` se todos os campos forem iguais.
bool Entry::operator==(const Entry& other) const {
  return time_ref_ == other.time_ref_ && account_ == other.account_ && code_ == other.code_ &&
         country_code_ == other.country_code_ && product_type_ == other.product_type_ &&
         value_ == other.value_ && status_ == other.status_;
}

/// Cria um Entry a partir de uma linha CSV.
/// @param csvLine Linha no formato do arquivo de origem.
/// @return Registro construído a partir dos campos extraídos.
/// @throw std::runtime_error Se o formato da linha for inválido.
Entry Entry::fromCSV(const std::string& csvLine) {
  static const std::regex csvLineFormat(
      R"lit(^(\d+),"(.*)","(.*)","(.*)","(.*)",(-?\d+\.?\d*)?,"(\w)"$)lit");

  std::smatch csvGroups;
  if (!std::regex_search(csvLine, csvGroups, csvLineFormat) || csvGroups.size() != 8) {
    throw std::runtime_error("formato de linha CSV inválido");
  }

  return {std::stoi(csvGroups[1].str()),
          csvGroups[2].str(),
          csvGroups[3].str(),
          csvGroups[4].str(),
          csvGroups[5].str(),
          std::stod(csvGroups[6].str()),
          csvGroups[7].str()[0]};
}

/// Converte o Entry para uma linha CSV.
/// @return Linha CSV com os campos entre aspas quando necessário.
std::string Entry::toCSV() const {
  return std::format(R"({},"{}","{}","{}","{}",{},"{}")", time_ref_, account_, code_, country_code_,
                     product_type_, value_, status_);
}

/// Escreve os campos do registro em @p os, um por linha.
/// @param os Fluxo de saída.
/// @param entry Registro a ser impresso.
/// @return Referência para o fluxo de saída.
std::ostream& operator<<(std::ostream& os, const Entry& entry) {
  os << "Time Ref: " << entry.time_ref_ << '\n'
     << "Account: " << entry.account_ << '\n'
     << "Code: " << entry.code_ << '\n'
     << "Country Code: " << entry.country_code_ << '\n'
     << "Product Type: " << entry.product_type_ << '\n'
     << "Value: " << entry.value_ << '\n'
     << "Status: " << entry.status_ << '\n';
  return os;
}

/// @return Referência constante para a referência temporal.
const int& Entry::getTimeRef() const {
  return time_ref_;
}

/// @return Referência constante para o valor monetário.
const double& Entry::getValue() const {
  return value_;
}

/// @return Referência constante para o indicador de status.
const char& Entry::getStatus() const {
  return status_;
}

/// @return Referência constante para a conta associada.
const std::string& Entry::getAccount() const {
  return account_;
}

/// @return Referência constante para o código do produto/transação.
const std::string& Entry::getCode() const {
  return code_;
}

/// @return Referência constante para o código do país.
const std::string& Entry::getCountryCode() const {
  return country_code_;
}

/// @return Referência constante para o tipo do produto.
const std::string& Entry::getProductType() const {
  return product_type_;
}
