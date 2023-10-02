/**
 * Author: Alon Krymgand
 * Date: 2023-10-02
 * Source: Haifa's Algorithm Competition Template Library
 * Description: Min-cost max-flow. Duplicated edges allowed, negative cycles not
 * supported. To obtain the actual flow, look at positive values only.
 * $O(F * E \log V)$, and $O(VE + F * E \log V)$ if contains negative edges.
 * Status: Tested.
 * Time: O(MaxF*mlogn), and O(mn+Maxf*mlogn) if contains negative edges.
 * Check max limits before submitting!
 */
#pragma once

const ll inf = 1e18 + 5;

struct MinCostMaxFlow {
  struct edge {
    int to, rev;
    ll cap, cost;
  };
  int n;
  vector<vector<edge>> g;
  vi par, edgeIdx;
  vector<ll> pi;
  MinCostMaxFlow(int n) : n(n), g(n), par(n), edgeIdx(n), pi(n) {}

  bool augment(int s, int t) {
    // Augment using Dijkstra in O(mlogn).
    vector<ll> dist(n, inf);
    vector<bool> inQ(n);
    queue<int> q;
    q.push(s), inQ[s] = true, dist[s] = 0;
    while (!q.empty()) {
      int u = q.front();
      q.pop(), inQ[u] = 0;
      rep(i, 0, sz(g[u])) {
        auto e = g[u][i];
        ll dto = dist[u] - pi[e.to] + pi[u] + e.cost;
        if (e.cap > 0 && dto < dist[e.to]) {
          dist[e.to] = dto;
          par[e.to] = u;
          edgeIdx[e.to] = i;
          if (!inQ[e.to])
            q.push(e.to), inQ[e.to] = true;
        }
      }
    }
    return dist[t] != inf;
  }

  pair<ll, ll> mcmf(int s, int t) {
    ll maxf = 0, minc = 0;
    while (augment(s, t)) {
      ll minf = inf, costsum = 0;
      for (int p = t; p != s; p = par[p]) {
        auto &e = g[par[p]][edgeIdx[p]];
        minf = min(minf, e.cap);
        costsum += e.cost;
      }
      for (int p = t; p != s; p = par[p]) {
        auto &e = g[par[p]][edgeIdx[p]];
        e.cap -= minf;
        g[e.to][e.rev].cap += minf;
      }
      maxf += minf, minc += costsum * minf;
    }
    return {maxf, minc};
  }

  void addEdge(int from, int to, ll cap, ll cost) {
    g[from].push_back({to, sz(g[to]), cap, cost});
    g[to].push_back({from, sz(g[from]) - 1, 0, -cost});
  }

  bool setpi(int s) {
    // call before mcmf, if there are negative costs.
    // Uses Bellman-Ford to compute pi of vertices in O(nm).

    pi.assign(n, inf), pi[s] = 0;
    int it = n, ch = 1;
    ll v;
    while (ch-- && it--) {
      rep(u, 0, n) for (auto &e : g[u]) {
        if (e.cap != 0 && (v = pi[u] + e.cost) < pi[e.to])
          ch = 1, pi[e.to] = v;
      }
    }
    return it >= 0; // true if NO negative cycles found
  }
};
