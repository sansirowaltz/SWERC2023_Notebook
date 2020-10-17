/**
 * Author: Johan Sannemo
 * License: CC0
 * Description: pi[x] computes the length of the longest prefix of s that ends at x, other than s[0...x] itself (abacaba -> 0010123).
 * Can be used to find all occurrences of a string.
 * Time: O(n)
 * Status: Tested on Kattis, stringmatching
 */
#pragma once

vi pi(const string& s) {
	vi p(sz(s));
	rep(i,1,sz(s)) {
		int g = p[i-1];
		while (g && s[i] != s[g]) g = p[g-1];
		p[i] = g + (s[i] == s[g]);
	}
	return p;
}


void compute_automaton(string s, vector<vi> &aut) {
  int n = s.length();
  vi pi = pi(s);
  aut.assign(n, vi(26));
  for (int i = 0; i < n; ++i) {
    for (int c = 0; c < 26; ++c) {
      if (i > 0 && s[i] != 'a' + c) {
        aut[i][c] = aut[pi[i - 1]][c];
      } else {
        aut[i][c] = i + (s[i] == 'a' + c);
      }
    }
  }
}

vi match(const string& s, const string& pat) {
	vi p = pi(pat + '\0' + s), res;
	rep(i,sz(p)-sz(s),sz(p))
		if (p[i] == sz(pat)) res.push_back(i - 2 * sz(pat));
	return res;
}
