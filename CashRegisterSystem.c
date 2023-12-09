//ミニストップのレジシステムを再現する
#include <stdio.h>:
#include <stdlib.h>:
int calurate(){
    int total = 0;
    int price;
    int num;
    int i;
        printf("商品の個数を入力してください\n");
        scanf("%d", &num);
        total += price * num;
    
    return total;
}
#include <stdio.h>

// 商品情報の構造体
typedef struct {
    int country;
    char name[100];
    int category;
    int price;
} Item;

int main() {
    // 構造体の変数を宣言
    Item item;

    // 構造体のメンバに値を代入
    item.country = 1;
    strcpy(item.name, "りんご");
    item.category = 2;
    item.price = 100;

    // 構造体のメンバの値を表示
    printf("国コード: %d\n", item.country);
    printf("商品名: %s\n", item.name);
    printf("カテゴリ: %d\n", item.category);
    printf("価格: %d\n", item.price);

    return 0;
}
