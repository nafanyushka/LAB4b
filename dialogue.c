//
// Created by Nafany on 12.05.2021.
//

#include "dialogue.h"

Tree* load(){
    Tree* root = NULL;
    int key, len;
    FILE* fd = fopen("test", "rb");
    while(!feof(fd)){
        fread(&key, 1, sizeof(int), fd);
        fread(&len, 1, sizeof(int), fd);
        char* info = (char*)malloc(sizeof(char) * len);
        fread(info, 1, len, fd);
        if(root == NULL){
            root = createTree(key, info);
        }
        else{
            add(&root, root, createTree(key, info));
        }
    }
    fclose(fd);
    return root;
}

void dialogue() {
    int key, choose;
    char* voidKey;
    char *info;

//    printf("Введите ключ корня: ");
//    key = getInt();
//    do {
//        printf("Введите информация корня: ");
//        info = get_String();
//    }while(strlen(info) < 1);
//    Tree* root = createTree(key, info);

    Tree* root = load();

    do{
        printf("Введите 1, чтобы добавить элемент в дерево Нафани.\n"
               "Введите 2, чтобы найти элемент в дереве Нафани.\n"
               "Введите 3, чтобы найти самый удаленный элемент в дереве Нафани.\n"
               "Введите 4, чтобы напечатать все большие ключи от заданного.\n"
               "Введите 0, чтобы вывести дерево Нафани.\n");
        choose = getInt();
        switch (choose) {
            case 1:
                printf("Введите ключ: ");
                key = getInt();
                do{
                    printf("Введите информацию: ");
                    info = get_String();
                }while(strlen(info) < 1);
                if(add(&root, root, createTree(key, info)) == 0){
                    printf("Такой ключ уже лежит в дереве.\n");
                }
                break;
            case 2:
                printf("Введите ключ для поиска: ");
                key = getInt();
                info = find(root, key);
                if(info == NULL){
                    printf("Не удалось найти объект с таким ключом.\n");
                }
                else
                    printf("Найденный объект содержит следующую информацию: %s\n", info);
                break;
            case 3:
                printf("Введите ключ для поиска: ");
                key = getInt();
                info = findFarest(root, key);
                printf("Информация найденного объекта: %s\n", info);
                break;
            case 4:
                printf("Введите ключ, чтобы вывести все что его превышает: ");
                voidKey = get_String();
                int* num = (int*)calloc(sizeof(int), 1);
                if(*voidKey == '\0')
                    num = NULL;
                else{
                    while(*voidKey != '\0'){
                        if(*voidKey < 48 || *voidKey > 57) {
                            free(voidKey);
                            free(num);
                            printf("Похоже, вы ввели буквы.\n");
                            break;
                        }
                        *num = (*num) * 10 + (*voidKey) - 48;
                        voidKey++;
                    }
                }
                printHigher(root, num);
                free(voidKey);
                free(num);
                break;
            case 0:
                printf("\n");
                printTree(root, 0);
                printf("\n");
                break;
            default:
                break;
        }


    }while(choose != 100);
    freeTree(root);
}