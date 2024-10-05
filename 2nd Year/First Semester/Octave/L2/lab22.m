pkg load statistics;
clear all;
clc;
clf;
s=input("Give the number of simulations of the experiment: ");
n=3;
hist(sum(rand(n, s) > 0.5))
