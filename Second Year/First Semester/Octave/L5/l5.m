pkg load statistics;

clear all;
clc;

x = [7, 7, 4, 5, 9, 9, 4, 12, 8, 1, 8, 7, 3, 13, 2, 1, 17, 7, 12, 5, 6, 2, 1, 13, 14, 10, 2, 4, 9, 11, 3, 5, 12, 6, 10, 7];
n = length(x);

sigma = 5;
conf_level = input("Input a confidence level: ");
sign_level = 1 - conf_level;

x_bar = mean(x);

tl = x_bar - sigma / sqrt(n) * norminv(1 - sign_level / 2);
tu = x_bar - sigma / sqrt(n) * norminv(sign_level / 2);

fprintf("a) The %2.0f%% confidence interval is (%5.3f, %5.3f).\n", conf_level * 100, tl, tu);

s = std(x);

tl = x_bar - tinv(1 - sign_level / 2, n - 1) * s / sqrt(n);
tu = x_bar - tinv(sign_level / 2, n - 1) * s / sqrt(n);

fprintf("b) The %2.0f%% confidence interval is (%5.3f, %5.3f).\n", conf_level * 100, tl, tu);

s = var(x);

tl = (n - 1) * s / chi2inv(1 - sign_level / 2, n - 1);
tu = (n - 1) * s / chi2inv(sign_level / 2, n - 1);

fprintf("c) The %2.0f%% confidence interval is (%5.3f, %5.3f).\n", conf_level * 100, tl, tu);

