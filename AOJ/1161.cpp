#include <iostream>
#include <algorithm>
using namespace std;

int dp[300][300];
int w[300];

// 何個落とせるか
int solve(int l, int r) {
  if (l >= r) return 0;
  // 基底（はじめ（1回目）に隣接している区間を落とす）
  if (l == r - 1) return abs(w[l] - w[r]) <= 1 ? 2 : 0;
  if (~dp[l][r]) return dp[l][r];

  int ret = 0;
  // 1回目から順調に進んでいたら値を足していく
  int progress = solve(l + 1, r - 1);
  //                                前までの進捗状況は r - l - 1 が理想
  if (abs(w[l] - w[r]) <= 1 && progress == r - l - 1)ret += 2 + progress;

  for (int i = l; i < r; ++i) // i を中心として区間を分ける
    ret = max(ret, solve(l, i) + solve(i + 1, r));
  return dp[l][r] = ret;
}

int main(int argc, char const *argv[]) {
  int n;
  while (cin >> n && n) {
    for (int i = 0; i < n; ++i) cin >> w[i];
    for (int i = 0; i < 300; ++i)
      for (int j = 0; j < 300; ++j)
        dp[i][j] = -1;
    int ret = solve(0, n-1);
    cout << ret << endl;
  }
  return 0;
}
