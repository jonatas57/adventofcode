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

int outcome(int x, int y) {
  return x == y ? 3 : (y - x + 3) % 3 == 1 ? 6 : 0;
}

int task1(vector<ii>& input) {
  int score = 0;
  for (auto& [x, y] : input) {
    score += y + outcome(x, y);
  }
  return score;
}

int fromOutcome(int x, int o) {
  return (x + o) % 3 + 1;
}

int task2(vector<ii>& input) {
  int score = 0;
  for (auto& [x, o] : input) {
    int y = fromOutcome(x, o);
    score += y + (o - 1) * 3;
  } 
  return score;
}

int main() {
  ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

  vector<ii> input;
  char a, b;
  while (cin >> a >> b) {
    input.emplace_back(a - 'A' + 1, b - 'X' + 1);
  }
  cout << "Task 1: " << task1(input) << endl;
  cout << "Task 2: " << task2(input) << endl;
  return 0;
}
