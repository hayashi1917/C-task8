//コンビニのレジシステムを再現する
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Item {//商品情報
    char name[100];
    int category;
    int price;
    int purchased;
    struct Item *next; // 次のItemへのポインタ //連結リスト
} Item;

Item *head = NULL; // 連結リストの先頭を指すポインタ

void loadItemsFromFile(const char *filename){
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("ファイルを開けません");
        return;
    }
    Item *current = head;
    while (!feof(file)) {
        Item *newItem = (Item *)malloc(sizeof(Item));
        if (fscanf(file, "%s %d %d", newItem->name, &newItem->category, &newItem->price) == 3) {
            newItem->next = NULL;
            newItem->purchased = 0;
            if (current == NULL) {
                head = newItem;
                current = newItem;
            } else {
                current->next = newItem;
                current = newItem;
            }
        } else {
            free(newItem);
            break;
        }
    }
    fclose(file);
}

typedef struct {//紙幣、硬貨の情報
    int num_10000;//10000円札の枚数
    int num_5000;//5000円札の枚数
    int num_2000;//2000円札の枚数
    int num_1000;//1000円札の枚数
    int num_500;//500円玉の枚数
    int num_100;//100円玉の枚数
    int num_50;//50円玉の枚数
    int num_10;//10円玉の枚数
    int num_5;//5円玉の枚数
    int num_1;//1円玉の枚数
} Money;

Money inside_money = {0,10,0,10,30,30,30,30,30,30}; // レジ内にある紙幣、硬貨の情報

int money_sum(Money money){//お金の合計金額を計算
    return money.num_10000 * 10000 + money.num_5000 * 5000 + money.num_2000 * 2000 + money.num_1000 * 1000 + money.num_500 * 500 + money.num_100 * 100 + money.num_50 * 50 + money.num_10 * 10 + money.num_5 * 5 + money.num_1 * 1;
}

void addMoney(Money *money1, Money *money2){//お金の加算
    money1->num_10000 += money2->num_10000;
    money1->num_5000 += money2->num_5000;
    money1->num_2000 += money2->num_2000;
    money1->num_1000 += money2->num_1000;
    money1->num_500 += money2->num_500;
    money1->num_100 += money2->num_100;
    money1->num_50 += money2->num_50;
    money1->num_10 += money2->num_10;
    money1->num_5 += money2->num_5;
    money1->num_1 += money2->num_1;
}

void subMoney(Money *money1, Money *money2){//お金の引き算
    money1->num_10000 -= money2->num_10000;
    money1->num_5000 -= money2->num_5000;
    money1->num_2000 -= money2->num_2000;
    money1->num_1000 -= money2->num_1000;
    money1->num_500 -= money2->num_500;
    money1->num_100 -= money2->num_100;
    money1->num_50 -= money2->num_50;
    money1->num_10 -= money2->num_10;
    money1->num_5 -= money2->num_5;
    money1->num_1 -= money2->num_1;
}

void inside_money_check(Money *inside_money) {//レジ内のお金の枚数を確認  //レジ内のお金の枚数が少ない場合は、コンビニ事務所の金庫から補充する
    if(inside_money->num_10000 < 0) {
        inside_money->num_10000++;//この１万円はコンビニ事務所の金庫にある
    }else if(inside_money->num_5000<5){
        inside_money->num_5000 += inside_money->num_10000 * 2;
        inside_money->num_10000 = 0;
    //else if(inside_money->num.2000<5) //2000円札は使わない
    }else if(inside_money->num_1000<5){
        inside_money->num_1000 += inside_money->num_5000 * 2;
        inside_money->num_5000 = 0;
    }else if(inside_money->num_500<5){
        inside_money->num_500 += inside_money->num_1000 * 5;
        inside_money->num_1000 = 0;
    }else if(inside_money->num_100<10){
        inside_money->num_100 += inside_money->num_500 * 2;
        inside_money->num_500 = 0;
    }else if(inside_money->num_50<10){
        inside_money->num_50 += inside_money->num_100 * 5;
        inside_money->num_100 = 0;
    }else if(inside_money->num_10<10){
        inside_money->num_10 += inside_money->num_50 * 5;
        inside_money->num_50 = 0;
    }else if(inside_money->num_5<10){
        inside_money->num_5 += inside_money->num_10 * 2;
        inside_money->num_10 = 0;
    }else if(inside_money->num_1<10){
        inside_money->num_1 += inside_money->num_5 * 5;
        inside_money->num_5 = 0;
    }
}

void printMoney(Money money) { //お金情報の表示//これ要る？
    printf("1万円札の枚数:%d\n", money.num_10000);
    printf("5千円札の枚数:%d\n", money.num_5000);
    printf("2千円札の枚数:%d\n", money.num_2000);
    printf("1千円札の枚数:%d\n", money.num_1000);
    printf("500円玉の枚数:%d\n", money.num_500);
    printf("100円玉の枚数:%d\n", money.num_100);
    printf("50円玉の枚数:%d\n", money.num_50);
    printf("10円玉の枚数:%d\n", money.num_10);
    printf("5円玉の枚数:%d\n", money.num_5);
    printf("1円玉の枚数:%d\n", money.num_1);
}

void calculateChange(int money, Money *inside_money) {//お釣り計算
    Money change = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    while(money >= 10000){
        change.num_10000++;
        money -= 10000;
    }
    while(money >= 5000){
        change.num_5000++;
        money -= 5000;
    }
    /*while(money >= 2000){
        change.num_2000++;
        money -= 2000;
    } */ //2000円札は使わない
    while(money >= 1000){
        change.num_1000++;
        money -= 1000;
    }
    while(money >= 500){
        change.num_500++;
        money -= 500;
    }
    while(money >= 100){
        change.num_100++;
        money -= 100;
    }
    while(money >= 50){
        change.num_50++;
        money -= 50;
    }
    while(money >= 10){
        change.num_10++;
        money -= 10;
    }
    while(money >= 5){
        change.num_5++;
        money -= 5;
    }
    while(money >= 1){
        change.num_1++;
        money -= 1;
    }
    subMoney(inside_money, &change);
    printMoney(change);
}

void register_items(int *total_price, int *tax_price) {// 商品登録
    int is_continue = 1;
    char item_name[100];
    int tax_price_item = 0;
    while(is_continue){
        printf("商品名を入力してください\n");
        scanf("%s", item_name);

        Item *current = head;
        while(current != NULL && strcmp(current->name, item_name) != 0) {
            current = current->next;
        }

        if (current == NULL) {
            printf("商品が見つかりませんでした。\n");
        } else {
            current->purchased = 1;
            if(current->category == 0){
                tax_price_item += current->price * 0.08 / 1.08; // 消費税（軽減税率）
            }else{
                tax_price_item += current->price * 0.1 / 1.1; // 消費税
            }
            *total_price = *total_price + current->price -tax_price_item;
            *tax_price += tax_price_item;
            printf("登録商品名: %s\n", current->name);
            printf("登録商品価格: %d\n", current->price);
            printf("うち消費税: %d\n", tax_price_item);
        }
        printf("登録を続けますか？(1:続ける, 0:終了)\n");
        scanf("%d", &is_continue);
    }
}

void receive_payment(Money *received_money) {// 受け取った金額の入力
    printf("受け取り金額\n");
    printf("1万円札の枚数:");
    scanf("%d", &received_money->num_10000);
    printf("5千円札の枚数:");
    scanf("%d", &received_money->num_5000);
    printf("2千円札の枚数:");
    scanf("%d", &received_money->num_2000);
    printf("1千円札の枚数:");
    scanf("%d", &received_money->num_1000);
    printf("500円玉の枚数:");
    scanf("%d", &received_money->num_500);
    printf("100円玉の枚数:");
    scanf("%d", &received_money->num_100);
    printf("50円玉の枚数:");
    scanf("%d", &received_money->num_50);
    printf("10円玉の枚数:");
    scanf("%d", &received_money->num_10);
    printf("5円玉の枚数:");
    scanf("%d", &received_money->num_5);
    printf("1円玉の枚数:");
    scanf("%d", &received_money->num_1);
}

void printReceiptToFile(Item *purchasedItems, int total_price, int tax_price, int received_money, int change) {// レシートの出力
 // 現在の日時を取得
    time_t t = time(NULL);
    struct tm *local = localtime(&t);

    // ファイル名を格納するための文字列バッファ
    char filename[50];

    // ファイル名をsprintfを使ってフォーマット
    sprintf(filename, "%d-%d-%d-%d:%d-receipt.txt", local->tm_year + 1900, local->tm_mon + 1, local->tm_mday, local->tm_hour, local->tm_min);

    // ファイルを開く
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("ファイルを開けません");
        return;
    }
    fprintf(file, "--- レシート ---\n");
    fprintf(file, "%d-%d-%d %d:%d\n", local->tm_year + 1900, local->tm_mon + 1, local->tm_mday, local->tm_hour, local->tm_min); // 現在の日付と時刻

    fprintf(file, "\n購入商品リスト:\n");
    while (purchasedItems != NULL) {
        if(purchasedItems->purchased == 1){
        fprintf(file, "商品名: %s, 価格: %d円\n", purchasedItems->name, purchasedItems->price);
        }
        purchasedItems = purchasedItems->next;
    }

    fprintf(file, "\n合計金額: %d円\n", total_price);
    fprintf(file, "消費税: %d円\n", tax_price);
    fprintf(file, "お預かり金額: %d円\n", received_money);
    fprintf(file, "お釣り: %d円\n", change);
    fprintf(file, "-------------------\n");

    fclose(file);
}

void calculate(int *total_price, int *tax_price) {// 会計
    Money received_money = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int current_total_price = 0;
    int current_tax_price = 0;

    register_items(&current_total_price, &current_tax_price);

    printf("合計金額:%d\n", current_total_price+current_tax_price);
    receive_payment(&received_money);

    
    printf("お預かり金額:%d\n", money_sum(received_money));
    
    if(money_sum(received_money) < current_total_price) {
        printf("お預かり金額が足りません。\n");
        return;
    }
    addMoney(&inside_money, &received_money);
    int change = money_sum(received_money) - current_total_price;
    printf("お釣り:%d\n", change);
    calculateChange(change, &inside_money);
    printReceiptToFile(head, current_total_price, current_tax_price, money_sum(received_money), change);
    *total_price += current_total_price;
    *tax_price += current_tax_price;
}

void check(int total_price_today,int initial_money,int total_tax_today){//在高点検
    printf("在高点検を行います。\n");
    printf("レジ内の金額:%d\n", money_sum(inside_money));
    printf("本日の売上金額:%d\n", total_price_today-total_tax_today);
    printf("本日の消費税額:%d\n", total_tax_today);
    printf("+-差分:%d\n", money_sum(inside_money) - (initial_money + total_price_today+total_tax_today));
}

void settlement(int *total_price_today, int *total_tax_today, int *refund_today, int *public_survice_today){//精算業務
    printf("精算を行います。\n");
    printf("本日の返金額:%d\n", *refund_today);
    *refund_today = 0;
    printf("本日の収納代行件数:%d\n", *public_survice_today);
    *public_survice_today = 0;
    int sum =  *total_price_today;
    calculateChange(sum,&inside_money);
     printf("本日の売上金額:%d\n", *total_price_today);
    *total_price_today = 0;
    printf("本日の消費税額:%d\n", *total_tax_today);
    *total_tax_today = 0;
    printf("レジ内の金額:%d\n", money_sum(inside_money));
}

void refund(int *total_price_today, int *total_tax_today, int *refund_today, Money *inside_money) {// 返金
    char item_name[100];
    int refund_amount;

    printf("返品する商品名を入力してください\n");
    scanf("%s", item_name);

    Item *current = head;
    while(current != NULL && strcmp(current->name, item_name) != 0) {
        current = current->next;
    }

    if (current == NULL) {
        printf("商品が見つかりませんでした。\n");
    } else {
        printf("返品商品名: %s\n", current->name);
        printf("返品商品価格: %d\n", current->price);

        refund_amount = current->price;
        printf("返金額: %d\n", refund_amount);
        calculateChange(refund_amount, inside_money); // レジ内のお金を更新
        *total_price_today -= refund_amount; // 売上金額から返金額を減算

        if(current->category == 0) {
            *total_tax_today -= refund_amount * 0.08 / 1.08; // 消費税から返金額の消費税分を減算
        } else {
            *total_tax_today -= refund_amount * 0.1 / 1.1; // 消費税から返金額の消費税分を減算
        }
        *refund_today += refund_amount; // 返金総額に返金額を加算
    }
}

int main(){
    int initial_money = money_sum(inside_money); // レジの初期金額
    int mode; // モード
    int total_price_today = 0; // 本日の売上金額
    int total_tax_today = 0; // 本日の消費税額
    int refund_today = 0; // 本日の返金額
    int public_survice_today = 0; // 本日の収納代行件数
    int is_continue = 1; // 続けるかどうか
    loadItemsFromFile("items.txt"); // 商品情報の読み込み

    while(is_continue){
        printf("モードを選択してください\n");
        printf("1:会計\n");
        printf("2:レジ点検\n");
        printf("3:レジ精算\n");
        printf("4:返金\n");
        printf("5:収納代行\n");//収納代行は、コンビニのレジで公共料金の支払いなどを行うこと
        printf("6:レジ休止\n");
        printf("入力:");
        scanf("%d", &mode);

        switch(mode) {
        case 1:
            calculate(&total_price_today, &total_tax_today);
            break;
        case 2:
            printf("レジ点検\n");
            printf("在高点検\n");
            check(total_price_today, initial_money, total_tax_today);
            break;
        case 3:
            printf("レジ精算\n");
            printf("精算します。\n");
            settlement(&total_price_today, &total_tax_today, &refund_today, &public_survice_today);
            break;
        
        case 4:
            printf("返金\n");
            refund(&total_price_today, &total_tax_today, &refund_today, &inside_money);
            break;
        case 5:
            printf("収納代行\n");
            public_survice_today++;//今回は収納代行件数をカウントするだけで、実際に実装はしない
            printf("収納代行サービスを行いました。\n"   );
            break;
        case 6:
            printf("レジ休止\n");
            printf("休止します。\n");
            is_continue = 0;
            break;
        default:
            printf("モードが不正です\n");
        }
        inside_money_check(&inside_money);
    }
}
