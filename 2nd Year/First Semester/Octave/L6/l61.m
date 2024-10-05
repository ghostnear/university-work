pkg load statistics;
clear all;
clc;

premium_x = [22.4, 21.7, 24.5, 23.4, 21.6, 23.3, 22.4, 21.6, 24.8, 20.0];
regular_x = [17.7, 14.8, 19.6, 19.6, 12.1, 14.8, 14.4, 12.6, 14.0, 12.2];

n = length(premium_x);
m = length(regular_x);

# a) sigma1 ^ 2 = sigma2 ^ 2 ??

# case 4: ratio
# theta = sigma1 ^ 2 / sigma2 ^ 2
# H0 : theta == 1
# H1 : theta != 1   -> bilateral test
# model: fischer model (n1-1, n2-1)

alpha = input("What is the significance level?\nInput: ");

ttalpha = finv(alpha / 2, n - 1, m - 1);
ttalpha1 = finv(1 - alpha / 2, n - 1, m - 1);

fprintf("Rejection interval: (-Inf, %f) U (%f, Inf)\n", ttalpha, ttalpha1);

fprintf("Part a)\n");

# [H, P, CI, STATS] = vartest2(X, Y, ALPHA, TAIL)
# X - premium_x, Y - regular_x, alpha = alpha, tail = 0
# STATS:  - fstat = TS0
#         - df1 = n1 - 1
#         - df2 = n2 - 1
[H, P, CI, STATS] = vartest2(premium_x, regular_x, "alpha", alpha, "tail", "both");

if H == 1
   fprintf("\tRejected!\n");
else
   fprintf("\tNot rejected!\n");
end

fprintf("\tP-value: %f\n\tConfidence interval: (%f, %f)\n", P, CI);

fprintf("\tSTATS:\n\t\tfstat: %f\n\t\tdf1: %f\n\t\tdf2: %f\n", STATS.fstat, STATS.df1, STATS.df2);

fprintf("Part b)\n");

# theta = mean1 - mean2;
# H0 = theta = 0
# H1 = theta > 0
# case 3: difference
# if we got at a) equality, we got case 2 of case 3, else case 3 of 3.

# [H, P, CI, STATS] = ttest2(X, Y, ALPHA, TAIL, VARTYPE)
# X - premium_x, Y - regular_x, alpha = alpha, tail = 0, VARTYPE = "equal" or "unequal"
# STATS:  - tstat = TS0
#         - df1 = n1 - 1
#         - df2 = n2 - 1
