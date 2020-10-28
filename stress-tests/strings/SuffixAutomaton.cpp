#include "../utilities/template.h"

#include "../../content/strings/MinRotation.h"
#include "../../content/strings/SuffixAutomaton.h"

int dfs(Automaton &sa, int cur) {
  int res = 1;
  rep(i,0,26) {
    if (sa.nodes[cur].next[i]) {
      res += dfs(sa, sa.nodes[cur].next[i]);
    }
  }
  return res;
}

int main() {
  srand(8);
  rep(N,5,10000) {
    string s;
    rep(i,0,N) s.push_back(rand() % 26 + 'a');

    Automaton sa;
    for (char &c: s) sa.extend(c - 'a');
    for (char &c: s) sa.extend(c - 'a');
    string smallestShift = "";
    int cur = 0;
    rep(i,0,sz(s)) {
      int let = -1;
      rep(j,0,26) {
        if (sa.nodes[cur].next[j]) {
          let = j;
          break;
        }
      }
      assert(let != -1);
      smallestShift += (char)(let + 'a');
      cur = sa.nodes[cur].next[let];
    }

    rotate(s.begin(), s.begin() + minRotation(s), s.end());
    assert(s == smallestShift);
  }
  rep(N,5,100) {
    string s;
    rep(i,0,N) s.push_back(rand() % 26 + 'a');

    unordered_set<string> st;
    rep(i,0,N) rep(j,i,N) {
      st.insert(s.substr(i, j - i + 1));
    }

    Automaton sa;
    for (char &c: s) sa.extend(c - 'a');

    assert(sz(st) == (dfs(sa, 0) - 1));
  }
  cout << "Tests passed!" << endl;
}
