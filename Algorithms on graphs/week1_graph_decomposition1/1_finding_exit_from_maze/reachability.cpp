#include <iostream>
#include <vector>

using std::pair;
using std::vector;
vector<int> visited;
int reach(vector<vector<int>> &adj, int x, int y)
{
  visited[x] = 1;
  if (x == y)
    return 1;

  for (size_t i = 0; i < adj[x].size(); i++)
  {
    if (visited[adj[x][i]] == 0)
    {
      if (reach(adj, adj[x][i], y) == 1)
        return 1;
    }
  }

  return 0;
}

int main()
{
  size_t n, m;
  std::cin >> n >> m;
  vector<vector<int>> adj(n, vector<int>());
  visited.resize(n);
  for (size_t i = 0; i < m; i++)
  {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }
  int x, y;
  std::cin >> x >> y;
  std::cout << reach(adj, x - 1, y - 1);
}
