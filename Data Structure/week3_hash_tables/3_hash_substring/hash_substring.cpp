#include <iostream>
#include <string>
#include <vector>

using std::string;
typedef unsigned long long ull;

struct Data
{
    string pattern, text;
};

Data read_input()
{
    Data data;
    std::cin >> data.pattern >> data.text;
    return data;
}

void print_occurrences(const std::vector<int> &output)
{
    for (size_t i = 0; i < output.size(); ++i)
        std::cout << output[i] << " ";
    std::cout << "\n";
}

size_t hash_func(const string &s)
{
    static const size_t multiplier = 263;
    static const size_t prime = 1000000007;
    unsigned long long hash = 0;
    for (int i = static_cast<int>(s.size()) - 1; i >= 0; --i)
        hash = (hash * multiplier + s[i]) % prime;
    return hash % prime;
}

std::vector<int> precompute_hashes(const string &text, const string &pattern)
{
    static const size_t multiplier = 263;
    static const size_t prime = 1000000007;

    int pLength = pattern.size();
    int tLength = text.size();
    int windowCount = tLength - pLength + 1;

    std::vector<int> hashes(windowCount);

    long long h_pow = 1;
    for (int i = 0; i < pLength; ++i)
        h_pow = (h_pow * multiplier) % prime;

    string lastWindow = text.substr(windowCount - 1, pLength);
    hashes[windowCount - 1] = hash_func(lastWindow);

    for (int i = windowCount - 2; i >= 0; --i)
    {
        long long val = multiplier * hashes[i + 1];
        val = (val + text[i]) % prime;
        long long to_subtract = (text[i + pLength] * h_pow) % prime;
        hashes[i] = (val - to_subtract + prime) % prime;
    }

    return hashes;
}

std::vector<int> get_occurrences(const Data &input)
{
    const string &pattern = input.pattern, &text = input.text;

    if (pattern.size() > text.size())
        return {};

    auto hashes = precompute_hashes(text, pattern);
    auto pattern_hash = hash_func(pattern);

    std::vector<int> ans;
    for (size_t i = 0; i + pattern.size() <= text.size(); ++i)
    {
        if (hashes[i] == pattern_hash)
        {
            if (text.substr(i, pattern.size()) == pattern)
                ans.push_back(i);
        }
    }
    return ans;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    print_occurrences(get_occurrences(read_input()));
    return 0;
}