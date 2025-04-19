#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::max;
using std::vector;

int compute_min_refills(int dist, int tank, vector<int> &stops)
{
    stops.push_back(dist);
    int navigated = 0;
    int i = -1;
    const int fullTank = tank;
    int ctr = 0;
    while (++i < stops.size())
    {
        if ((stops[i] - navigated) <= tank)
        {
            tank -= (stops[i] - navigated);
            navigated = stops[i];
            continue;
        }
        if ((stops[i] - navigated) > fullTank)
        {
            return -1;
        }
        tank = fullTank - (stops[i] - navigated);
        navigated = stops[i];
        ctr++;
    }

    return ctr;
}

int main()
{
    int d = 0;
    cin >> d;
    int m = 0;
    cin >> m;
    int n = 0;
    cin >> n;

    vector<int> stops(n);
    for (size_t i = 0; i < n; ++i)
        cin >> stops.at(i);

    cout << compute_min_refills(d, m, stops) << "\n";

    return 0;
}
