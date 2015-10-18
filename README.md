# B-Tree
Implementação em C de uma B-Tree de propósito geral.

UFSCar - São Carlos - 2015

## Autores
- Antonio Carlos Falcão Petri
- Thiago Yonamine

Alunos do 2º ano de Ciência da Computação na UFSCar - São Carlos.

## Motivação
Esse projeto é um trabalho da disciplina Organização e Recuperação da Informação ministrada pelo
Prof. Dr. Ricardo Cerri no 2º semestre de 2015.

## Documentação

### Vantagens da implementação
- Um mesmo programa pode possuir várias B-Tree de ordens diferentes;
- A B-Tree pode armazenar qualquer tipo de dado, desde que ele seja indexado por um valor inteiro.

### Structs
  - `pair_t`
  - `node_t`
  - `node_position_t`
  - `btree_t -> BTree`
  
### Métodos públicos
  - `BTree* btree_new(int order);`
  - `void btree_delete(BTree *bt);`
  
  - `node_position btree_insert(BTree* bt, int key);`
  - `node_position btree_find(BTree* bt, int key);`
  - `node_position btree_remove(BTree* bt, int key);`
  
