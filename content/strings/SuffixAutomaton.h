/**
 * Author: hieplpvip
 * Date: 2020-10-17
 * License: own work
 * Source: cp-algorithms
 * Description: Builds suffix automaton for a string.
 * Time: O(n)
 * Status: untested
 */
#pragma once

struct Automaton {
  const static int N = 2e6 + 666;
  struct Node {
    int len, link;
    int next[33];
  } nodes[N * 2];
  int sz, last;
  Automaton() {
    sz = last = 0;
    nodes[0].len = 0;
    nodes[0].link = -1;
    ++sz;
  }
  void extend(int c) {
    int cur = sz++, p;
    nodes[cur].len = nodes[last].len + 1;
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
        for(; p != -1 && nodes[p].next[c] == q; p = nodes[p].link)
          nodes[p].next[c] = clone;
        nodes[q].link = nodes[cur].link = clone;
      }
    }
    last = cur;
  }
};
