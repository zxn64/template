int exgcd(int A,int B) {
    if(!B) { X=1; Y=0; return A; }
    int res = exgcd(B,A%B);
    int t = X; X = Y; Y = t-A/B*Y;
    return res;
}

int d = exgcd(A,B);
cout<<A<<"*"<<X<<" + "<<B<<"*"<<Y<<" = "<<d<<"\n";
