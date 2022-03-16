/**
 * Author: Benjamin Qi
 * Date: 2021-10-07
 * License: CC0
 * Source: https://github.com/bqi343/USACO/blob/master/Implementations/content/graphs%20(12)/Flows%20(12.3)/MCMF.h
 * Description: Min-cost max-flow, assumes no negative cycles.
 *  If costs can be negative, call setpi before maxflow.
 *  To get flow through original edges, assign ID's during \texttt{addEdge}.
 * Status: Tested on kattis:mincostmaxflow, stress-tested against another implementation
 * Time: Ignoring setpi, $O(FM\log M)$ if caps are integers and $F$ is max flow.
 */

struct MCMF {
  using F = ll; using C = ll; using T = pair<C, int>;
  const C inf = numeric_limits<C>::max();
  struct Edge { int to, rev; F flo, cap; C cost; };
  int N; vector<C> pi, dist; vector<pii> pre; vector<vector<Edge>> adj;
  MCMF(int N) : N(N), pi(N), dist(N), pre(N), adj(N) {}
  void addEdge(int u, int v, F cap, C cost) {
    adj[u].pb({v, sz(adj[v]), 0, cap, cost});
    adj[v].pb({u, sz(adj[u]) - 1, 0, 0, -cost});
  }
  bool path(int s, int t) {
    dist.assign(N, inf);
    priority_queue<T, vector<T>, greater<T>> q;
    q.push({dist[s] = 0, s});
    while (!q.empty()) {
      C nd; T x = q.top(); q.pop();
      if (x.first > dist[x.second]) continue;
      for (auto& e : adj[x.second]) {
        if (e.flo < e.cap && dist[e.to] > (nd = x.first + e.cost + pi[x.second] - pi[e.to]))
          pre[e.to] = {x.second, e.rev}, q.push({dist[e.to] = nd, e.to});
      }
    }
    return dist[t] != inf;
  }
  pair<F, C> maxflow(int s, int t) {
    F totFlow = 0; C totCost = 0;
    while (path(s, t)) {
      rep(i,0,N) pi[i] += dist[i];
      F df = numeric_limits<F>::max();
      for (int x = t; x != s; x = pre[x].first) {
        Edge& e = adj[pre[x].first][adj[x][pre[x].second].rev];
        df = min(df, e.cap - e.flo);
      }
      totFlow += df; totCost += (pi[t] - pi[s]) * df;
      for (int x = t; x != s; x = pre[x].first) {
        Edge& e = adj[x][pre[x].second]; e.flo -= df;
        adj[pre[x].first][e.rev].flo += df;
      }
    }
    return {totFlow, totCost};
  }
  // If some costs can be negative, call this before maxflow:
  bool setpi(int s) { // (otherwise, leave this out)
    fill(all(pi), inf); pi[s] = 0;
    int it = N, ch = 1; C v;
    while (ch-- && it--) rep(i,0,N) if (pi[i] != inf)
      for (auto e : adj[i])
        if (e.cap && (v = pi[i] + e.cost) < pi[e.to])
          pi[e.to] = v, ch = 1;
    return (it >= 0); // negative cost cycle
  }
};
