#include <iostream>
#include <vector>
using namespace std;

class Solver
{
	string s;
	vector<long long> hashes1;
	vector<long long> hashes2;
	vector<long long> powers1;
	vector<long long> powers2;
	const int m1 = 1000000007;
	const int m2 = 1000000009;
	const int x = 263;

public:
	Solver(string s) : s(s)
	{
		int n = s.size();
		hashes1.resize(n + 1, 0);
		hashes2.resize(n + 1, 0);
		powers1.resize(n + 1, 0);
		powers2.resize(n + 1, 0);

		powers1[0] = 1;
		powers2[0] = 1;
		for (int i = 1; i <= n; i++)
		{
			powers1[i] = (powers1[i - 1] * x) % m1;
			powers2[i] = (powers2[i - 1] * x) % m2;
		}

		for (int i = 0; i < n; i++)
		{
			hashes1[i + 1] = (hashes1[i] * x + s[i]) % m1;
			hashes2[i + 1] = (hashes2[i] * x + s[i]) % m2;
		}
	}

	bool ask(int a, int b, int l)
	{
		long long hash1_a = (hashes1[a + l] - (hashes1[a] * powers1[l]) % m1 + m1) % m1;
		long long hash1_b = (hashes1[b + l] - (hashes1[b] * powers1[l]) % m1 + m1) % m1;

		if (hash1_a != hash1_b)
			return false;

		long long hash2_a = (hashes2[a + l] - (hashes2[a] * powers2[l]) % m2 + m2) % m2;
		long long hash2_b = (hashes2[b + l] - (hashes2[b] * powers2[l]) % m2 + m2) % m2;

		return hash2_a == hash2_b;
	}
};

int main()
{
	ios_base::sync_with_stdio(0), cin.tie(0);

	string s;
	int q;
	cin >> s >> q;
	Solver solver(s);
	for (int i = 0; i < q; i++)
	{
		int a, b, l;
		cin >> a >> b >> l;
		cout << (solver.ask(a, b, l) ? "Yes\n" : "No\n");
	}
}
