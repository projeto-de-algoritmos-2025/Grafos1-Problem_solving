#include <bits/stdc++.h>

using namespace std;

const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, 1, 0, -1};

bool isValid(int x, int y, int rows, int cols,
             const vector<vector<char>> &maze) {
  return (x >= 0 && x < rows && y >= 0 && y < cols && maze[x][y] == '.');
}

void dfs(int x, int y, vector<vector<bool>> &visited,
         const vector<vector<char>> &maze, vector<pair<int, int>> &traversal,
         int rows, int cols) {
  visited[x][y] = true;

  traversal.push_back({x, y});

  for (int i = 0; i < 4; i++) {
    int newX = x + dx[i];
    int newY = y + dy[i];

    if (isValid(newX, newY, rows, cols, maze) && !visited[newX][newY]) {
      dfs(newX, newY, visited, maze, traversal, rows, cols);
    }
  }
}

int main() {
  int n, m, k;
  cin >> n >> m >> k;

  vector<vector<char>> maze(n, vector<char>(m));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cin >> maze[i][j];
    }
  }

  int startX = -1, startY = -1;
  for (int i = 0; i < n && startX == -1; i++) {
    for (int j = 0; j < m; j++) {
      if (maze[i][j] == '.') {
        startX = i;
        startY = j;
        break;
      }
    }
  }

  if (startX == -1) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        cout << maze[i][j];
      }
      cout << endl;
    }
    return 0;
  }

  vector<vector<bool>> visited(n, vector<bool>(m, false));
  vector<pair<int, int>> traversal;
  dfs(startX, startY, visited, maze, traversal, n, m);

  int cellsToRemove = min(k, (int)traversal.size());
  vector<vector<char>> result = maze;

  for (int i = traversal.size() - cellsToRemove; i < traversal.size(); i++) {
    int x = traversal[i].first;
    int y = traversal[i].second;
    result[x][y] = 'X';
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cout << result[i][j];
    }
    cout << endl;
  }

  return 0;
}
