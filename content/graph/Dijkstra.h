/**
 * Author: chilli
 * Date: 2019-04-26
 * License: CC0
 * Source: https://cp-algorithms.com/graph/dinic.html
 * Description: Dijkstra's algorithm for finding shortest distances to all
 * vertexes from a single source. Works on weighted graphs without negative
 * edges.
 */

#pragma once

void dijkstra(vvii& g, vi& d, int s, int inf) {
    set<ii> heap;
    d = vi(g.size(), inf);
    heap.insert({d[s] = 0, s});
    int dv;
    while (!heap.empty()) {
        auto [du, u] = *heap.begin();
        heap.erase({du, u});  // process u with distance du
        for (auto [w, v] : g[u])
            if ((dv = du + w) < d[v]) {  // process edge that is better
                heap.erase({d[v], v});
                heap.insert({d[v] = dv, v});
            }
    }
}
