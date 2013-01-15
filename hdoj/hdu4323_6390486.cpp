/*
 *   Author: Tangyao
 *   Email:  tangyao0792@gmail.com
 *   tangyao0792.github.com
 */
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int idx;
struct BKNode {
    char value[15];
    int children[30];
}node[1510];

void init(int i, char *newValue) {
    strcpy(node[i].value, newValue);
    memset(node[i].children, -1, sizeof(node[i].children));
}

int CompareString(char *s1, char *s2) {
    int dp[15][15];
    memset(dp, 0, sizeof(dp));

    int m = strlen(s1),
        n = strlen(s2),
        i = 0, j = 0;

    for (i = 0; i<= m; ++i) {
        dp[i][0] = i;
    }
    for (j = 0; j <= n; ++j) {
        dp[0][j] = j;
    }
    int cost = 0;
    for (i = 1;i <= m; ++i) {
        for (j=1;j<=n;++j) {
            if (s1[i-1] == s2[j-1]) {
                cost = 0;
            } else {
                cost = 1;
            }
            dp[i][j]= min(min(dp[i-1][j-1] + cost, dp[i-1][j] + 1), dp[i][j-1] + 1);
        }
    }
    return dp[m][n];
}

void insert(int r, char *rhs) {
    int dist = CompareString(node[r].value, rhs);
    if (dist != 0) {
        if (node[r].children[dist + 15] != -1) {
            insert(node[r].children[dist + 15], rhs);
        } else {
            init(idx, rhs);
            node[r].children[dist + 15] = idx++;
        }
    }
}

int find(int r, char *rhs, int threshold) {
    int dist = CompareString(node[r].value, rhs);
    int res = 0;
    if (dist<=threshold){
        res++;
    }

    int dmin=dist-threshold;
    int dmax=dist+threshold;

    for (int i=dmin; i<=dmax; i++) {
        if (node[r].children[i + 15] != -1) {
            res += find(node[r].children[i + 15], rhs, threshold);
        }
    }
    return res;
}

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    int n, m;
    char line[1510];
    int cs;
    scanf("%d", &cs);
    for (int c = 1; c <= cs; c++)
    {
        int root = -1;
        idx = 0;

        scanf("%d%d", &n, &m);
        for (int i = 0; i < n; i++) {
            scanf("%s", line);
            if (i == 0) {
                init(idx, line);
                root = idx++;
            } else {
                insert(root, line);
            }
        }
        printf ("Case #%d:\n", c);
        int dis;
        for (int i = 0; i < m; i++) {
            scanf("%s%d", line, &dis);
            printf("%d\n", find(root, line, dis));
        }
    }

    return 0;
}
