#include <iostream>
#include <vector>

using std::pair;
using std::vector;

vector<int> visited;

bool dfs_circle(vector<vector<int>> &adj,vector<int> &explored, vector<int> &visited_nodes, int x)
{
  visited[x] = 1;
  visited_nodes[x] = 1;
  for (int i = 0; i < adj[x].size(); i++)
  {
    if (visited_nodes[adj[x][i]] == 1 && !explored[adj[x][i]])
      return true;
    if (dfs_circle(adj, explored, visited_nodes, adj[x][i]))
      return true;
  }
  explored[x] = 1;
  return false;
}

int acyclic(vector<vector<int>> &adj)
{
  for (int i = 0; i < visited.size(); i++)
  {
    if (visited[i] == 0)
    {
      auto explored = vector<int>(visited.size(), 0);
      auto visited_nodes = vector<int>(visited.size(), 0);
      if (dfs_circle(adj, explored,visited_nodes,  i))
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
  visited = vector<int>(n, 0);
  for (size_t i = 0; i < m; i++)
  {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
  }
  std::cout << acyclic(adj);
}
