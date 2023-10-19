ll catalan(ll a) { return f[a<<1] * ni[a+1] %p * ni[a] %p; }
ll catalan(ll a) { return C(2*a,a) - C(2*a,a-1); }
ll catalan(ll a) { if(!a) return 1; ll res = 0; for(int i=0;i<=a-1;i++) res += catalan(i) * catalan(a-1-i); return res; }
