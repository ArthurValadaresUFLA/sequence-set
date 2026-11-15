# Versão mínima alinhada à estrutura de referência do projeto data-structure.
cmake_minimum_required(VERSION 3.28)

# Bloqueia builds dentro da árvore de fontes: eles espalhariam CMakeCache.txt,
# Makefile, Doxyfile e outros artefatos pela raiz do projeto.
if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
  message(
    FATAL_ERROR
      "Build dentro da árvore de fontes não é permitido. Informe um diretório "
      "separado: cmake -S . -B build (ou use cmake --preset default).")
endif()

project(
  sequence-set
  VERSION 0.1.0
  DESCRIPTION
    "Conjunto de sequências implementado com chunks e lista duplamente encadeada (GAC108 - DCC/UFLA)"
  HOMEPAGE_URL "https://github.com/ArthurValadaresUFLA/sequence-set"
  LANGUAGES CXX)

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ---------------------------------------------------------------------------
# Executável
# ---------------------------------------------------------------------------

file(GLOB_RECURSE SEQUENCE_SET_HEADERS CONFIGURE_DEPENDS ${INCLUDE_DIR}/*.h)
file(GLOB_RECURSE SEQUENCE_SET_TEMPLATE_SOURCES CONFIGURE_DEPENDS
     ${SOURCE_DIR}/*.tpp)

set(SEQUENCE_SET_SOURCES ${SOURCE_DIR}/main.cpp
                         ${SOURCE_DIR}/sequence-set/entry/entry.cpp)

add_executable(${PROJECT_NAME} ${SEQUENCE_SET_SOURCES} ${SEQUENCE_SET_HEADERS})

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

# include/ e src/ são raízes de inclusão: os cabeçalhos usam caminhos absolutos
# de projeto, como <sequence-set/common/chunk/chunk.h>, e as definições de
# template vivem em src/sequence-set/... .
target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIR} ${SOURCE_DIR})

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
  target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
endif()

# Alvo auxiliar para que a IDE liste e indexe também os arquivos .tpp.
add_custom_target(
  ${PROJECT_NAME}_sources
  SOURCES ${SEQUENCE_SET_HEADERS} ${SEQUENCE_SET_TEMPLATE_SOURCES}
  COMMENT "Auxílio à indexação por IDE's")

# ---------------------------------------------------------------------------
# Instalação
# ---------------------------------------------------------------------------

include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

# ---------------------------------------------------------------------------
# Documentação
# ---------------------------------------------------------------------------

option(SEQUENCE_SET_BUILD_DOCS "Gera a documentação Doxygen"
       ${PROJECT_IS_TOP_LEVEL})

if(SEQUENCE_SET_BUILD_DOCS)
  find_package(Doxygen)

  if(NOT DOXYGEN_FOUND)
    message(
      WARNING "${PROJECT_NAME}: Doxygen não encontrado, docs desabilitada")
  else()
    include(FetchContent)

    FetchContent_Declare(
      doxygen-awesome-css
      URL https://github.com/jothepro/doxygen-awesome-css/archive/refs/tags/v2.3.4.zip
    )
    FetchContent_MakeAvailable(doxygen-awesome-css)
    FetchContent_GetProperties(doxygen-awesome-css SOURCE_DIR AWESOME_CSS_DIR)

    set(DOXYFILE_IN ${CMAKE_CURRENT_SOURCE_DIR}/doc/Doxyfile.in)
    set(DOXYFILE_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)
    configure_file(${DOXYFILE_IN} ${DOXYFILE_OUT} @ONLY)

    add_custom_target(
      docs
      COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYFILE_OUT}
      WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
      COMMENT "Gerando a documentação com Doxygen"
      VERBATIM)
  endif()
endif()
