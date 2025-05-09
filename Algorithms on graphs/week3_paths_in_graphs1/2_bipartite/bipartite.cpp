#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using std::queue;
using std::vector;

int bipartite(vector<vector<int>> &adj)
{
  vector<int> distances(adj.size(), INT_MAX);
  for (size_t j = 0; j < adj.size(); j++)
  {
    if (distances[j] == INT_MAX)
    {
      std::queue<int> q;
      q.push(j);
      distances[j] = 0;
      while (!q.empty())
      {
        auto v = q.front();
        q.pop();
        for (int i = 0; i < adj[v].size(); i++)
        {
          if (distances[adj[v][i]] == INT_MAX)
          {
            q.push(adj[v][i]);
            distances[adj[v][i]] = distances[v] + 1;
          }
          else if (distances[adj[v][i]] == distances[v])
            return 0;
        }
      }
    }
  }
  return 1;
}

int main()
{
  int n, m;
  std::cin >> n >> m;
  vector<vector<int>> adj(n, vector<int>());
  for (int i = 0; i < m; i++)
  {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }
  std::cout << bipartite(adj);
}
