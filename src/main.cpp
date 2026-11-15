//
// Created by arthur on 23/01/25.
//

#include <exception>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>

#include <sequence-set/entry/entry.h>
#include <sequence-set/sequence_set.h>

/// @file
/// @brief Menu interativo e rotinas de leitura/escrita de CSV e binário.

/// @brief Código da aplicação.
namespace Project {

namespace {

/// Cabeçalho esperado nos arquivos CSV.
constexpr auto kCsvHeader =
    R"(time_ref,"account","code","country_code","product_type",value,"status")";

/// Escreve um valor primitivo em @p file em formato binário.
/// @tparam U Tipo do valor.
/// @param file Arquivo de saída aberto em modo binário.
/// @param value Valor a ser escrito.
template <class U>
void writeValue(std::ofstream& file, const U& value) {
  file.write(reinterpret_cast<const char*>(&value), static_cast<std::streamsize>(sizeof(U)));
}

/// Lê um valor primitivo de @p file em formato binário.
/// @tparam U Tipo do valor.
/// @param file Arquivo de entrada aberto em modo binário.
/// @param value Destino do valor lido.
/// @throw std::runtime_error Se a leitura falhar.
template <class U>
void readValue(std::ifstream& file, U& value) {
  file.read(reinterpret_cast<char*>(&value), static_cast<std::streamsize>(sizeof(U)));
  if (!file) {
    throw std::runtime_error("não foi possível ler o arquivo binário");
  }
}

/// Escreve uma string precedida pelo seu tamanho.
/// @param file Arquivo de saída aberto em modo binário.
/// @param value String a ser escrita.
void writeString(std::ofstream& file, const std::string& value) {
  const std::size_t length = value.size();
  writeValue(file, length);
  file.write(value.data(), static_cast<std::streamsize>(length));
}

/// Lê uma string precedida pelo seu tamanho.
/// @param file Arquivo de entrada aberto em modo binário.
/// @return String lida do arquivo.
/// @throw std::runtime_error Se a leitura do conteúdo falhar.
std::string readString(std::ifstream& file) {
  std::size_t length = 0;
  readValue(file, length);

  std::string value(length, '\0');
  if (length > 0) {
    file.read(value.data(), static_cast<std::streamsize>(length));
    if (!file) {
      throw std::runtime_error("não foi possível ler o arquivo binário");
    }
  }
  return value;
}

}  // namespace

/// Lê um arquivo CSV e retorna os dados como um SequenceSet<Entry>.
///
/// Linhas vazias e o cabeçalho são ignorados. Cada linha restante é convertida
/// em um Entry e inserida com um identificador sequencial crescente.
///
/// @param filename Caminho do arquivo CSV.
/// @param chunkSize Capacidade de cada chunk.
/// @return Conjunto com os registros lidos.
/// @throw std::runtime_error Se o arquivo não existir ou não puder ser aberto.
SequenceSet<Entry> readCSV(const std::string& filename, std::size_t chunkSize) {
  if (!std::filesystem::exists(filename)) {
    throw std::runtime_error("o arquivo não existe");
  }

  std::ifstream file(filename);
  if (!file.is_open()) {
    throw std::runtime_error("não foi possível abrir o arquivo");
  }

  SequenceSet<Entry> entries(chunkSize);

  std::string line;
  std::size_t id = 1;
  while (std::getline(file, line)) {
    if (line.empty() || line == kCsvHeader) {
      continue;
    }

    entries.insert(id, Entry::fromCSV(line));
    ++id;
  }

  return entries;
}

/// Salva os dados de um SequenceSet<Entry> em um arquivo CSV.
///
/// O cabeçalho é escrito antes dos registros; cada Entry é serializado pelo
/// seu método toCSV.
///
/// @param entries Conjunto de registros a salvar.
/// @param filename Caminho do arquivo CSV de destino.
/// @throw std::runtime_error Se o arquivo não puder ser aberto ou escrito.
void saveCSV(const SequenceSet<Entry>& entries, const std::string& filename) {
  std::ofstream file(filename);
  if (!file.is_open()) {
    throw std::runtime_error("não foi possível abrir o arquivo");
  }

  file << kCsvHeader << '\n';
  for (const auto& chunk : entries) {
    for (const auto& [key, entry] : chunk) {
      file << entry.toCSV() << '\n';
    }
  }

  if (!file) {
    throw std::runtime_error("não foi possível escrever o arquivo CSV");
  }
}

/// Lê os dados serializados por saveBinary.
///
/// O arquivo começa com a capacidade dos chunks e a quantidade de chunks; em
/// seguida, cada chunk informa seu tamanho e seus elementos. Os campos de
/// texto são lidos como tamanho seguido de conteúdo.
///
/// @param filename Caminho do arquivo binário.
/// @return Conjunto com os registros lidos do arquivo.
/// @throw std::runtime_error Se o arquivo não existir, não puder ser aberto ou
/// estiver corrompido.
SequenceSet<Entry> readBinary(const std::string& filename) {
  if (!std::filesystem::exists(filename)) {
    throw std::runtime_error("o arquivo não existe");
  }

  std::ifstream file(filename, std::ios::binary);
  if (!file.is_open()) {
    throw std::runtime_error("não foi possível abrir o arquivo");
  }

  std::size_t chunkCapacity = 0;
  std::size_t chunkCount = 0;
  readValue(file, chunkCapacity);
  readValue(file, chunkCount);

  SequenceSet<Entry> entries(chunkCapacity);

  for (std::size_t chunkIndex = 0; chunkIndex < chunkCount; ++chunkIndex) {
    std::size_t chunkSize = 0;
    readValue(file, chunkSize);

    for (std::size_t i = 0; i < chunkSize; ++i) {
      std::size_t key = 0;
      int timeRef = 0;
      double value = 0.0;
      char status = '\0';

      readValue(file, key);
      readValue(file, timeRef);
      readValue(file, value);
      readValue(file, status);

      std::string account = readString(file);
      std::string code = readString(file);
      std::string countryCode = readString(file);
      std::string productType = readString(file);

      entries.insert(key, Entry(timeRef, std::move(account), std::move(code),
                                std::move(countryCode), std::move(productType), value, status));
    }
  }

  return entries;
}

/// Salva os dados de um SequenceSet<Entry> em um arquivo binário.
///
/// A capacidade dos chunks e a quantidade de chunks são escritas primeiro.
/// Para cada chunk, grava-se a quantidade de elementos e, para cada Entry, os
/// campos primitivos seguidos das strings no formato tamanho + conteúdo.
///
/// @param entries Conjunto de registros a salvar.
/// @param filename Caminho do arquivo binário de destino.
/// @throw std::runtime_error Se o arquivo não puder ser aberto ou escrito.
void saveBinary(const SequenceSet<Entry>& entries, const std::string& filename) {
  std::ofstream file(filename, std::ios::binary);
  if (!file.is_open()) {
    throw std::runtime_error("não foi possível abrir o arquivo");
  }

  writeValue(file, entries.getChunkSize());
  writeValue(file, entries.getChunkCount());

  for (const auto& chunk : entries) {
    const std::size_t chunkSize = chunk.getSize();
    writeValue(file, chunkSize);

    for (const auto& [key, entry] : chunk) {
      writeValue(file, key);
      writeValue(file, entry.getTimeRef());
      writeValue(file, entry.getValue());
      writeValue(file, entry.getStatus());

      writeString(file, entry.getAccount());
      writeString(file, entry.getCode());
      writeString(file, entry.getCountryCode());
      writeString(file, entry.getProductType());
    }
  }

  if (!file) {
    throw std::runtime_error("não foi possível escrever o arquivo binário");
  }
}

}  // namespace Project

/// Executa o menu interativo da aplicação.
///
/// Os comandos aceitos são `read`, `b-read`, `save`, `b-save`, `search`,
/// `remove`, `print` e `exit`. Cada comando pode falhar com uma exceção, que é
/// capturada para que o menu continue em execução.
///
/// @return 0 após o encerramento normal do menu.
int main() {
  SequenceSet<Entry> entries(5);

  std::string option;
  while (true) {
    std::cout << "Choose an option:\n";
    std::cout << "1. read - Load content from a CSV file\n";
    std::cout << "2. b-read - Load content from a binary file\n";
    std::cout << "3. save - Save content in CSV file\n";
    std::cout << "4. b-save - Save content in binary file\n";
    std::cout << "5. search - Search for an element by ID\n";
    std::cout << "6. remove - Remove an element by ID\n";
    std::cout << "7. print - print each elements\n";
    std::cout << "8. exit - Exit the program\n";
    std::cout << "Enter your command: ";

    if (!(std::cin >> option)) {
      break;
    }

    if (option == "exit") {
      break;
    }

    if (option == "read") {
      std::string filepath;
      std::cout << "Enter the CSV file absolute path: ";
      std::cin >> filepath;
      std::cout << "Loading content from CSV file: " << filepath << '\n';
      try {
        entries = Project::readCSV(filepath, 5);
        std::cout << "\n --- Content loaded successfully --- \n\n";
      } catch (const std::exception& error) {
        std::cout << "\n --- Content NOT loaded --- \n\n";
        std::cerr << error.what() << '\n';
      }
    } else if (option == "b-read") {
      std::string filepath;
      std::cout << "Enter the binary file absolute path: ";
      std::cin >> filepath;
      std::cout << "Loading content from binary file: " << filepath << '\n';
      try {
        entries = Project::readBinary(filepath);
        std::cout << "\n --- Content loaded successfully --- \n\n";
      } catch (const std::exception& error) {
        std::cout << "\n --- Content NOT loaded --- \n\n";
        std::cerr << error.what() << '\n';
      }
    } else if (option == "save") {
      std::string filepath;
      std::cout << "Enter the CSV file absolute path: ";
      std::cin >> filepath;
      std::cout << "Saving content in CSV file: " << filepath << '\n';
      try {
        Project::saveCSV(entries, filepath);
        std::cout << "\n --- Content saved successfully --- \n\n";
      } catch (const std::exception& error) {
        std::cout << "\n --- Content NOT saved --- \n\n";
        std::cerr << error.what() << '\n';
      }
    } else if (option == "b-save") {
      std::string filepath;
      std::cout << "Enter the binary file absolute path: ";
      std::cin >> filepath;
      std::cout << "Saving content in binary file: " << filepath << '\n';
      try {
        Project::saveBinary(entries, filepath);
        std::cout << "\n --- Content saved successfully --- \n\n";
      } catch (const std::exception& error) {
        std::cout << "\n --- Content NOT saved --- \n\n";
        std::cerr << error.what() << '\n';
      }
    } else if (option == "search") {
      std::size_t id = 0;
      std::cout << "Enter the ID to search: ";
      std::cin >> id;
      std::cout << "Searching for element with ID: " << id << '\n';
      try {
        const auto element = entries.find(id);
        std::cout << "\n --- Element found --- \n" << element << '\n';
      } catch (const std::exception& error) {
        std::cout << "\n --- Element NOT found --- \n\n";
        std::cerr << error.what() << '\n';
      }
    } else if (option == "remove") {
      std::size_t id = 0;
      std::cout << "Enter the ID to remove: ";
      std::cin >> id;
      std::cout << "Trying to remove element with ID: " << id << '\n';
      try {
        entries.remove(id);
        std::cout << "\n --- Element removed successfully --- \n\n";
      } catch (const std::exception& error) {
        std::cout << "\n --- Element NOT found --- \n\n";
        std::cerr << error.what() << '\n';
      }
    } else if (option == "print") {
      if (entries.getSize() == 0) {
        std::cout << "\n --- Sequence set is empty --- \n\n";
      } else {
        for (const auto& chunk : entries) {
          for (const auto& [key, entry] : chunk) {
            std::cout << "Key: " << key << '\n';
            std::cout << entry << '\n';
          }
        }
      }
    } else {
      std::cout << "Invalid option. Please try again.\n";
    }
  }

  return 0;
}
