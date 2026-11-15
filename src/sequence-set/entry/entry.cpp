//
// Created by arthur on 23/01/25.
//

#include <sequence-set/entry/entry.h>

Entry::Entry(int time_ref, std::string account, std::string code, std::string country_code,
             std::string product_type, double value, char status)
    : time_ref_(time_ref),
      value_(value),
      status_(status),
      account_(std::move(account)),
      code_(std::move(code)),
      country_code_(std::move(country_code)),
      product_type_(std::move(product_type)) {}

bool Entry::operator==(const Entry& other) const {
  return time_ref_ == other.time_ref_ && account_ == other.account_ && code_ == other.code_ &&
         country_code_ == other.country_code_ && product_type_ == other.product_type_ &&
         value_ == other.value_ && status_ == other.status_;
}

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

std::string Entry::toCSV() const {
  return std::format(R"({},"{}","{}","{}","{}",{},"{}")", time_ref_, account_, code_, country_code_,
                     product_type_, value_, status_);
}

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

const int& Entry::getTimeRef() const {
  return time_ref_;
}

const double& Entry::getValue() const {
  return value_;
}

const char& Entry::getStatus() const {
  return status_;
}

const std::string& Entry::getAccount() const {
  return account_;
}

const std::string& Entry::getCode() const {
  return code_;
}

const std::string& Entry::getCountryCode() const {
  return country_code_;
}

const std::string& Entry::getProductType() const {
  return product_type_;
}
