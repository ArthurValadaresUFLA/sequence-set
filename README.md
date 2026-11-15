# sequence-set

**sequence-set** é um programa C++20 que implementa um conjunto de sequências sobre uma lista
duplamente encadeada de *chunks*. O programa oferece um menu interativo para leitura e escrita de
arquivos CSV e binários, busca e remoção por identificador e impressão dos dados armazenados.

## Pré-requisitos

- Compilador com suporte a C++20 (`g++` 13+ ou `clang++` 16+).
- CMake 3.28 ou superior.
- Um gerador de build, como Make ou Ninja.
- Doxygen (opcional, apenas para a documentação).
- `prek` e `cppcheck` (opcionais, apenas para os hooks de *pre-commit*).

## Compilação

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

O executável é gerado em `build/sequence-set`.

Para gerar a documentação Doxygen:

```bash
cmake -S . -B build -DSEQUENCE_SET_BUILD_DOCS=ON
cmake --build build --target docs
```

A documentação HTML é escrita em `doc/generated/html`.

## Execução

```bash
./build/sequence-set
```

Siga as instruções do menu interativo. O programa aceita caminhos absolutos para os arquivos CSV e
binários.

## Estrutura do projeto

```text
sequence-set/
├── CMakeLists.txt
├── doc/
│   └── Doxyfile.in
├── include/
│   └── sequence-set/
│       ├── common/
│       │   ├── chunk/
│       │   └── node/
│       ├── entry/
│       ├── interface/
│       ├── list/
│       └── sequence_set.h
├── src/
│   ├── main.cpp
│   └── sequence-set/
│       ├── common/
│       │   ├── chunk/chunk.tpp
│       │   └── node/doubly_linked_node.tpp
│       ├── entry/entry.cpp
│       ├── list/doubly_linked_list.tpp
│       └── sequence_set.tpp
└── README.md
```

Os cabeçalhos usam caminhos absolutos de projeto, como `<sequence-set/common/chunk/chunk.h>`. As
definições de template ficam em arquivos `.tpp` dentro de `src/` e são incluídas ao final do
cabeçalho correspondente.

## Principais funcionalidades

- Leitura e escrita de arquivos CSV.
- Leitura e escrita de arquivos binários.
- Busca e remoção de elementos por identificador.
- Impressão de todos os elementos no console.
- Divisão automática de chunks cheios, preservando a ordenação.

## Qualidade de código

O repositório inclui configuração de *pre-commit* com verificação de whitespace, formatação de C++ e
CMake, lint com `cppcheck`, formatação de Markdown e correção ortográfica com `cspell`.

Para instalar os hooks:

```bash
prek install
```

Para executar todas as verificações manualmente:

```bash
prek run --all-files
```
