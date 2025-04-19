#include <algorithm>
#include <iostream>
#include <vector>

using std::pair;
using std::vector;

void dfs(vector<vector<int>> &adj, vector<int> &used, int x)
{
  used[x] = 1;
  for (size_t i = 0; i < adj[x].size(); i++)
  {
    if (used[adj[x][i]] == 0)
      dfs(adj, used, adj[x][i]);
  }
}

void dfs_sort(vector<vector<int>> &adj, vector<int> &used, vector<int> &order, int x)
{
  used[x] = 1;
  for (size_t i = 0; i < adj[x].size(); i++)
  {
    if (used[adj[x][i]] == 0)
      dfs_sort(adj, used, order, adj[x][i]);
  }
  order.push_back(x);
}

vector<int> toposort(vector<vector<int>> adj)
{
  vector<int> used(adj.size(), 0);
  vector<int> order;
  for (size_t i = 0; i < adj.size(); i++)
  {
    if (used[i] == 0)
      dfs_sort(adj, used, order, i);
  }
  reverse(order.begin(), order.end());

  return order;
}

int number_of_strongly_connected_components(vector<vector<int>> &adj, vector<int> &order)
{
  int result = 0;
  vector<int> used(adj.size(), 0);
  for (int i = 0; i < order.size(); i++)
  {
    if (used[order[i]] == 0){
      dfs(adj, used, order[i]);
      result++;
    }
  }

  return result;
}

int main()
{
  size_t n, m;
  std::cin >> n >> m;
  vector<vector<int>> adj(n, vector<int>());
  vector<vector<int>> reverse_adj(n, vector<int>());
  for (size_t i = 0; i < m; i++)
  {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    reverse_adj[y - 1].push_back(x - 1);
  }
  auto order = toposort(reverse_adj);
  std::cout << number_of_strongly_connected_components(adj, order);
}
