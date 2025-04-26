#include <iostream>
#include <vector>
#include <functional>
#include <climits>
#include <limits>
#include <queue>

using ll = long long;
typedef std::vector<ll> vec;
using std::queue;
using std::vector;

static const ll INF = std::numeric_limits<int>::max();

struct Edge
{
  int u, v;
  ll w;
};

void shortest_paths(int n, int s, vector<vector<int>> &adj, vector<Edge> &edges, vector<ll> &distance, vector<int> &reachable, vector<int> &shortest)
{
  queue<int> q;
  reachable[s] = 1;
  q.push(s);
  while (!q.empty())
  {
    auto v = q.front();
    q.pop();
    for (auto v_adj : adj[v])
    {
      if (!reachable[v_adj])
      {
        reachable[v_adj] = 1;
        q.push(v_adj);
      }
    }
  }

  distance[s] = 0;
  bool relaxed;
  for (int i = 0; i < n - 1; i++)
  {
    relaxed = false;
    for (auto &edge : edges)
    {
      if (!reachable[edge.u] || !reachable[edge.v])
        continue;
      if (distance[edge.v] > distance[edge.u] + edge.w)
      {
        distance[edge.v] = distance[edge.u] + edge.w;
        relaxed = true;
      }
    }
    if (!relaxed)
      break;
  }

  queue<int> negatives;

  if (relaxed)
  {
    for (auto edge : edges)
    {
      if (!reachable[edge.u] || !reachable[edge.v])
        continue;
      if (distance[edge.v] > distance[edge.u] + edge.w)
      {
        distance[edge.v] = distance[edge.u] + edge.w;
        negatives.push(edge.v);
        negatives.push(edge.u);
      }
    }
  }

  while (!negatives.empty())
  {
    auto v = negatives.front();
    negatives.pop();
    if (shortest[v])
    {
      shortest[v] = 0;
      for (auto adj_v : adj[v])
      {
        negatives.push(adj_v);
      }
    }
  }
}

int main()
{
  int n, m, s;
  std::cin >> n >> m;
  vector<vector<int>> adj(n, vector<int>());
  vector<vector<int>> cost(n, vector<int>());
  vector<Edge> edges(m);
  for (int i = 0; i < m; i++)
  {
    int x, y, w;
    std::cin >> x >> y >> w;
    adj[x - 1].push_back(y - 1);
    cost[x - 1].push_back(w);
    edges[i].u = x - 1;
    edges[i].v = y - 1;
    edges[i].w = w;
  }
  std::cin >> s;
  s--;
  vector<ll> distance(n, INF);
  vector<int> reachable(n, 0);
  vector<int> shortest(n, 1);
  shortest_paths(n, s, adj, edges, distance, reachable, shortest);
  for (int i = 0; i < n; i++)
  {
    if (!reachable[i])
    {
      std::cout << "*\n";
    }
    else if (!shortest[i])
    {
      std::cout << "-\n";
    }
    else
    {
      std::cout << distance[i] << "\n";
    }
  }
}
