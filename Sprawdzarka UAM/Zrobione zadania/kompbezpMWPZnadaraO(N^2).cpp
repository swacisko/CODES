#include <bits/stdc++.h>
#define FOR(i, a, b) for(int i =(a); i <=(b); ++i)
#define RE(i, n) FOR(i, 1, n)
#define make2(type, x, y) type x,y; cin>>x>>y;
using namespace std;
const int N = 5e2 + 5;
long long comp[N], dp[2][N];
int main() {
  make2(int, n, mod);
  int now = 1, res = 0;
  dp[0][0] = 1;
  RE (i, n) {
    dp[now][0] = 0;
    FOR (j, 1, n) dp[now][j] = (2 * dp[now][j - 1] + dp[now ^ 1][j - 1]) % mod;
    FOR (j, 0, n) dp[now][j] = dp[now][j] * (n - j + 1) % mod;
    comp[i] = dp[now][n];
    now ^= 1;
  }
  RE (i, n) res = (res + comp[i] * (comp[i - 1] + 2 * comp[i] + comp[i + 1])) % mod;
  cout<<1 + (res - 1 + mod) % mod<<endl;
  return 0;
}
