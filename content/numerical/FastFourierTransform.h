/**
 * Author: Nir Adir
 * Date: 2019-01-09
 * License: CC0
 * Description: dft(a) computes $\hat f(k) = \sum_x a[x] \exp(2\pi i \cdot k x /
 N)$ for all $k$. N must be a power of 2. Useful for convolution:
   \texttt{conv(a, b) = c}, where $c[x] = \sum a[i]b[x-i]$.
   For convolution of complex numbers or more than two vectors: FFT, multiply
   pointwise, divide by n, reverse(start+1, end), FFT back.
   Rounding is safe if $(\sum a_i^2 + \sum b_i^2)\log_2{N} < 9\cdot10^{14}$
   (in practice $10^{16}$; higher for random inputs).
   Otherwise, use NTT/FFTMod.
 * Time: O(N \log N) with $N = |A|+|B|$ ($\tilde 1s$ for $N=2^{22}$)
 * Status: somewhat tested
 * Details: An in-depth examination of precision for both FFT and FFTMod can be
 found
 * here
 (https://github.com/simonlindholm/fft-precision/blob/master/fft-precision.md)
 */
#pragma once

struct com {  // works also with c++ complex class but twice slower
    double a, b;
    com(double a = 0, double b = 0) : a(a), b(b) {}
};
com inline operator+(com l, com r) { return com(l.a + r.a, l.b + r.b); }
com inline operator-(com l, com r) { return com(l.a - r.a, l.b - r.b); }
com inline operator*(com l, com r) {
    return com(l.a * r.a - l.b * r.b, l.b * r.a + l.a * r.b);
}
com inline operator/(com c, double b) { return com(c.a / b, c.b / b); }

void inline dft(vector<com> &a, int len, vi &rev, int tp = 1) {
    const double pi = acos(-1);
    for (int i = 0; i <= len; i++)
        if (rev[i] > i) swap(a[i], a[rev[i]]);
    for (int k = 1; k < len; k <<= 1) {
        com w0(cos(2 * pi / (k << 1)), tp * sin(2 * pi / (k << 1)));
        for (int l = 0; l < len; l += (k << 1)) {
            com w(1);
            for (int i = 0; i < k; ++i, w = w * w0) {
                com p0 = a[l + i], p1 = w * a[l + k + i];
                a[l + i] = p0 + p1, a[l + k + i] = p0 - p1;
            }
        }
    }
}
vector<com> inline multiply(vector<com> &p, vector<com> &q) {  // modify p,q!!!
    int len, k = 0;
    for (len = 1; len <= p.size() + q.size(); len <<= 1, ++k)
        ;
    vector<com> res(len * 2, 0);
    p.resize(2 * len, 0);
    q.resize(2 * len, 0);
    res.resize(2 * len, 0);
    vi rev(len + 1, 0);
    for (int i = 0; i <= len; i++)
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (k - 1));
    dft(p, len, rev), dft(q, len, rev);
    for (int i = 0; i <= len; i++) res[i] = p[i] * q[i];
    dft(res, len, rev, -1);
    for (int i = 0; i <= len; i++) res[i] = res[i] / len;
    return res;
}
