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

vi readVec(string&& s) {
  stringstream ss;
  ss << s;
  int x;
  vi v;
  while (ss >> x) v.push_back(x);
  return v;
}

ll solve(ll t, ll d) {
  ll h = t / 2;
  ll l = 0, r = h;
  while (l < r) {
    ll mid = avg(l, r);
    ll dist = mid * (t - mid);
    if (d < dist) r = mid;
    else l = mid + 1;
  }
  return t - 2 * l + 1;
}

int task1(vector<string> input) {
  int ans = 1;
  vi t, d;
  readVec(input[0].substr(input[0].find(' '))).swap(t);
  readVec(input[1].substr(input[1].find(' '))).swap(d);
  for (int i = 0;i < (int)t.size();i++) {
    ans *= solve(t[i], d[i]);
  }
  return ans;
}

ll task2(vector<string> input) {
  vector<ll> vs;
  transform(iter(input), back_inserter(vs), [] (string& s) {
    ll x = 0;
    each(c, s) if (isdigit(c)) {
      x *= 10;
      x += c - '0';
    }
    return x;
  });
  return solve(vs[0], vs[1]);
}

int main() {
  ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

  vector<string> ss(2);
  each(s, ss) getline(cin, s);
  cout << "Task 1: " << task1(ss) << endl;
  cout << "Task 2: " << task2(ss) << endl;
  return 0;
}

