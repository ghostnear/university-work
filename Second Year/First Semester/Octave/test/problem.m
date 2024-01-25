pkg load statistics;
clear all;
clc;

Steel = [4.6, 0.7, 4.2, 1.9, 4.8, 6.1, 4.7, 5.5, 5.4]
Glass = [2.5, 1.3, 2.0, 1.8, 2.7, 3.2, 3.0, 3.5, 3.4]

Steel_n = length(Steel);
Glass_n = length(Glass);

# a) At 1% significance level, do the population variances seem to differ?
alpha = 0.01;

fprintf("a)\n");
fprintf("The null hypothesis is if the variance ratio is 1.\n");
fprintf("The alt. hypothesis is if the variance ratio is not 1.\n");
fprintf("That means a two tailed variance test is used.\n");

rr_lower = finv(alpha / 2, Steel_n - 1, Glass_n - 1);
rr_upper = finv(1 - alpha / 2, Steel_n - 1, Glass_n - 1);

[H, P, CI, STATS] = vartest2(Steel, Glass, "alpha", alpha, "tail", "both");

if H == 1
  fprintf("Null hypothesis is rejected! On average, the population variances seem to differ.\n\n");
else
  fprintf("Null hypothesis is approved! On average, the population variances seem to be the same.\n\n");
end

fprintf("P-Val: %.2f\n", P);
fprintf("Rejection region: (-Inf, %.2f) U (%.2f, Inf)\n", rr_lower, rr_upper);
fprintf("Confidence interval: (%.2f, %.2f)\n", CI);
fprintf("Test stats:\n\tTest statistic: %.2f\n\tDegress of freedom: %.2f / %.2f (%.2f)\n", STATS.fstat, STATS.df1, STATS.df2, STATS.df1 / STATS.df2);

# b) Find a 99% confidence interval for the difference of the average heat losses.
conf = 0.99;
alpha = 1 - conf;

Steel_Mean = mean(Steel);
Glass_Mean = mean(Glass);

fprintf("\nb)\n");
fprintf("The variances seem to be the same and they are unknown.\n");

Steel_std = std(Steel);
Glass_std = std(Glass);

sp = sqrt(((Steel_n - 1) * Steel_std * Steel_std + (Glass_n - 1) * Glass_std * Glass_std) / (Steel_n + Glass_n - 2));
t = tinv(1 - alpha / 2, Steel_n + Glass_n - 2);

fprintf("sp = %.2f\n", sp);
fprintf("t = %.2f\n", t);

u_lower = Steel_Mean - Glass_Mean - t * sp * sqrt(1 / Steel_n + 1 / Glass_n);
u_higher = Steel_Mean - Glass_Mean + t * sp * sqrt(1 / Steel_n + 1 / Glass_n);

fprintf("The %.2f%% confidence interval for the difference of the average heat losses is: (%.2f, %.2f)\n\n", conf * 100, u_lower, u_higher);
