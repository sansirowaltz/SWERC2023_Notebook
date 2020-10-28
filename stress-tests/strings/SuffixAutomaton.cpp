#include "../utilities/template.h"

#include "../../content/strings/MinRotation.h"
#include "../../content/strings/SuffixAutomaton.h"

struct Automaton {
  const static int N = 1e6 + 666;
  struct Node {
    int len, link;
    int next[33];
  } nodes[N * 2];
  int sz, last;
  vector<pii> order;
  Automaton() {
    sz = last = 0;
    nodes[0].len = 0;
    nodes[0].link = -1;
    memset(nodes[0].next, 0, sizeof(nodes[0].next));
    ++sz;
  }
  void extend(int c) {
    int cur = sz++, p;
    nodes[cur].len = nodes[last].len + 1;
    memset(nodes[cur].next, 0, sizeof(nodes[cur].next));
    order.emb(nodes[cur].len, cur);
    for(p = last; p != -1 && !nodes[p].next[c]; p = nodes[p].link)
      nodes[p].next[c] = cur;
    if (p == -1) nodes[cur].link = 0;
    else {
      int q = nodes[p].next[c];
      if (nodes[p].len + 1 == nodes[q].len) nodes[cur].link = q;
      else {
        int clone = sz++;
        nodes[clone].len = nodes[p].len + 1;
        nodes[clone].link = nodes[q].link;
        memcpy(nodes[clone].next, nodes[q].next, sizeof(nodes[q].next));
        order.emb(nodes[clone].len, clone);
        for(; p != -1 && nodes[p].next[c] == q; p = nodes[p].link)
          nodes[p].next[c] = clone;
        nodes[q].link = nodes[cur].link = clone;
      }
    }
    last = cur;
  }
};

int minRotation(string s) {
	int a=0, N=sz(s); s += s;
	rep(b,0,N) rep(k,0,N) {
		if (a+k == b || s[a+k] < s[b+k]) {b += max(0, k-1); break;}
		if (s[a+k] > s[b+k]) { a = b; break; }
	}
	return a;
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
  cout << "Tests passed!" << endl;
}
