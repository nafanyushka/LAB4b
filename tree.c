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
            continue;
        }
        if(key > tree->key){
            tree = tree->right;
            continue;
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

int reBalanceLeftLess(Tree* tree, Tree** parent){ //ТО ЕСТЬ СЛЕВА БОЛЬШЕ ЭЛЕМЕНТОВ
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
        if(*parent == tree){
            *parent = fixer;
        }
        else if(fixer->key < (*parent)->key){
            (*parent)->left = fixer;
        }
        else{
            (*parent)->right = fixer;
        }
        tree->balance = 0;
        tree->right = NULL;
        tree->left = NULL;
        add(parent, fixer, tree);
        return 1;
    }
    prevFixer->right = fixer->left;
    fixer->balance = tree->balance + 1;
    if(*parent == tree){
        *parent = fixer;
    }
    else if(fixer->key < (*parent)->key){
        (*parent)->left = fixer;
    }
    else{
        (*parent)->right = fixer;
    }
    fixer->left = tree->left;
    fixer->right = tree->right;
    tree->balance = 0;
    tree->right = NULL;
    tree->left = NULL;
    add(parent, fixer, tree);
    correctLeftLess(firstLeft, &fixer);
    return 1;
}

int reBalanceRightLess(Tree* tree, Tree** parent){ //ТО ЕСТЬ СПРАВА БОЛЬШЕ ЭЛЕМЕНТОВ
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
        if(*parent == tree){
            *parent = fixer;
        }
        else if(fixer->key < (*parent)->key){
            (*parent)->left = fixer;
        }
        else{
            (*parent)->right = fixer;
        }
        tree->balance = 0;
        tree->right = NULL;
        tree->left = NULL;
        add(parent, fixer, tree);
        return 1;
    }
    prevFixer->left = fixer->right;
    fixer->balance = tree->balance - 1;
    if(*parent == tree){
        *parent = fixer;
    }
    else if(fixer->key < (*parent)->key){
        (*parent)->left = fixer;
    }
    else{
        (*parent)->right = fixer;
    }
    fixer->left = tree->left;
    fixer->right = tree->right;
    tree->balance = 0;
    tree->right = NULL;
    tree->left = NULL;
    add(parent, fixer, tree);
    correctRightLess(firstLeft, &fixer);
    return 1;
}

int backendAdd(Tree** root, Tree* tree, Tree* plug){
    if(plug->key < tree->key){
        if(tree->left == NULL){
            tree->balance -= 1;
            tree->left = plug;
            if(abs(tree->balance) > DELTA){
                if(*root == tree)
                    reBalanceLeftLess(tree, root);
                else {
                    return -1;
                } //ВОЗВРАЩАЕТ -1 ЕСЛИ ПРОИЗОШЛА РАЗБАЛАНСИРОВКА
            }
            return 0;
        }
        else{
            tree->balance -= 1;
            int k = backendAdd(root, tree->left, plug);
            if(k == -1){
                reBalanceLeftLess(tree->left, &tree);
            }
            if(k == 1){
                reBalanceRightLess(tree->left, &tree);
            }
            if(abs(tree->balance) > DELTA) {
                if (*root == tree)
                    reBalanceLeftLess(tree, root);
                else
                    return -1;
            }
            return 0;
        }
    }
    else{
        if(tree->right == NULL){
            tree->balance += 1;
            tree->right = plug;
            if(tree->balance > DELTA){
                if(*root == tree)
                    reBalanceRightLess(tree, root);
                else
                    return 1;
            }
            return 0;
        }
        else{
            tree->balance += 1;
            int k = backendAdd(root, tree->right, plug);
            if(k == -1){
                reBalanceLeftLess(tree->right, &tree);
            }
            if(k == 1){
                reBalanceRightLess(tree->right, &tree);
            }
            if(tree->balance > DELTA){
                if(*root == tree)
                    reBalanceRightLess(tree, root);
                else
                    return 1;
            }
            return 0;
        }
    }
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

void printTree(Tree* root, int i){
    if(root == NULL) {
        return;
    }
    printTree(root->right, i + 1);
    for(int space = 0; space < i; space++){
        printf(" ");
    }
    printf("%d\n", root->key);
    printTree(root->left, i + 1);
}

int add(Tree** root, Tree* tree, Tree* plug){
    if(*root == NULL){
        *root = plug;
        return 1;
    }
    if(checkKey(tree, plug->key) == 1) {
        freeBranch(plug);
        return 0;
    }

    backendAdd(root, tree, plug);
    return 1;
}

int delete(Tree** root, Tree* tree, Tree* previous, int key){
    if(tree == NULL)
        return 0;
    else if(key < tree->key){
        int k = delete(root, tree->left, tree, key);
        if(k != 0){
            tree->balance++;
            if(abs(tree->balance) > DELTA){
                if(previous == NULL)
                    reBalanceRightLess(tree, root);
                else
                    reBalanceRightLess(tree, &previous);
            }
        }
        return k;
    }
    else if(key > tree->key){
        int k = delete(root, tree->right, tree, key);
        if(k != 0){
            tree->balance--;
            if(tree->balance > DELTA){
                if(previous == NULL)
                    reBalanceLeftLess(tree, root);
                else
                    reBalanceLeftLess(tree, &previous);
            }
        }
        return k;
    }
    else if(key == tree->key){ //ПОШЛИ УДАЛЯШКИ ДА БЛИН
        if(tree->left == NULL && tree->right == NULL){
            if(previous == NULL){
                *root = NULL;
                freeBranch(tree);
                return 1;
            }
            else{
                if(key < previous->key){
                    previous->left = NULL;
                    freeBranch(tree);
                    return 1;
                }
                else{
                    previous->right = NULL;
                    freeBranch(tree);
                    return 1;
                }
            }
        }
        else if(tree->left == NULL && tree->right != NULL){
            if(previous == NULL){
                *root = tree->right;
                freeBranch(tree);
                return 1;
            }
            else{
                if(key < previous->key){
                    previous->left = tree->right;
                    freeBranch(tree);
                    return 1;
                }
                else{
                    previous->right = tree->right;
                    freeBranch(tree);
                    return 1;
                }
            }
        }
        else if(tree->left != NULL && tree->right == NULL){
            if(previous == NULL){
                *root = tree->left;
                freeBranch(tree);
                return 1;
            }
            else{
                if(key < previous->key){
                    previous->left = tree->left;
                    freeBranch(tree);
                    return 1;
                }
                else{
                    previous->right = tree->left;
                    freeBranch(tree);
                    return 1;
                }
            }
        }
        else if(tree->left != NULL && tree->right != NULL){
            Tree* findReplace = tree->left;
            Tree* helper = NULL;
            Tree* firstLeft = tree->left;
            while(findReplace->right != NULL){
                findReplace->balance--;
                helper = findReplace;
                findReplace = findReplace->right;
            }
            if(helper != NULL){
                helper->right = findReplace->left;
                findReplace->left = tree->left;
                findReplace->right = tree->right;
                findReplace->balance = tree->balance + 1;
            }
            else{
                findReplace->right = tree->right;
                findReplace->balance = tree->balance + 1;
            }
            if(previous == NULL){
                *root = findReplace;
                if(findReplace->left == firstLeft)
                    correctLeftLess(findReplace->left, root);
                if(findReplace->balance > DELTA){
                    reBalanceRightLess(findReplace, root);
                }
                freeBranch(tree);
                return 1;
            }
            else{
                if(key < previous->key){
                    previous->left = findReplace;
                    if(findReplace->left == firstLeft)
                        correctLeftLess(findReplace->left, &findReplace);
                    if(findReplace->balance > DELTA){
                        reBalanceRightLess(findReplace, &previous);
                    }
                    freeBranch(tree);
                    return 1;
                }
                else{
                    previous->right = findReplace;
                    if(findReplace->left == firstLeft)
                        correctLeftLess(findReplace->left, &findReplace);
                    if(findReplace->balance > DELTA){
                        reBalanceRightLess(findReplace, &previous);
                    }
                    freeBranch(tree);
                    return 1;
                }
            }
        }
    }
}
char* find(Tree* tree, int key){
    Tree* finder = tree;
    while(finder != NULL){
        if(key == finder->key)
            return finder->info;
        if(key < finder->key){
            finder = finder->left;
            continue;
        }
        if(key > finder->key){
            finder = finder->right;
            continue;
        }
    }
    return NULL;
}

char* findFarest(Tree* root, int key){
    Tree* finder = root;
    while(finder->left != NULL){
        finder = finder->left;
    }
    Tree* min = finder;
    finder = root;
    while(finder->right != NULL){
        finder = finder->right;
    }
    Tree* max = finder;
    if(abs(max->key - key) > abs(min->key - key)){
        return max->info;
    }
    else{
        return min->info;
    }
}

void printHigher(Tree* tree, int* key){
    if(tree == NULL)
        return;
    if(key == NULL){
        printHigher(tree->right, key);
        printf("Ключ: %d, информация: %s\n", tree->key, tree->info);
        printHigher(tree->left, key);
    }
    else{
        if(*key >= tree->key){
            printHigher(tree->right, key);
        }
        else{
            printHigher(tree->right, key);
            printf("Ключ: %d, информация: %s.\n", tree->key, tree->info);
            printHigher(tree->left, key);
        }
    }


}

void freeTree(Tree* tree){
    if(tree == NULL){
        return;
    }
    freeTree(tree->left);
    freeTree(tree->right);
    freeBranch(tree);
}