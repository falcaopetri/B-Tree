# B-Tree
Implementação em C de uma B-Tree de propósito geral.

DC - UFSCar - São Carlos - 2015

## Autores
- Antonio Carlos Falcão Petri
- Thiago Yonamine

Graduandos em Ciência da Computação na UFSCar - São Carlos.

## Motivação
Esse projeto é um trabalho da disciplina Organização e Recuperação da Informação ministrada pelo Prof. Dr. Ricardo Cerri no 2º semestre de 2015 no Departamento de Computação, UFSCar - São Carlos.

## Uso
### Execução
Caso você possua a ferramenta GNU Make disponível, basta executar:
```shell
$ make
$ ./bin/btree
```

### Debug
Compile a aplicação e o `test/debug.c` com o **define**: `-DDEBUG=1`.

Com o makefile, basta descomentar o conteúdo da variável `CFLAGS` no cabeçalho:
`CFLAGS := -g -Wall -DDEBUG=1`; e executar:
```shell
$ make clean
$ make debug
$ ./bin/debug
```

## Documentação


### Detalhes de implementação
- Um mesmo programa pode possuir várias B-Tree de ordens diferentes;
- A B-Tree pode armazenar qualquer tipo de dado, desde que:
    - ele seja indexável por um valor inteiro;
    - ele seja gerenciado pela aplicação externa (a B-Tree não gerenciará o ciclo de vida dos dados).
- As funções `btree_insert()`, `btree_find()` e `btree_remove()` retornam um `node_position`, conforme determinado na especificação do trabalho. **Esteja ciente desse comportamento**. O endereço indicado pelo `node_position` pode **se tornar desatualizado** facilmente e, no caso da remoção, pode **apontar para um endereço que foi liberado e possui lixo de memória**.

Essa implementação foi fortemente baseada nas notas do livro **Introduction to Algorithms, Third Edition - Cormen, T.; Leiserdon, C. E.; Rivest, R. L.; Stein, C. n** e nas **notas de aula do Prof. Ricardo Cerri sobre Árvores B**.

Os Pseudo-códigos descritos aqui são modificações dos que se encontram no **Introduction to Algorithms**.

As implementações das operações **Inserção** e **Busca** foram, basicamente, transcrições entre os pseudo-códigos do livro para a linguagem C.

Já a operação **Remoção** não possuia pseudo-código correspondente, e foi implementada realizando uma análise dos casos especiais descritos no livro.

### Structs
  - `pair_t`
    - Associação entre `key` e `value`: `pair<int key, void *value>`
  - `node_t`
    - Nó da **B-Tree**. Pode possuir **[1, 2\*order)** `chaves` e **[1, 2\*order]** `nós-filhos`. Possui o `número de chaves ativas` e a flag `is_leaf`
  - `node_position_t` -> `typedef node_position`
    - Permite acessar diretamente um `node` e, em especial, o valor associado à uma `key`. Possui para tal o `ponteiro para um nó` e o `index` de uma determinada chave. É o resultado de várias operações na **B-Tree**
  - `btree_t` -> `typedef BTree`
    - **Struct principal**. Possui apenas o `nó raiz`, e a `ordem` da árvore

### API / Métodos "públicos"
- `BTree* btree_new(int order);`
    - Aloca e retorna uma nova B-Tree (Heap).
    - Deve ter uma chamada correspondente à `btree_delete_h(BTree *bt)`.


- `void btree_init(BTree *bt, int order);`
    - Inicializa uma B-Tree alocada na **Stack**.
    - Deve ter uma chamada correspondente à `btree_delete_s(BTree *bt)`.


- `void btree_delete_h(BTree *bt);`
    - Deleta uma B-Tree alocada na **Heap**. Deve ser chamada para não gerar memory leak.


- `void btree_delete_s(BTree *bt);`
    - Deleta uma B-Tree alocada na **Stack**. Deve ser chamada para não gerar memory leak.


- `node_position btree_insert(BTree *bt, int key, void *value);`
    - Insere a chave `key` em `bt`, associando-a ao valor `value`.
    - Retorna o node_position da inserção ou (NULL, -1).


- `node_position btree_find(BTree* bt, int key);`
    - Procura em `bt` a chave `key`.
    - Retorna o node_position da busca ou (NULL, -1).


- `node_position btree_remove(BTree* bt,
int key);`
    - Remove de `bt` a chave `key`.
    - Retorna o node_position da remoção ou (NULL, -1).


- `void btree_dfs(BTree *bt);`
    - Executa uma DFS sobre `bt` imprimindo o conteúdo dos seus nós em ordem **posfixa**.

### Criação
`BTree *tree = btree_new(2);`

Pseudo-código:
```
Allocate-Node(Order, IsLeaf):
    Node.order = Order
    Node.isLeaf = IsLeaf
    Node.nKeys = 0
    Node.children = Allocate-Children-Pointers(2*Order)
    Node.keys = Allocate-Keys-Pointers(2*Order-1)

    return Node
```

```
B-Tree-Create(T, Order):
    T.order = Order
    T.root = Allocate-Node(Order, True)
```
### Inserção
`node_position pos = btree_insert(tree, key, value);`

```
B-Tree-Insert(T, Key, Order)
    r = T.root
    if r.nKeys == 2*Order -1:
        s = Allocate-Node(Order, False)
        T.root = s
        s.c[0] = r
        B-Tree-Split-Child(s, 1, Order)
        B-Tree-Insert-Nonfull(s, Key, Order)
    else:
        B-Tree-Insert-Nonfull(r, Key, Order)
```
### Busca
`node_position pos = btree_find(tree, key);`

### Remoção
`node_position pos = btree_remove(tree, key);`

### Deleção
`btree_delete(tree);`

A deleção da B-Tree é executada aplicando-se a remoção sobre a primeira chave da raiz, enquanto existirem chaves.

Apesar de a operação poder ser mais eficiente aplicando-se, por exemplo, uma DFS de deleção, é garantido que a remoção eliminará todos os `pair's` e `node's` gerados na B-Tree.

Após o fim da remoção, deleta-se o nó raiz.
