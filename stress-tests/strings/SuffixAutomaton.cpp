#include "../utilities/template.h"

#include "../../content/strings/MinRotation.h"
#include "../../content/strings/SuffixAutomaton.h"

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
  cout << "Tests passed!" << endl;
}
