#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

    char filename[100];
    printf("ファイル名を入力してください: ");
    scanf("%s", filename);
    //ユーザーがモードを選択
    int mode;
    printf("1...読み込み, 2...書き込み, 3...追加書き込み\n");
    printf("モードを入力してください: ");
    scanf("%d", &mode);
    // ファイルを開く
    FILE *fp;

    if (mode == 1) {
        fp = fopen(strcat(filename, ".txt"), "r");
        if(fp == NULL){
            printf("ファイルが存在しません。\n");
            exit(1);
        }
    } else if (mode == 2) {
        fp = fopen(strcat(filename, ".txt"), "w");
    }else if(mode == 3){
        fp = fopen(strcat(filename, ".txt"), "a");
        if(fp == NULL){
            printf("ファイルが存在しません。\n");
            exit(1);
        }
    }else{
        printf("モードが不正です。\n");
    }
    // ここにコードを追加

    fclose(fp);

    return 0;
}

int menu(){
    int mode;
    printf("モードを選択したください\n");
    printf("1:読み込み\n");
    
}
