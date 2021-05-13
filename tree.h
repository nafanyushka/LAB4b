//
// Created by Nafany on 12.05.2021.
//

#ifndef LAB4B_TREE_H
#define LAB4B_TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Tree Tree;

struct Tree{
    int key;
    int balance;
    char* info;
    Tree* left;
    Tree* right;
};

Tree* createTree(int key, char* info);
int add(Tree** root, Tree* tree, Tree* plug);
int delete(Tree* tree, int key);
char* find(Tree* tree, int key);
void freeTree(Tree* tree);

#endif //LAB4B_TREE_H
