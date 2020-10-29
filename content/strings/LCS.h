/**
 * Author: hieplpvip
 * Date: 2020-10-29
 * License: CC0
 * Source: cp-algorithms
 * Description: Find longest common substring
 * Time: $O(N + M)$
 * Status: stress-tested
 */
#pragma once

#include "../strings/SuffixAutomaton.h"

string lcs(const string& s, const string &t) {
  Automaton sa;
  for (const char& c: s) sa.extend(c - 'a');
  int bestpos = 0, best = 0, v = 0, l = 0;
  rep(i,0,sz(t)) {
    int c = t[i] - 'a';
    while (v && !sa.nodes[v].next[c]) {
      v = sa.nodes[v].link;
      l = sa.nodes[v].len;
    }
    if (sa.nodes[v].next[c]) {
      v = sa.nodes[v].next[c];
      ++l;
    }
    if (l > best) bestpos = i, best = l;
  }
  return t.substr(bestpos - best + 1, best);
}
