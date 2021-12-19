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

bool ispar(char c, char d) {
  return c < '0' ? abs(c - d) == 1 : abs(c - d) == 2;
}

bool isopen(char c) {
  return c == '(' or c == '[' or c == '{' or c == '<';
}

int task1(vector<string>& ss) {
  int ans = 0;
  map<char, int> m = {{')', 3}, {']', 57}, {'}', 1197}, {'>', 25137}};
  each(s, ss) {
    stack<char> st;
    for (int i = 0;s[i];i++) {
      if (isopen(s[i])) st.push(s[i]);
      else if (!st.empty() and ispar(s[i], st.top())) {
        st.pop();
      }
      else {
        ans += m[s[i]];
        break;
      }
    }
  }
  return ans;
}

ll task2(vector<string>& ss) {
  vector<ll> ans;
  map<char, int> m = {{'(', 1}, {'[', 2}, {'{', 3}, {'<', 4}};
  each(s, ss) {
    stack<char> st;
    ll score = 0;
    bool ok = true;
    for (int i = 0;s[i];i++) {
      if (isopen(s[i])) st.push(s[i]);
      else if (!st.empty() and ispar(s[i], st.top())) {
        st.pop();
      }
      else {
        ok = false;
        break;
      }
    }
    if (ok) {
      while (!st.empty()) {
        score *= 5;
        score += m[st.top()];
        st.pop();
      }
      ans.push_back(score);
    }
  }
  int n = ans.size();
  sort(iter(ans));
  return ans[n >> 1];
}

int main() {
  ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

  string s;
  vector<string> ss;
  while (cin >> s) ss.push_back(s);
  cout << "Task 1: " << task1(ss) << endl;
  cout << "Task 2: " << task2(ss) << endl;
  return 0;
}

