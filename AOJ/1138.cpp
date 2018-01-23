#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <queue>

using namespace std;
#define INF 1e9

int N, M, P;
int S, G;
struct Edge {
  int to, dist;
};
vector < Edge > edge[32];

// 今いる頂点、馬券の使用状況
double min_time[32][1 << 8];
int used[32][1 << 8];
int ticket[8];

// tuple(総時間、今いる頂点、馬券の使用状況)
typedef tuple < double, int, int> Data;
void Dijkstra() {

  for (int i = 0; i < 32; ++i)
    for (int j = 0; j < 1 << 8; ++j)
        min_time[i][j] = INF;


  priority_queue < Data, vector < Data >, greater < Data > > que;
  que.push(make_tuple(0, S, 0));
  min_time[S][0] = 0;

  while (!que.empty()) {
    Data d = que.top(); que.pop();
    double time;
    int v, state;
    tie(time, v, state) = d;

    for (auto &e: edge[v]) {
      //        cout << v << " -> " << e.to << endl;
      for (int h_num = 0; h_num < N; ++h_num) {
	       if (!((state >> h_num) & 1)) { // 馬券が消費されていなかったら
	          int next_state = state | (1 << h_num);
	           //            cout << next_state << endl;
          if (min_time[e.to][next_state] > time + (double)e.dist / ticket[h_num]) {
             //              cout << v << " -> " << e.to << endl;
	           min_time[e.to][next_state] = time + (double)e.dist / ticket[h_num];
	           que.push(make_tuple(min_time[e.to][next_state], e.to, next_state));
	        }
	      }
      }
    }
  }
}

int main(int argc, char const *argv[]) {
  while (cin >> N >> M >> P >> S >> G && N) {
    S--; G--; // to zero idx
    for (int i = 0; i < 32; ++i)
      edge[i].clear();
    for (int i = 0; i < N; ++i)
      cin >> ticket[i];

    for (int i = 0; i < P; ++i) {
      int a, b, dist;
      cin >> a >> b >> dist;
      --a; --b;
      edge[a].push_back(Edge{b, dist});
      edge[b].push_back(Edge{a, dist});
    }


    Dijkstra();
    double ret = INF;
    for (int i = 0; i < 1 << 8; ++i) {
      //        cout << min_time[G][i] << endl;
      ret = min(ret, min_time[G][i]);
    }
    if (ret == INF) {
      cout << "Impossible" << endl;
    } else {
      cout << ret << endl;
    }
  }
  return 0;
}
