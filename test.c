//
// Created by Nafany on 13.05.2021.
//

#include "dialogue.h"

int main(){
    FILE* fd = fopen("test", "wb");
    int key;
    char* info;
    do{
        key = getInt();
        do{
            info = get_String();
        }while(strlen(info) < 1);
        fwrite(&key, 1, sizeof(int), fd);
        int len = (int)strlen(info) + 1;
        fwrite(&len, 1, sizeof(int), fd);
        fwrite(info, 1, len, fd);
    }while(key != 100);
    fclose(fd);
}