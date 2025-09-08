#include <bits/stdc++.h>
using namespace std;

int main() {
  int n, m;
  cin >> n >> m;

  vector<int> cats(n + 1);
  for (int i = 1; i <= n; i++) {
    cin >> cats[i];
  }

  vector<vector<int>> tree(n + 1);
  for (int i = 0; i < n - 1; i++) {
    int x, y;
    cin >> x >> y;
    tree[x].push_back(y);
    tree[y].push_back(x);
  }

  int validRestaurants = 0;

  function<void(int, int, int)> dfs = [&](int node, int parent,
                                          int consecutiveCats) {
    if (cats[node] == 1) {
      consecutiveCats++;
    } else {
      consecutiveCats = 0;
    }

    if (consecutiveCats > m) {
      return;
    }

    bool isLeaf = true;
    for (int neighbor : tree[node]) {
      if (neighbor != parent) {
        isLeaf = false;
        dfs(neighbor, node, consecutiveCats);
      }
    }

    if (isLeaf && node != 1) {
      validRestaurants++;
    }
  };

  dfs(1, 0, 0);

  cout << validRestaurants << endl;

  return 0;
}
