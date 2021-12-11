#include <bits/stdc++.h>

using namespace std;

typedef long long          ll;
typedef unsigned long long ull;
typedef vector<int>         vi;
typedef vector<bool>       vb;
typedef map<int, int>      mii;
typedef pair<int, int>     ii;

#define INF                0x3f3f3f3f
#define INFLL              0x3f3f3f3f3f3f3f3f
#define each(x, s)         for(auto& x : s)
#define loop(x)            for(int i = 0;i < x;i++)
#define vloop(v, x)        for(int v = 0;v < x;v++)
#define avg(l, r)          (l + r) >> 1
#define iter(a)            a.begin(), a.end()
#define riter(a)           a.rbegin(), a.rend()
#define endl               "\n"

const ll mod = 1000000007;
const double EPS = 1e-7;
const double PI = acos(-1);

int task1(vector<pair<vector<string>, vector<string>>>& input) {
  int cnt = 0;
  set<int> x = {2, 3, 4, 7};
  for (auto& [_, ds] : input) {
    each(s, ds) {
      cnt += x.count(s.length());
    }
  }
  return cnt;
}

map<string, int> conv = {
  {"abcefg", 0},
  {"cf", 1},
  {"acdeg", 2},
  {"acdfg", 3},
  {"bcdf", 4},
  {"abdfg", 5},
  {"abdefg", 6},
  {"acf", 7},
  {"abcdefg", 8},
  {"abcdfg", 9}
};

bool has(string& s, char c) {
  return s.find(c) != string::npos;
}

int diff(string& s, string& t) {
  int ans = 0;
  for (int i = 0, j = 0;;) {
    if (!s[i] and !t[j]) break;
    else if (!s[i]) ans++, j++;
    else if (!t[j]) ans++, i++;
    else if (s[i] > t[j]) j++, ans++;
    else if (s[i] < t[j]) i++, ans++;
    else i++, j++;
  }
  return ans;
}

map<string, int> crack(vector<string>& a) {
  map<string, int> dec;
  map<char, int> cnt;
  vector<string> five, six;
  each(s, a) {
    sort(iter(s));
    int l = s.length();
    if (l == 2) dec[s] = 1;
    else if (l == 3) dec[s] = 7;
    else if (l == 4) dec[s] = 4;
    else if (l == 7) dec[s] = 8;
    else if (l == 5) five.push_back(s);
    else six.push_back(s);
    each(c, s) cnt[c]++;
  }
  char b, e;
  for (auto& [c, q] : cnt) {
    if (q == 6) b = c;
    else if (q == 4) e = c;
  }
  string s5;
  each(s, five) {
    if (has(s, b)) dec[s] = 5, s5 = s;
    else if (has(s, e)) dec[s] = 2;
    else dec[s] = 3;
  }
  vector<string> zors;
  each(s, six) {
    if (has(s, e)) zors.push_back(s);
    else dec[s] = 9;
  }
  if (diff(zors[0], s5) == 1) swap(zors[0], zors[1]);
  dec[zors[0]] = 0;
  dec[zors[1]] = 6;
  return dec;
}

int task2(vector<pair<vector<string>, vector<string>>>& input) {
  int ans = 0;
  for (auto& [ns, ds] : input) {
    map<string, int> dec = crack(ns);
    int x = 0;
    each(s, ds) {
      sort(iter(s));
      x *= 10;
      x += dec[s];
    }
    ans += x;
  }
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

  vector<pair<vector<string>, vector<string>>> input;
  string line;
  while (getline(cin, line)) {
    vector<string> ns, ds;
    stringstream ss;
    ss << line;
    string s;
    loop(10) ss >> s, ns.push_back(s);
    ss >> s;
    loop(4) ss >> s, ds.push_back(s);
    input.emplace_back(ns, ds);
  }
  cout << "Task 1: " << task1(input) << endl;
  cout << "Task 2: " << task2(input) << endl;
  return 0;
}

