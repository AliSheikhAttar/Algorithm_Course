#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <algorithm>
#include <deque>
using std::cin;
using std::cout;
using std::max_element;
using std::string;
using std::vector;
using std::deque;

int main()
{
    int n = 0;
    cin >> n;

    vector<int> A(n);
    for (size_t i = 0; i < n; ++i)
        cin >> A.at(i);

    int w = 0;
    cin >> w;
    deque<int> indices;
    if (w > n)
        w = n;
    for (size_t i = 0; i < n; ++i)
    {
        if (indices.front() == i - w)
            indices.pop_front();
        while (!indices.empty() && A[indices.back()] < A[i])
            indices.pop_back();

        indices.push_back(i);

        if (i >= w - 1)
            cout << A[indices.front()] << " ";
    }
    return 0;
}
