pkg load statistics;
clear all;
clc;
# cla; clf; only if forms, but we won't prob use them.

# Technique times measurements.
X_1 = [46, 37, 39, 48, 47, 44, 35, 31, 44, 37]
n_1 = length(X_1);

X_2 = [35, 33, 31, 35, 34, 30, 27, 32, 31, 31]
n_2 = length(X_2);


# a) At 5% significance level, do the population variances seem to differ?
alpha = 0.05;

rr_lower = finv(alpha / 2, n_1 - 1, n_2 - 1);
rr_upper = finv(1 - alpha / 2, n_1 - 1, n_2 - 1);

[H, P, CI, STATS] = vartest2(X_1, X_2, "alpha", alpha, "tail", "both");

if H == 1
  fprintf("a) Hypothesis is rejected! On average, the population variances are the same.\n\n");
else
  fprintf("a) Hypothesis is approved! On average, the population variances seem to differ.\n\n");
end

fprintf("P-Val: %.2f\n", P);
fprintf("Rejection interval: (-Inf, %.2f) U (%.2f, Inf)\n", rr_lower, rr_upper);
fprintf("Confidence interval: (%.2f, %.2f)\n", CI);
fprintf("Test stats:\n\tTest statistic: %.2f\n\tDegress of freedom: %.2f / %.2f (%.2f)\n", STATS.fstat, STATS.df1, STATS.df2, STATS.df1 / STATS.df2);

fprintf("\n");

# b) Find a 95% confidence interval for the difference of the average assembling times.
conf = 0.95;
alpha = 1 - conf;

# Population variances are the same and unknown in this case.
X_mean_1 = mean(X_1);
X_mean_2 = mean(X_2);

s_1 = std(X_1);
s_2 = std(X_2);
s_p = sqrt(((n_1 - 1) * s_1 * s_1 + (n_2 - 1) * s_2 * s_2) / (n_1 + n_2 - 2));

t = tinv(1 - alpha / 2, n_1 + n_2 - 2);

ulower = X_mean_1 - X_mean_2 - t * sqrt((s_1 * s_1 / n_1) + (s_2 * s_2 / n_2));
uhigh = X_mean_1 - X_mean_2 + t * sqrt((s_1 * s_1 / n_1) + (s_2 * s_2 / n_2));

fprintf("b) A %.2f%% confidence interval for the difference of average assembling times is: (%.2f, %.2f)\n", conf * 100, ulower, uhigh);
fprintf("\n");
fprintf("Mean for the first set: %.2f\n", X_mean_1);
fprintf("Mean for the second set: %.2f\n", X_mean_2);
fprintf("\n");
fprintf("Standard deviation for the first set: %.2f\n", s_1);
fprintf("Standard deviation for the second set: %.2f\n", s_2);
fprintf("\n");
fprintf("Test standard deviation: %.2f\n", s_p);
fprintf("Test quantile: %.2f\n", t);
fprintf("\n");
