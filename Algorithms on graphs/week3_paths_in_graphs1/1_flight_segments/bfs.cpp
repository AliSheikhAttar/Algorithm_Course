#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <queue>

using std::vector;
using std::queue;



int distance(vector<vector<int> > &adj, int s, int t) {
    vector<int> distances(adj.size(), INT_MAX);
    std::queue<int> q;
    q.push(s);
    distances[s] = 0;
    while (!q.empty())
    {
        auto v = q.front();
        for (int i = 0; i < adj[v].size(); i++)
        {
            if (distances[adj[v][i]] == INT_MAX)
            {
                q.push(adj[v][i]);
                distances[adj[v][i]] = distances[v] + 1;
                if (adj[v][i] == t)
                    return distances[adj[v][i]];
            }
        }
        q.pop();
  }
  return -1;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }
  int s, t;
  std::cin >> s >> t;
  s--, t--;
  std::cout << distance(adj, s, t);
}
