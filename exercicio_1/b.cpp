#include <bits/stdc++.h>

using namespace std;

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  // FIFO
  int n, t; cin >> n >> t;
  vector<char> V(n);

  for (char &c : V)
    cin >> c;

  while (t--)
    for (int i = 0; i < n; ++i) {
      if (i + 1 == n) break;
      if (V[i] == 'B' && V[i + 1] == 'G') {
        char tmp = V[i];
        V[i] = V[i + 1];
        V[i + 1] = tmp;
        i++;
    }
  }

  for (char &c : V)
    cout << c;
  cout << '\n';

  return 0;
}
