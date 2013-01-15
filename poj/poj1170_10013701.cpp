#include <stdio.h>
#include <string.h>
#define N 7
#define MAX 1000000
typedef struct
{
    int num[N], v;
} offer;
/* item: DP中保存状态的数组
* noffer:各种优惠的总数目，包括单价优惠
*/
int item[N][N][N][N][N], noffer;
int code[1005];
offer list_offer[150];

int dp(int basket[N])
{
    int i, j, min = MAX, v, nbasket[N];
    if (item[basket[1]][basket[2]][basket[3]][basket[4]][basket[5]] != -1)
        return item[basket[1]][basket[2]][basket[3]][basket[4]][basket[5]];
    for (i = 1; i <= noffer; i++)
    {
        int fail = 0;
        /* 检查某个优惠能否使用，就是商品的数量是否会超出我们需要的数量 */
        for (j = 1; j <= 5; j++)
            if ((nbasket[j] = basket[j] - list_offer[i].num[j]) < 0)
            {
                fail = 1;
                break;
            }
        if (fail)
            continue;
        /* 对前一个状态进行DP */
        v = dp(nbasket) + list_offer[i].v;
        if (v < min)
            min = v;
    }
    item[basket[1]][basket[2]][basket[3]][basket[4]][basket[5]] = min;
    return min;
}

int main()
{
    int i, j, id, nk, ioffer = 1, p, no, a1, a2, a3, a4, a5;
    /* basket：当前需要商品的列表 */
    int basket[N];
    memset(basket, 0, sizeof(basket));
    for (a1 = 0; a1 <= 5; a1++)
        for (a2 = 0; a2 <= 5; a2++)
            for (a3 = 0; a3 <= 5; a3++)
                for (a4 = 0; a4 <= 5; a4++)
                    for (a5 = 0; a5 <= 5; a5++)
                        item[a1][a2][a3][a4][a5] = -1;

    item[0][0][0][0][0] = 0;

    scanf("%d", &nk);
    for (i = 1; i <= nk; i++)
    {
        scanf("%d%d%d", &id, &basket[i], &p);
        /* 用code数组对商品编号和我们题目商品的实际下标进行转化 */
        code[id] = i;
        /* 此处把商品的单价也看作是一种优惠 */
        memset(list_offer[ioffer].num, 0, sizeof(list_offer[ioffer].num));
        list_offer[ioffer].num[i] = 1;
        list_offer[ioffer].v = p;
        ioffer++;
    }
    scanf("%d", &no);
    for (i = 1; i <= no; i++)
    {
        int ni, n2;
        scanf("%d", &ni);
        for (j = 1; j <= ni; j++)
        {
            scanf("%d%d", &id, &n2);
            id = code[id];
            list_offer[ioffer].num[id] = n2;
        }
        scanf("%d", &p);
        list_offer[ioffer].v = p;
        ioffer++;
    }
    noffer = ioffer - 1;
    if (!nk)
        printf("0");
    else
        printf("%d", dp(basket));
    return 0;
}
