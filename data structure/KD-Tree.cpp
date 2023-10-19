#include <algorithm>
#include <iostream>

using namespace std;
constexpr int max_n     = 2e5 + 5;
constexpr int dimension = 2;
constexpr double lim    = 0.7;

struct Point {
    int pos[dimension], min_val[dimension], max_val[dimension], sz, val;
    int sum, d;
    Point *ls, *rs;
    Point *up() {
        sz  = ls->sz + rs->sz + 1;
        sum = ls->sum + rs->sum + val;
        for (int i = 0; i < dimension; ++i) {
            min_val[i] = min(pos[i], min(ls->min_val[i], rs->min_val[i]));
            max_val[i] = max(pos[i], max(ls->max_val[i], rs->max_val[i]));
        }
        return this;
    }
} pool[max_n], *null = new Point, *pit = pool;

Point *tmp[max_n], **pt;

void init() {
    null->ls = null->rs = null;
    fill(null->min_val, null->min_val + dimension, INT32_MAX);
    fill(null->max_val, null->max_val + dimension, INT32_MIN);
    null->sum = null->val = null->sz = 0;
}

double pow2(double x) { return x * x; }

int max_var(Point **l, Point **r) {
    double var[dimension];
    double ave;
    for (int i = 0; i < dimension; ++i) {
        ave = 0;
        for (auto it = l; it < r; ++it) {
            ave += (*it)->pos[i];
        }
        ave /= (r - l);
        var[i] = 0;
        for (auto it = l; it < r; ++it) {
            var[i] += pow2((*it)->pos[i] - ave);
        }
    }
    return (max_element(var, var + dimension) - var);
}

Point *build(Point **l, Point **r) {
    if (l >= r) return null;
    Point **mid = l + (r - l) / 2;
    int d       = max_var(l, r);
    auto cmp = [d](const Point *a, const Point *b) { return a->pos[d] < b->pos[d]; };
    nth_element(l, mid, r, cmp);
    Point *o = *mid;
    o->d     = d;
    o->ls    = build(l, mid);
    o->rs    = build(mid + 1, r);
    return o->up();
}

inline bool inside(const int o_min[], const int o_max[], const int min_val[], const int max_val[]) {
    for (int i = 0; i < dimension; ++i) {
        if (max_val[i] < o_max[i] || o_min[i] < min_val[i]) return false;
    }
    return true;
}

int query(Point *o, const int min_val[], const int max_val[]) {
    if (o == null) return 0;
    for (int i = 0; i < dimension; ++i) {
        if (o->max_val[i] < min_val[i] || max_val[i] < o->min_val[i]) return 0;
    }
    if (inside(o->min_val, o->max_val, min_val, max_val)) return o->sum;
    return query(o->ls, min_val, max_val) + query(o->rs, min_val, max_val)
           + (inside(o->pos, o->pos, min_val, max_val) ? o->val : 0);
}

void dfs(Point *o) {
    if (o == null) return;
    *pt++ = o;
    dfs(o->ls);
    dfs(o->rs);
}

inline Point *rebuild(Point *o, Point *x) {
    pt = tmp;
    dfs(o);
    *pt++ = x;
    return build(tmp, pt);
}
Point *insert(Point *o, Point *x) {
    if (o == null) return x->up();
    Point *&nxt = (x->pos[o->d] <= o->pos[o->d]) ? o->ls : o->rs;
    if (nxt->sz > o->sz * lim) {
        return rebuild(o, x);
    }
    nxt = insert(nxt, x);
    return o->up();
}

Point *del(Point *o, Point *x) {
    if (o == x) return null;
    Point *&nxt = (x->pos[o->d] <= o->pos[o->d]) ? o->ls : o->rs;
    if (nxt->sz < o->sz * (1 - lim)) {
        return rebuild(o, x);
    }
    nxt = del(nxt, x);
    return o->up();
}

int main() {
    ios::sync_with_stdio(false);
    init();
    int n;
    cin >> n;
    int op, x, y, val, ans = 0;
    int min_val[2], max_val[2];
    Point *rt = null;
    cin >> op;
    while (op != 3) {
        if (op == 1) {
            cin >> x >> y >> val;
            x ^= ans, y ^= ans, val ^= ans;
            pit->pos[0] = x, pit->pos[1] = y;
            pit->val = val;
            pit->ls = pit->rs = null;
            rt                = insert(rt, pit++);
        } else {
            cin >> min_val[0] >> min_val[1] >> max_val[0] >> max_val[1];
            min_val[0] ^= ans, min_val[1] ^= ans;
            max_val[0] ^= ans, max_val[1] ^= ans;
            if (min_val[0] > max_val[0]) swap(min_val[0], max_val[0]);
            if (min_val[1] > max_val[1]) swap(min_val[1], max_val[1]);
            cout << (ans = query(rt, min_val, max_val)) << '\n';
        }
        cin >> op;
    }
    return 0;
}
