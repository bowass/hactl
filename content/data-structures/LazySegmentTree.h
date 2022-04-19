/**
 * Author: Simon Lindholm
 * Date: 2016-10-08
 * License: CC0
 * Source: me
 * Description: Segment tree with ability to add or set values of large intervals, and compute max of intervals.
 * Can be changed to other things e.g. min, max, sum, xor, gcd, lcm (by replacing "max" function, replacing "val" neutral value, and sometimes other things specified).
 * Use with a bump allocator for better performance, and SmallPtr or implicit indices to save memory.
 * Time: O(\log N) query, O(N) non-sparse build
 * Usage: Node* tr = new Node(v, 0, sz(v));
 * Status: stress-tested a bit
 */
#pragma once

#include "../various/BumpAllocator.h"

const int inf = 1e9;
struct Node {
	Node *l = 0, *r = 0;
	int lo, hi, mset = inf, madd = 0;
	int val = -inf; // min: inf, max: -inf, sum: 0 or [init_value * (hi - lo) -> in constructor], gcd: 1 (init_value), lcm: 1 (init_value)
	Node(int lo,int hi):lo(lo),hi(hi){} // sparse segment tree (use for large intervals of default value "val")
	Node(vi& v, int lo, int hi) : lo(lo), hi(hi) {
		// build segment tree from v - [lo, hi)
		if (lo + 1 < hi) {
			int mid = lo + (hi - lo)/2;
			l = new Node(v, lo, mid); r = new Node(v, mid, hi);
			val = max(l->val, r->val);
		}
		else val = v[lo];
	}
	int query(int L, int R) { // [L, R)
		if (R <= lo || hi <= L) return -inf; // CHANGE THIS (out of range)
		if (L <= lo && hi <= R) return val;
		push();
		return max(l->query(L, R), r->query(L, R));
	}
	void set(int L, int R, int x) { // [L, R)
		if (R <= lo || hi <= L) return;
		if (L <= lo && hi <= R) {
			// CHANGE THIS (update covers node)
			mset = x;
			val = x; // e.g. for sum: x * (hi - lo), for xor: x * ((hi - lo) & 1)
			madd = 0;
		}
		else {
			push(), l->set(L, R, x), r->set(L, R, x);
			val = max(l->val, r->val);
		}
	}
	void add(int L, int R, int x) { // [L, R)
		if (R <= lo || hi <= L) return;
		if (L <= lo && hi <= R) {
			// CHANGE THIS (update covers node)
			if (mset != inf) mset += x;
			else madd += x;
			val += x; // e.g. for sum: x * (hi - lo), xor/gcd/lcm too hard
		}
		else {
			push(), l->add(L, R, x), r->add(L, R, x);
			val = max(l->val, r->val);
		}
	}
	void push() {
		if (!l) {
			int mid = lo + (hi - lo)/2;
			l = new Node(lo, mid); r = new Node(mid, hi);
		}
		if (mset != inf)
			l->set(lo,hi,mset), r->set(lo,hi,mset), mset = inf;
		else if (madd)
			l->add(lo,hi,madd), r->add(lo,hi,madd), madd = 0;
	}
};
