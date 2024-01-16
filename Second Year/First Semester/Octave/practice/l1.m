pkg load statistics;
clear all;
clc;
# cla; clf; only if forms, but we won't prob use them.

# Nickel particles in the equipemnt.
X = [3.26, 1.89, 2.42, 2.03, 3.07, 2.95, 1.39, 3.06, 2.46, 3.35, 1.56, 1.79, 1.76, 3.82, 2.42, 2.96]
n = length(X);

conf = 0.95;
alpha = 1 - conf;

fprintf("Confidence: %.2f\nAlpha: %.2f\n", conf, alpha);

X_mean = mean(X);

fprintf("Mean: %.2f\n", X_mean);

# s - standard deviation (per sample)                 std
# sigma - standard deviation (per entire population)  std - known
# sigma^2 - variance (per entire population)         var - known
# s^2 - variance (per sample)                        var

s = std(X);

fprintf("Standard deviation: %.2f\n", s);

# a) Find a 95% confidence interval for the average size of the Nickel particles.

t = tinv(1 - alpha / 2, n - 1);

ulower = X_mean - s / sqrt(n) * t;
uhigh = X_mean  + s / sqrt(n) * t;

fprintf("a) The %.2f confidence interval is: (%.2f, %.2f)\n", conf * 100, ulower, uhigh);

# b) At the 1% significance level, on average, do the Nickel particles seem to be smaller than 3?
alpha = 0.01; # significance level
test_mean = 3;

[H, P, CI, STATS] = ttest(X, test_mean, "alpha", alpha, "tail", "right");

# Take any of these (last one is TSTAT in Rejection Region).
if H == 1 && P < alpha && STATS.tstat > tinv(1 - alpha, n - 1)
  fprintf("b) Hypothesis is rejected! On average, the nickel particles seem to be bigger than 3.\n\n");
else
  fprintf("b) Hypothesis is approved! On average, the nickel particles seem to be smaller than 3.\n\n");
end

fprintf("Alpha: %.2f\n", alpha);
fprintf("P-val: %.2f\n", P);
fprintf("Confidence interval: (%.2f, %.2f)\n", CI);
fprintf("Rejection region: (%.2f, INF)\n", tinv(1 - alpha, n - 1));
fprintf("Test stats:\n\tTest statistic: %.2f\n\tDegress of freedom: %.2f\n\tStandard deviation: %.2f\n", STATS.tstat, STATS.df, STATS.sd);

