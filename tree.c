//
// Created by Nafany on 12.05.2021.
//

#include "tree.h"

int checkKey(Tree* tree, int key){
    while(tree != NULL){
        if(key == tree->key){
            return 1;
        }
        if(key < tree->key){
            tree = tree->left;
        }
        if(key > tree->key){
            tree = tree->right;
        }
    }
    return 0;
}

int reBalanceLeftLess(Tree* tree, Tree** parent);
int reBalanceRightLess(Tree* tree, Tree** parent);

void correctLeftLess(Tree* tree, Tree** parent){
    if(tree == NULL){
        return;
    }
    correctLeftLess(tree->right, &tree);
    if(tree->balance < -1) {
        reBalanceLeftLess(tree, parent);
    }
}

void correctRightLess(Tree* tree, Tree** parent){
    if(tree == NULL){
        return;
    }
    correctRightLess(tree->right, &tree);
    if(tree->balance > 1) {
        reBalanceRightLess(tree, parent);
    }
}

int reBalanceLeftLess(Tree* tree, Tree** parent){ //ТО ЕСТЬ СЛЕВА БОЛЬШЕ ЭЛЕМЕНТОВ НА ДВА
    Tree* fixer = tree->left;
    Tree* prevFixer = tree;
    Tree* firstLeft = fixer;
    while(fixer->right != NULL){
        fixer->balance -= 1;
        prevFixer = fixer;
        fixer = fixer->right;
    }
    if(fixer == tree->left){ //НЕ СДВИНУЛСЯ, ТО ЕСТЬ ФИКСЕР СЛЕВА ОТ ПЕРЕМЕЩАЕМОГО ЭЛЕМЕНТА
        fixer->balance = tree->balance + 1;
        fixer->right = tree->right;
        if(fixer->key < (*parent)->key){
            (*parent)->left = fixer;
        }
        else{
            (*parent)->right = fixer;
        }
        tree->balance = 0;
        add(parent, fixer, tree);
        return 1;
    }
    prevFixer->right = fixer->left;
    fixer->balance = tree->balance + 1;
    if(fixer->key < (*parent)->key){
        (*parent)->left = fixer;
    }
    else{
        (*parent)->right = fixer;
    }
    fixer->left = tree->left;
    fixer->right = tree->right;
    tree->balance = 0;
    add(parent, fixer, tree);
    correctLeftLess(firstLeft, &fixer);
    return 1;
}

int reBalanceRightLess(Tree* tree, Tree** parent){ //ТО ЕСТЬ СПРАВА БОЛЬШЕ ЭЛЕМЕНТОВ НА ДВА
    Tree* fixer = tree->right;
    Tree* prevFixer = tree;
    Tree* firstLeft = fixer;
    while(fixer->left != NULL){
        fixer->balance += 1;
        prevFixer = fixer;
        fixer = fixer->left;
    }
    if(fixer == tree->right){ //НЕ СДВИНУЛСЯ, ТО ЕСТЬ ФИКСЕР СПРАВА ОТ ПЕРЕМЕЩАЕМОГО ЭЛЕМЕНТА
        fixer->balance = tree->balance - 1;
        fixer->left = tree->left;
        if(fixer->key < (*parent)->key){
            (*parent)->left = fixer;
        }
        else{
            (*parent)->right = fixer;
        }
        tree->balance = 0;
        add(parent, fixer, tree);
        return 1;
    }
    prevFixer->left = fixer->right;
    fixer->balance = tree->balance - 1;
    if(fixer->key < (*parent)->key){
        (*parent)->left = fixer;
    }
    else{
        (*parent)->right = fixer;
    }
    fixer->left = tree->left;
    fixer->right = tree->right;
    tree->balance = 0;
    add(parent, fixer, tree);
    correctRightLess(firstLeft, &fixer);
    return 1;
}

void freeBranch(Tree* branch){
    free(branch->info);
    free(branch);
}

Tree* createTree(int key, char* info){
    Tree* tree = (Tree*)malloc(sizeof(Tree));
    tree->key = key;
    tree->info = info;
    tree->balance = 0;
    tree->right = NULL;
    tree->left = NULL;
    return tree;
}
int add(Tree** root, Tree* tree, Tree* plug){
    if(plug->key == tree->key){
        freeBranch(plug);
        return 0;
    }
    if(plug->key < tree->key){
        if(tree->left == NULL){
            tree->left = plug;
            tree->balance--;
            return 1;
        }
        int k = add(root, tree->left, plug);
        if(k == 1){
            tree->balance--;
            return 1;
        }
    }
}
int delete(Tree* tree, int key){

}
char* find(Tree* tree, int key){

}
void freeTree(Tree* tree){

}