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

int prio(char c) {
  return isupper(c) ? c - 'A' + 27 : c - 'a' + 1;
}

set<char> inter(set<char> s, set<char> t) {
  auto it = s.begin();
  auto it2 = t.begin();
  set<char> ans;
  while (it != s.end() and it2 != t.end()) {
    if (*it == *it2) {
      ans.insert(*it);
      it++;
      it2++;
    }
    else if (*it < *it2) it++;
    else it2++;
  }
  return ans;
}

int task1(vector<string>& ss) {
  int ans = 0;
  each(s, ss) {
    int l = s.length() / 2;
    set<char> c1(s.begin(), s.begin() + l), c2(s.begin() + l, s.end());
    ans += prio(*inter(c1, c2).begin());
  }
  return ans;
}

int task2(vector<string>& ss) {
  int n = ss.size();
  int ans = 0;
  for (int i = 0;i < n;i += 3) {
    ans += prio(*inter(set(iter(ss[i])), inter(set(iter(ss[i + 1])), set(iter(ss[i + 2])))).begin());
  }
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

  vector<string> input;
  string s;
  while (getline(cin, s)) input.push_back(s);
  cout << "Task 1: " << task1(input) << endl;
  cout << "Task 2: " << task2(input) << endl;
  return 0;
}
