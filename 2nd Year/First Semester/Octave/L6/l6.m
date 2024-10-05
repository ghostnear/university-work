## Confidence intervals review

# P(theta in (thetalow, thetaupper)) = 1 - alpha (confidence level), alpha (significance level)
# (thetalow, thetaupper) was the 100(1-alpha)% confidence interval.
# ex: P(theta in (4, 6)) = 95%

## Hypothesis testing.

# H0 -> null hypothesis -> theta = theta0
# H1 -> alternative hypothesis (research hypothesis)
#   theta < theta0 - left tailed test.
#   theta > theta0 - right tailed test.
#   theta != theta0 - two tailed test / bilateral test.

# Q: do we reject H0?

## Notations:
# TS -> statistical test.
# TS0 -> observed value of the statistical test. (TS(theta = theta0))
# RR -> rejection region (test is if T0 in RR) (in tests.pdf from teacher)   (quantiles -> *inv)
# P-value (if alpha < P then we do not reject H0) (*test (ex. binotest))

pkg load statistics;
clear all;
clc;

X = [7, 7, 4, 5, 9, 9, 4, 12, 8, 1, 8, 7, 3, 13, 2, 1, 17, 7, 12, 5, 6, 2, 1, 13, 14, 10, 2, 4, 9, 11, 3, 5, 12, 6, 10, 7];

alpha = input("What is the significance level?\nInput: ");

fprintf("Part a)\n");

sigma = 5;

# Theta is the mean
theta = mean(X);
theta0 = 8.5;

# H0: does the mean meet the efficiency standard
  # H0 = (mean = 8.5)

# H1: is the efficiency standard met
  # H1 = mean < 8.5   (left tailed test)

# 1. Normal distribution as we have a large size and theta known.
ttalpha = norminv(alpha);
fprintf("\tRejection region is (-Inf, %f)\n", ttalpha);

# [H, P, CI, ZVAL] = ztest(X, M, SIGMA, ALPHA, TAIL) - multiple outputs for this.
# X - data = X, M - theta0 = 8.5, sigma = 5, alpha = alpha, tail = (-1 left, 1 right, 0 bilateral) = -1
# H - 0 - keep H0
#   - 1 - reject H0
# P - the P-value
# CI - confidence interval
# ZVAL - TS0

[H, P, CI, ZVAL] = ztest(X, theta0, sigma, "alpha", alpha, "tail", "left");

if H == 1
   fprintf("\tRejected!\n");
else
   fprintf("\tNot rejected!\n");
end

fprintf("\tP-value: %f\n\tConfidence interval: (%f, %f)\n\tObserved value: %f\n", P, CI, ZVAL);

fprintf("Part b)\n");

# H0: mean = 5.5
# H1: mean > 5.5
  # -> right tailed tests

# we do not know sigma -> student distribution of parameter n - 1
n = length(X);

theta0 = 5.5;

ttalpha = tinv(1 - alpha, n - 1);
fprintf("\tRejection region is (%f, Inf)\n", ttalpha);

# [H, P, CI, STATS] = ttest(X, M, ALPHA, TAIL)
# X - data, M - theta0 = 5.5, alpha = alpha, tail = 1
# STATS .tstat = TS0
#       .df = n - 1
#       .sd = an aproximation of the standard deviation.
[H, P, CI, STATS] = ttest(X, theta0, "alpha", alpha, "tail", "right");

if H == 1
   fprintf("\tRejected!\n");
else
   fprintf("\tNot rejected!\n");
end

fprintf("\tP-value: %f\n\tConfidence interval: (%f, %f)\n", P, CI);

fprintf("\tSTATS:\n\t\tstat: %f\n\t\tdf: %f\n\t\tsd: %f\n", STATS.tstat, STATS.df, STATS.sd);


