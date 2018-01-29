#include <iostream>
#include <algorithm>
using namespace std;
int main(int argc, char const *argv[]) {
  int n, m, t;
  int a[128];
  cin >> n >> m >> t;
  for (int i = 0; i < n; ++i) cin >> a[i];
  int ret = a[0] - m;
  for (int i = 1; i < n; ++i) {
    int add = a[i] - (a[i - 1] + 2 * m);
    if (add > 0) ret += add;
  }
  int add = t - (a[n - 1] + m);
  if (add > 0) ret += add;
  cout << ret << endl;
  return 0;
}
