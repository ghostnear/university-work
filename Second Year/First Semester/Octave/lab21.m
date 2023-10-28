pkg load statistics;
clear all;
clc;
clf;
n=3;
p=0.5;
k=0:n;
print("a)")
pf=binopdf(k,n,p);
[k;pf]
pf=binocdf(k,n,p);
[k;pf]

binopdf(0, n, p)

1 - binopdf(1, n, p)

binocdf(2, n, p)

binocdf(2, n, p) - binopdf(2, n, p)

1 - binocdf(1, n, p) + binopdf(1, n, p)

1 - binocdf(1, n, p)

