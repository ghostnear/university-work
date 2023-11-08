clear all;
clc;
clf;

pkg load statistics;

p = 0
while p < 0.05 || p > 0.95
  p = input("Input p for binomial model: ");
end

for n=1:5:100
  hold on;
  k = 0:n;
  mu = n * p;
  sigma = sqrt(n*p*(1-p));
  % title("n=" + n);
  plot(k, binopdf(k, n, p));
  plot(k, normpdf(k, mu, sigma));
  hold off;
  pause(0.5)
end
