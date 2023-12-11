//ミニストップのレジシステムを再現する
#include <stdio.h>
#include <stdlib.h>

typedef struct { // 商品情報の構造体
    char name[100];
    int category;
    int price;
} Item;

typedef struct {//レジ内にある紙幣、硬貨の情報
    int num_10000;//10000円札の枚数
    int num_5000;//5000円札の枚数
    int num_2000;//2000円札の枚数
    int num_1000;//1000円札の枚数
    int num_500;//500円玉の枚数
    int num_100;//100円玉の枚数
    int num_50;//50円玉の枚数
    int num_10;//10円玉の枚数
    int num_5;//5円玉の枚数
    int num_1;//1円玉の枚数;
} inside_Money;

inside_Money inside_money = {0,10,0,10,30,30,30,30,30,30}; // レジ内にある紙幣、硬貨の情報

int inside_money_sum(){
    return inside_money.num_10000*10000 + inside_money.num_5000*5000 + inside_money.num_2000*2000 + inside_money.num_1000*1000 + inside_money.num_500*500 + inside_money.num_100*100 + inside_money.num_50*50 + inside_money.num_10*10 + inside_money.num_5*5 + inside_money.num_1*1;
}

Item item[100]; //商品

void calurate(){//商品登録
    typedef struct {//受け取った金額の情報
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
    } Recived_Money;

    Recived_Money recived_money = {0,0,0,0,0,0,0,0,0,0};

    int current_total_price = 0;
    int is_continue = 1;
    int item_num;
    while(is_continue){
        printf("商品の登録(商品配列のインデックスを入力)\n");
        scanf("%d", &item_num);
        printf("登録商品名:%s\n", item[item_num].name);
        printf("登録商品価格:%d\n", item[item_num].price);
        current_total_price += item[item_num].price;
        printf("登録を続けますか？(1:続ける, 0:終了)\n");
        scanf("%d", &is_continue);
    }
    printf("合計金額:%d\n", current_total_price);
    printf("受け取り金額\n");
    printf("1万円札の枚数:");
    scanf("%d", &recived_money.num_10000);
    printf("5千円札の枚数:");
    scanf("%d", &recived_money.num_5000);
    printf("2千円札の枚数:");
    scanf("%d", &recived_money.num_2000);
    printf("1千円札の枚数:");
    scanf("%d", &recived_money.num_1000);
    printf("500円玉の枚数:");
    scanf("%d", &recived_money.num_500);
    printf("100円玉の枚数:");
    scanf("%d", &recived_money.num_100);
    printf("50円玉の枚数:");
    scanf("%d", &recived_money.num_50);
    printf("10円玉の枚数:");
    scanf("%d", &recived_money.num_10);
    printf("5円玉の枚数:");
    scanf("%d", &recived_money.num_5);
    printf("1円玉の枚数:");
    scanf("%d", &recived_money.num_1);
    int recived_money_sum = recived_money.num_10000*10000 + recived_money.num_5000*5000 + recived_money.num_2000*2000 + recived_money.num_1000*1000 + recived_money.num_500*500 + recived_money.num_100*100 + recived_money.num_50*50 + recived_money.num_10*10 + recived_money.num_5*5 + recived_money.num_1*1;
    printf("お預かり金額:%d\n", recived_money_sum);
    printf("お釣り:%d\n", recived_money_sum - current_total_price);
}

void addItem(){//新製品登録
    printf("新製品登録を行います。\n");
    printf("商品名を入力してください\n");
    scanf("%s", item[0].name);
    printf("商品価格を入力してください\n");
    scanf("%d", &item[0].price);
    printf("商品名:%s\n", item[0].name);
    printf("商品価格:%d\n", item[0].price);
}

void check(int total_price_today,int initial_money){//在高点検
    printf("在高点検を行います。\n");
    printf("レジ内の金額:%d\n", inside_money_sum());
    printf("本日の売上金額:%d\n", total_price_today);
    printf("+-差分:%d\n", inside_money_sum() - (initial_money + total_price_today));
}

int main(){
    int initial_money = inside_money_sum();
    int mode; // モード
    int total_price_today = 0; // 本日の売上金額
    int total_tax_today = 0; // 本日の消費税額
    int refund_today = 0; // 本日の返金額
    int public_survice_today = 0; // 本日の収納代行件数
    int is_continue = 1; // 続けるかどうか

    while(is_continue){
        printf("モードを選択してください\n");
        printf("1:商品登録\n");
        printf("2:レジ点検\n");
        printf("3:レジ精算\n");
        printf("4:レジ休止\n");
        printf("入力:");
        scanf("%d", &mode);

        switch(mode) {
        case 1:
            calurate();
            break;
        case 2:
            {
                int mode_check;
                printf("レジ点検\n");
                printf("モードを選択してください\n");
                printf("1:在高点検\n");
                printf("2:新製品登録\n");
                printf("入力:");
                scanf("%d", &mode_check);

                switch(mode_check) {
                    case 1:
                        printf("在高点検\n");
                        check(total_price_today, initial_money);
                        break;
                    case 2:
                        printf("新製品登録\n");
                        addItem();
                        break;
                    default:
                        printf("モードが不正です\n");
                }
            }
            break;
        case 3:
            printf("レジ精算\n");
            printf("精算します。\n");
            break;
        case 4:
            printf("レジ休止\n");
            printf("休止します。\n");
            is_continue = 0;
            break;
        default:
            printf("モードが不正です\n");
        }
    }
}
