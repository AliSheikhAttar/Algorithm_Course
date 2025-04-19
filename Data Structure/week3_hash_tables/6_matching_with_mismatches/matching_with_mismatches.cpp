#include <iostream>
#include <vector>

using namespace std;

// Prefix hash arrays (much smaller)
vector<long long> shashes1, shashes2;
vector<long long> thashes1, thashes2;
vector<long long> powers1, powers2;

const int m1 = 1000000007;
const int m2 = 1000000009;
const int x = 263;

void precompute_hashes(const string &s, const string &t)
{
	int ns = s.size();
	int nt = t.size();
	int max_len = max(ns, nt);

	// Resize to store only prefix hashes
	shashes1.assign(ns + 1, 0);
	shashes2.assign(ns + 1, 0);
	thashes1.assign(nt + 1, 0);
	thashes2.assign(nt + 1, 0);

	// Precompute powers of x
	powers1.assign(max_len + 1, 0);
	powers2.assign(max_len + 1, 0);
	powers1[0] = 1;
	powers2[0] = 1;

	for (int i = 1; i <= max_len; i++)
	{
		powers1[i] = (powers1[i - 1] * x) % m1;
		powers2[i] = (powers2[i - 1] * x) % m2;
	}

	// Compute prefix hashes for string s
	for (int i = 0; i < ns; i++)
	{
		shashes1[i + 1] = (shashes1[i] * x + s[i]) % m1;
		shashes2[i + 1] = (shashes2[i] * x + s[i]) % m2;
	}

	// Compute prefix hashes for string t
	for (int i = 0; i < nt; i++)
	{
		thashes1[i + 1] = (thashes1[i] * x + t[i]) % m1;
		thashes2[i + 1] = (thashes2[i] * x + t[i]) % m2;
	}
}

// Get hash of substring [start, end] (inclusive)
pair<long long, long long> get_hash_pair(int start, int end, bool is_first_string)
{
	if (start > end)
		return {0, 0};

	int length = end - start + 1;

	if (is_first_string)
	{
		long long hash1 = (shashes1[start + length] - (shashes1[start] * powers1[length]) % m1 + m1) % m1;
		long long hash2 = (shashes2[start + length] - (shashes2[start] * powers2[length]) % m2 + m2) % m2;
		return {hash1, hash2};
	}
	else
	{
		long long hash1 = (thashes1[start + length] - (thashes1[start] * powers1[length]) % m1 + m1) % m1;
		long long hash2 = (thashes2[start + length] - (thashes2[start] * powers2[length]) % m2 + m2) % m2;
		return {hash1, hash2};
	}
}

vector<int> solve(int k, const string &t, const string &p)
{
	vector<int> ans;

	if (p.size() == 0 || t.size() == 0 || p.size() > t.size())
		return ans;

	precompute_hashes(p, t);

	for (int i = 0; i + p.size() <= t.size(); i++)
	{
		int mismatches = 0;
		int pos = 0;

		while (mismatches <= k && pos < p.size())
		{
			int low = pos;
			int high = p.size() - 1;
			int mismatch_pos = p.size();

			while (low <= high)
			{
				int mid = (low + high) / 2;

				auto p_hash = get_hash_pair(pos, mid, true);
				auto t_hash = get_hash_pair(i + pos, i + mid, false);

				if (p_hash.first == t_hash.first && p_hash.second == t_hash.second)
					low = mid + 1;
				else
				{
					mismatch_pos = mid;
					high = mid - 1;
				}
			}

			if (mismatch_pos == p.size())
				break;

			mismatches++;
			pos = mismatch_pos + 1;
		}

		if (mismatches <= k)
			ans.push_back(i);
	}

	return ans;
}

int main()
{
	ios_base::sync_with_stdio(false), cin.tie(0);
	int k;
	string t, p;
	while (cin >> k >> t >> p)
	{
		auto a = solve(k, t, p);
		cout << a.size();
		for (int x : a)
			cout << " " << x;
		cout << "\n";
	}
}
