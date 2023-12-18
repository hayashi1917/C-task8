//コンビニのレジシステムを再現する
#include <stdio.h>
#include <stdlib.h>

typedef struct { // 商品情報の構造体 //連結リスト
    char name[100];
    int category;
    int price;
    int salecount;
    Item *next;
} Item;

Item item[100]; //商品

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

int money_sum(Money money){
    return money.num_10000 * 10000 + money.num_5000 * 5000 + money.num_2000 * 2000 + money.num_1000 * 1000 + money.num_500 * 500 + money.num_100 * 100 + money.num_50 * 50 + money.num_10 * 10 + money.num_5 * 5 + money.num_1 * 1;
}

Money addMoney(Money money1, Money money2){
    Money money = {0,0,0,0,0,0,0,0,0,0};
    money.num_10000 = money1.num_10000 + money2.num_10000;
    money.num_5000 = money1.num_5000 + money2.num_5000;
    money.num_2000 = money1.num_2000 + money2.num_2000;
    money.num_1000 = money1.num_1000 + money2.num_1000;
    money.num_500 = money1.num_500 + money2.num_500;
    money.num_100 = money1.num_100 + money2.num_100;
    money.num_50 = money1.num_50 + money2.num_50;
    money.num_10 = money1.num_10 + money2.num_10;
    money.num_5 = money1.num_5 + money2.num_5;
    money.num_1 = money1.num_1 + money2.num_1;
    return money;
}

Money subMoney(Money money1, Money money2){
    Money money = {0,0,0,0,0,0,0,0,0,0};
    money.num_10000 = money1.num_10000 - money2.num_10000;
    money.num_5000 = money1.num_5000 - money2.num_5000;
    money.num_2000 = money1.num_2000 - money2.num_2000;
    money.num_1000 = money1.num_1000 - money2.num_1000;
    money.num_500 = money1.num_500 - money2.num_500;
    money.num_100 = money1.num_100 - money2.num_100;
    money.num_50 = money1.num_50 - money2.num_50;
    money.num_10 = money1.num_10 - money2.num_10;
    money.num_5 = money1.num_5 - money2.num_5;
    money.num_1 = money1.num_1 - money2.num_1;
    return money;
}

Money inside_money = {0,10,0,10,30,30,30,30,30,30}; // レジ内にある紙幣、硬貨の情報

void inside_money_check(Money inside_money){//レジ内のお金の枚数を確認
    if(inside_money.num_10000<0){
        +=inside_money.num_10000;//この１万円はコンビニ事務所の金庫にある
    }else if(inside_money.num.5000<5){
        inside_money.num.5000 += inside_money.num.10000 * 2;
        inside_money.num.10000 = 0;
    //else if(inside_money.num.2000<5) //2000円札は使わない
    }else if(inside_money.num.1000<5){
        inside_money.num.1000 += inside_money.num.5000 * 2;
        inside_money.num.5000 = 0;
    }else if(inside_money.num.500<5){
        inside_money.num.500 += inside_money.num.1000 * 5;
        inside_money.num.1000 = 0;
    }else if(inside_money.num.100<10){
        inside_money.num.100 += inside_money.num.500 * 2;
        inside_money.num.500 = 0;
    }else if(inside_money.num.50<10){
        inside_money.num.50 += inside_money.num.100 * 5;
        inside_money.num.100 = 0;
    }else if(inside_money.num.10<10){
        inside_money.num.10 += inside_money.num.50 * 5;
        inside_money.num.50 = 0;
    }else if(inside_money.num.5<10){
        inside_money.num.5 += inside_money.num.10 * 2;
        inside_money.num.10 = 0;
    }else if(inside_money.num.1<10){
        inside_money.num.1 += inside_money.num.5 * 5;
        inside_money.num.5 = 0;
    }
}

void printMoney(Money money) { //お金情報の表示
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

void calculateChange(int money, Money/ inside_money) {//お釣り計算
    Money change = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    while(money >= 10000){
        change.num_10000++;
        money -= 10000;
    }
    while(money >= 5000){
        change.num_5000++;
        money -= 5000;
    }
    while(money >= 2000){
        change.num_2000++;
        money -= 2000;
    }
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
    subMoney(inside_money, change);
    printMoney(change);
}
    
void calculate(){//商品登録
    
    Money received_money = {0,0,0,0,0,0,0,0,0,0};
    Money change_money = {0,0,0,0,0,0,0,0,0,0};

    int current_total_price = 0;
    int current_tax_price = 0;
    int is_continue = 1;
    int item_num;

    while(is_continue){
        printf("商品の登録(商品配列のインデックスを入力)\n");
        scanf("%d", &item_num);
        printf("登録商品名:%s\n", item[item_num].name);
        printf("登録商品価格:%d\n", item[item_num].price);

        current_total_price += item[item_num].price;
        if(item[item_num].category == 0){
            current_tax_price += item[item_num].price * 0.08;//消費税（軽減税率）
            return;
        }else{
            current_tax_price += item[item_num].price * 0.1;//消費税
            return;
        }

        printf("登録を続けますか？(1:続ける, 0:終了)\n");
        scanf("%d", &is_continue);
    }

    printf("合計金額:%d\n", current_total_price);
    printf("受け取り金額\n");
    printf("1万円札の枚数:");
    scanf("%d", &received_money.num_10000);
    printf("5千円札の枚数:");
    scanf("%d", &received_money.num_5000);
    printf("2千円札の枚数:");
    scanf("%d", &received_money.num_2000);
    printf("1千円札の枚数:");
    scanf("%d", &received_money.num_1000);
    printf("500円玉の枚数:");
    scanf("%d", &received_money.num_500);
    printf("100円玉の枚数:");
    scanf("%d", &received_money.num_100);
    printf("50円玉の枚数:");
    scanf("%d", &received_money.num_50);
    printf("10円玉の枚数:");
    scanf("%d", &received_money.num_10);
    printf("5円玉の枚数:");
    scanf("%d", &received_money.num_5);
    printf("1円玉の枚数:");
    scanf("%d", &received_money.num_1);
    inside_money = addMoney(inside_money, received_money);
    printf("お預かり金額:%d\n", money_sum(received_money));
    if(money_sum(received_money)- current_total_price < 0){
        printf("お預かり金額が足りません。\n");
        return;
    }
    printf("お釣り:%d\n", money_sum(received_money) - current_total_price);
    caluculateCarge(money_sum(received_money) - current_total_price);
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
    printf("+-差分:%d\n", money_sum(inside_money) - (initial_money + total_price_today));
}

void settlement(int total_price_today, int total_tax_today, int refund_today, int public_survice_today){//精算業務
    printf("精算を行います。\n");
    printf("本日の売上金額:%d\n", total_price_today);
    total_price_today = 0;
    printf("本日の消費税額:%d\n", total_tax_today);
    total_tax_today = 0;
    printf("本日の返金額:%d\n", refund_today);
    refund_today = 0;
    printf("本日の収納代行件数:%d\n", public_survice_today);
    public_survice_today = 0;
    printf("レジ内の金額:%d\n", inside_money_sum());

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
            caluculate();
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
            settlement(total_price_today, total_tax_today, refund_today, public_survice_today);
            break;
        case 4:
            printf("レジ休止\n");
            printf("休止します。\n");
            is_continue = 0;
            break;
        default:
            printf("モードが不正です\n");
        }
        inside_money_check(inside_money);
    }
}
