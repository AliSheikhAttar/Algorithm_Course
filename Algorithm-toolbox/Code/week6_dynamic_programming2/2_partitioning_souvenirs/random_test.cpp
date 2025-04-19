#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <numeric>

using namespace std;

// Forward declarations of the functions we want to test
bool optimal_weight(long long W, vector<long long> &w);
int partition3(vector<long long> &A);
int optimal_weight2(int W, vector<long long> &w);
int partition32(vector<long long> &A);

int main()
{
    // Initialize random number generator with a time-based seed
    default_random_engine engine(chrono::system_clock::now().time_since_epoch().count());
    uniform_int_distribution<int> size_dist(3, 10);  // Vector size between 3 and 10
    uniform_int_distribution<int> value_dist(1, 20); // Values between 1 and 20

    int test_count = 0;
    while (true)
    {
        test_count++;

        // Generate random vector
        int size = size_dist(engine);
        vector<long long> w(size);
        for (auto &x : w)
        {
            x = value_dist(engine);
        }

        // Make copies since both functions modify the input
        auto w1 = w;
        auto w2 = w;

        // Test both implementations
        int result1 = partition3(w1);
        int result2 = partition32(w2);

        // Print current test case
        cout << "\rTest #" << test_count << ": {";
        for (size_t i = 0; i < w.size(); ++i)
        {
            cout << w[i];
            if (i < w.size() - 1)
                cout << ", ";
        }
        cout << "}" << flush;

        // Check for mismatch
        if (result1 != result2)
        {
            cout << "\nMismatch found!\n";
            cout << "Input: {";
            for (size_t i = 0; i < w.size(); ++i)
            {
                cout << w[i];
                if (i < w.size() - 1)
                    cout << ", ";
            }
            cout << "}\n";
            cout << "partition3() returned: " << result1 << "\n";
            cout << "partition32() returned: " << result2 << "\n";
            break;
        }
    }

    return 0;
}