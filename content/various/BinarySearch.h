/**
 * Author: Wikipedia
 * Date: 2022-04-19
 * License: CC0
 * Source: https://en.wikipedia.org/wiki/Binary_search_algorithm
 * Description: Performs binary search. Leftmost returns the leftmost matching index, rightmost returns rightmost matching index. When not found, returns -1 or rank (customizeable).
 * Time: O(\log N)
 */
#pragma once

int bsleftmost(vi& a, int x) {
    int l = 0, r = sz(a); // [l, r)
    while (l < r) {
        int m = (l + r) / 2;
        if (a[m] < x) l = m + 1;
        else r = m;
    }
    // remove to return (num of elements < x):
    if (a[l] != x) return -1;
    return l;
}

int bsrightmost(vi& a, int x) {
    int l = 0, r = sz(a); // [l, r)
    while (l < r) {
        int m = (l + r) / 2;
        if (a[m] > x) r = m;
        else l = m + 1;
    }
    // remove to return ((num of elements < x) - 1):
    if (a[l] != x) return -1; 
    return r - 1;
}
