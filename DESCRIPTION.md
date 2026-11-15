# Descrição em Alto Nível do Programa

Ao longo do delineamento do projeto, as funcionalidades implementadas se dividiram em 7 partes
passíveis de seleção por meio de um menu interativo:

- Leitura de arquivo CSV;
- Escrita de arquivo CSV;
- Leitura de arquivo binário;
- Escrita de arquivo binário;
- Busca com base no identificador;
- Remoção com base no identificador;
- Escrever todos os dados;

Há partes que lançam as bases para a abstração geral do projeto, de modo permitir uma maior
abstração. Essas partes são:

- Node;
- DoublyLinkedList;
- Chunk;
- SequenceSet;

Cada objeto definido no projeto segue, a medida do possível, a regra dos 5 no C++. A regra determina
que o construtor, o destrutor, o construtor de cópia, o operador de atribuição e o operador de
igualdade devem ser implementados.

## Recursos

### Node

A classe node, suas derivadas e suas interfaces abstraem a ideia de um nó, os atributos e métodos
que todo nó deve implementar. Cabe a um nó ter um objeto interno, passível de obtenção por meio de
um método de acesso - método *get* -, um nó simplesmente encadeado fica responsável por referenciar
somente o nó subsequente da corrente, ao passo que o nó duplamente encadeado fica responsável por
referenciar tanto o nó subsequente quanto o precedente. Para ambos os tipos de nós, há os métodos de
acesso e definição dos respectivos atributos. A fim de permitir uma maior generalização, faz-se o
uso de *templates*, um recurso de meta-programação do C++ que permite delegar ao compilador o
processo de definição de uma classe com base no uso dentro do código a partir de um modelo que deve
ser seguido.

## DoublyLinkedList

Essa classe é responsável por fazer a abstração de uma lista duplamente encadeada, com os métodos
comuns e fazendo o uso de um nó duplamente encadeado. Também faz o uso de *templates*, de modo que o
código, se necessário, possa ser reutilizado em outros situações.

## Chunk

É a classe responsável por permitir uma manipulação de nível mais complexo do que pode ser entendido
como *blocos* constituintes da estrutura de dados sequence set. Cada Chunk possui um vetor alocado
dinamicamente - com base na capacidade informada no construtor.

## SequenceSet

A estrutura de dados principal, herda de DoublyLinkedList de modo que os métodos da superclasse
sejam protegidos, a fim de evitar que os métodos sejam usados de forma inapropriada e,
eventualmente, comprometa o estado interno do objeto. A responsabilidade de referenciar o bloco
subsequente e precedente é do SequenceSet, ou, em uma visão mais estrita, da lista duplamente
encadeada.

## Funcionalidades

### Leitura do CSV

Quando selecionado, é requisitado o caminho absoluto do arquivo CSV, depois de fornecido, o programa
verifica a existência do arquivo, abre, ignora o cabeçalho se ele estiver presente e itera sobre as
linhas, de modo a usar uma expressão regular - incluso na std no módulo `regex` - para extrair o
valor de cada campo. Durante a iteração sobre as linhas do arquivo os objetos construídos a partir
de cada linha são inseridos no sequence set. Durante o processo de inserção, se o bloco no qual o
elemento deve ser inserido estiver cheio, ele é dividido em dois, mantendo a ordem e o tamanho
mínimo, que, para efeitos práticos foi definido como a metade. O novo novo valor é então inserido.

### Escrita do CSV

O caminho absoluto do arquivo é informado, ele é aberto, se houver um erro ele informa a o usuário,
caso não, ele adiciona o cabeçalho ao arquivo, itera sobre os elementos do sequence set acessando o
método toCSV de cada elemento e redireciona o valor para o arquivo. Quando termina de iterar sobre
os elementos ele fecha o arquivo.

### Escrita do binário

Escreve-se a quantidade dos *chunks* e o tamanho deles no início do arquivo, e, para cada chunk,
escrever a quantidade de elementos presentes, para cada elemento do *chunk* ele - um Entry - ele
serializa o tipos primitivos do C++ e, para cada string, escreve o tamanho da string seguido do seu
conteúdo. A escrita é finalizada com o fechamento do arquivo e o usuário é informado que, na
perspectiva do programa, o processo foi encerrado com sucesso.

### Leitura do binário

A leitura do arquivo binário segue o processo oposto da escrita, é feito a leitura do número de
*chunks* e o tamanho deles, cria-se o sequence set com base no tamanho dos blocos e, para cada
bloco, deserializa os objetos fazendo a leitura dos tipos primitivos e dos campos de texto na ordem
em que foram escritos, respeitando a lógica de tamanho seguido de conteúdo para o caso dos campos de
texto.

### Busca

Por mais que o sequence set tenha os identificadores ordenados e não permita a duplicação, a busca é
feita de forma linear. O método responsável por isso jaz no sequence set, busca com base nos valores
do primeiro e último elemento do bloco, se estiver presente retorna o dado correspondente, caso não
levanta uma exceção.

### Remoção

Com base em um identificado fornecido, ele remove o par (chave, valor) correspondente, mantendo a
ordenação, movendo os elementos para as devidas posições e atualizando as informações
correspondentes do bloco - por exemplo, o tamanho.

### Escrever todos os dados no console

Esse método é responsável por permitir a averiguação das atividades do programa, para verificar a
consistência dos dados, a remoção, inserção e busca conforme o informado pelo usuário.
