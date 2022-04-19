/**
 * Author: Tomer & Yanir
 * Date: 2022-04-19
 * License: CC0
 * Source: Folklore
 * Description: Haifa's template.
 */
#pragma once

#pragma region
#include <bits/stdc++.h>
using namespace std;
#define int int64_t
#define all(x) (x).begin(), (x).end()
#define fine(i, s, n) for (int i = s; i <= (n); ++i)
#define fin(i, s, n) for (int i = s; i < (n); ++i)
#define rep fin
#define sz(x) ((int)(x).size())
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)
#define pb push_back
#define eb emplace_back
template<class t> ostream& operator<<(ostream& o, const vector<t>& v)
{ o << '['; fin(i, 0, sz(v) - 1) o << v[i] << ','; return o << v.back() << ']'; }
template<class t, class u> ostream& operator<<(ostream& o, const pair<t, u> v)
{ return o << '{' << v.first << ',' << v.second << '}'; }
void _m(); signed main() { cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit); _m(); }
#define main _m
constexpr bool _debug =
#ifdef DEBUG
true;
#else
false;
#endif
#define dout if (_debug) cout
#define val(x) #x << ": " << (x)
#define print(x) dout << (x) << endl;
#define dbg(x) dout << val(x) << endl
using vi = vector<int>;
using vvi = vector<vi>;
using ii = pair<int, int>;
using pii = ii;
using vii = vector<ii>;
using vvii = vector<vii>;
using ll = long long;
#pragma endregion



void main() {
    
}
