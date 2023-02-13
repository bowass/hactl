/**
 * Author: Tomer & Yanir
 * Date: 2022-04-19
 * License: CC0
 * Source: Folklore
 * Description: Haifa's template.
 */
#pragma once
#include <bits/stdc++.h>
using namespace std;
#ifdef lol
const int dbg = 1;
#else
const int dbg = 0;
#endif
#define int int64_t
#define all(x) (x).begin(), (x).end()
#define fin(i, s, n) for (auto i = s; i < (n); ++i)
#define fine(i, s, n) for (auto i = s; i <= (n); ++i)
#define rep fin
#define fori(n,i) fin(i,0,n)
#define sz(x) int((x).size())
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)
#define pb push_back
#define eb emplace_back
template<class T> ostream& operator<<(ostream& os, vector<T> v) {
	if(dbg) os << '[';
	if(!v.empty()) {
		os << v[0]; fin(i,1,sz(v)) os << (dbg?',':' ') << v[i];
	}
	return os << (dbg?']':'\n');
}
template<class A, class B> ostream& operator<<(ostream& os, pair<A,B> p) {
	return dbg ? (os << '{' << p.x << ',' << p.y << '}') : (os << p.x << ' ' << p.y);
}
#define dout if(dbg) cout
#define val(x) #x << ": " << (x)
#define print(x) dout << (x) << endl
#define dbg(x) dout << val(x) << endl
using vi = vector<int>;
using vvi = vector<vi>;
using ii = pair<int, int>;
using vii = vector<ii>;
using vvii = vector<vii>;
using ld = long double;
#pragma endregion
int32_t main() {
	if(dbg) {
		freopen("ina.txt","r",stdin);
		cout << "using " << 8*sizeof(int) <<"-bit integers." << endl;
	} else cin.tie(0)->sync_with_stdio(0);
	return 0;
}
