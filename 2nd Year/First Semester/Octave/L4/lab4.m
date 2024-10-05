clear all;
clc;

pkg load statistics;

% Random number generators lab

% Reminder:
% Binomial - bino
% Normal - norm
% Student - t
% Fisher - f
% x^2 - chi2
% Poisson - poiss

% Use with:
% pdf
% cdf
% inv - inverse (for quantile)
% rnd - random

p = -1;

while p < 0 || p > 1
  p = input("Give the probability of success: ");
end

s = input("How many simulations do you want to make: ");

u = rand(1, s);

x = u < p;

U_x = unique(x);

n_x = hist(x, length(U_x));

p_x = n_x / s;

[U_x;p_x]

