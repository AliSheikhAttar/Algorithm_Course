#include <iostream>
#include <vector>

using std::pair;
using std::vector;
vector<int> visited;

void reach(vector<vector<int>> &adj, int x)
{
  visited[x] = 1;

  for (size_t i = 0; i < adj[x].size(); i++)
  {
    if (visited[adj[x][i]] == 0)
    {
      reach(adj, adj[x][i]);
    }
  }
}

int number_of_components(vector<vector<int>> &adj, int n)
{
  int res = 0;
  for (size_t i = 0; i < n; i++)
  {
    if (visited[i] == 0)
    {
      reach(adj, i);
      res++;
    }
  }
  return res;
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
  std::cout << number_of_components(adj, n);
}
