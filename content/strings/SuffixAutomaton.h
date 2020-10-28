/**
 * Author: hieplpvip
 * Date: 2020-10-17
 * License: own work
 * Source: cp-algorithms
 * Description: Builds suffix automaton for a string.
 * Time: $O(N)$
 * Status: untested
 * Usage: Automaton sa; for(char c : s) sa.extend(c - 'a');
 *  1. Number of distinct substr:
 *     - Find number of different paths --> DFS on SA
 *     - f[u] = 1 + sum( f[v] for v in s[u].next
 *  2. Number of occurrences of a substr:
 *     - Initially, in extend: s[cur].cnt = 1; s[clone].cnt = 0;
 *     - Sort order by len
 *     - for (it: reverse order)
 *         p = nodes[it->second].link;
 *         nodes[p].cnt += nodes[it->second].cnt
 *  3. Find total length of different substrings:
 *     - We have f[u] = number of strings starting from node u
 *     - ans[u] = sum(ans[v] + d[v] for v in next[u])
 *  4. Lexicographically k-th substring
 *     - Based on number of different substring
 *  5. Smallest cyclic shift
 *     - Build SA of S+S, then just follow smallest link
 *  6. Find first occurrence
 *     - firstpos[cur] = len[cur] - 1, firstpos[clone] = firstpos[q]
 */
#pragma once

struct Automaton {
  const static int N = 1e6 + 666;
  struct Node {
    int len, link;
    int next[33];
  } nodes[N * 2];
  int sz, last;
  //vector<pii> order;
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
    //order.emb(nodes[cur].len, cur);
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
        //order.emb(nodes[clone].len, clone);
        for(; p != -1 && nodes[p].next[c] == q; p = nodes[p].link)
          nodes[p].next[c] = clone;
        nodes[q].link = nodes[cur].link = clone;
      }
    }
    last = cur;
  }
};
