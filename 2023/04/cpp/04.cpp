#include <bits/stdc++.h>

using namespace std;

typedef long long          ll;
typedef vector<int>        vi;
typedef vector<bool>       vb;
typedef pair<int, int>     ii;

const int INF = 0x3f3f3f3f;
const ll  INFLL = 0x3f3f3f3f3f3f3f3fll;

#define each(x, s)  for(auto& x : s)
#define loop(x)     for(int i = 0;i < x;i++)
#define vloop(v, x) for(int v = 0;v < x;v++)
#define iter(a)     a.begin(), a.end()
#define riter(a)    a.rbegin(), a.rend()
#define endl        "\n"
#define avg(l, r)   (l + r) / 2

struct card {
  vi win, num;
  card(string s) {
    stringstream ss;
    ss << s;
    string t;
    ss >> t >> t;
    bool w = true;
    while (ss >> t) {
      if (isdigit(t[0])) {
        int x = stoi(t);
        if (w) win.push_back(x);
        else num.push_back(x);
      }
      else w = false;
    }
    sort(iter(win));
    sort(iter(num));
  }
};

int task1(vector<card> cs) {
  int ans = 0;
  each(c, cs) {
    int p = 0;
    int l = 0, r = 0;
    while (l < (int)c.win.size() and r < (int)c.num.size()) {
      if (c.win[l] < c.num[r]) l++;
      else if (c.win[l] > c.num[r]) r++;
      else {
        l++, r++;
        if (!p) p = 1;
        else p <<= 1;
      }
    }
    ans += p;
  }
  return ans;
}

ll task2(vector<card> cs) {
  ll ans = 0;
  int n = cs.size();
  vector<ll> onda(n);
  onda[0] = 1;
  loop(n) {
    card& c = cs[i];
    if (i) onda[i] += onda[i - 1];
    int p = 0;
    int l = 0, r = 0;
    while (l < (int)c.win.size() and r < (int)c.num.size()) {
      if (c.win[l] < c.num[r]) l++;
      else if (c.win[l] > c.num[r]) r++;
      else {
        l++, r++;
        p++;
      }
    }
    if (i + 1 < n) onda[i + 1] += onda[i];
    if (i + p + 1 < n) onda[i + p + 1] -= onda[i];
    ans += onda[i];
  }
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

  vector<card> cs;
  string s;
  while (getline(cin, s)) cs.emplace_back(s);
  cout << "Task 1: " << task1(cs) << endl;
  cout << "Task 2: " << task2(cs) << endl;
  return 0;
}

