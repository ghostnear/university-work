pkg load statistics;

clear all;
clc;

premium_x = [22.4, 21.7, 24.5, 23.4, 21.6, 23.3, 22.4, 21.6, 24.8, 20.0];
regular_x = [17.7, 14.8, 19.6, 19.6, 12.1, 14.8, 14.4, 12.6, 14.0, 12.2];

conf_level = input("Input a confidence level: ");
sign_level = 1 - conf_level;

premium_n = length(premium_x);
regular_n = length(regular_x);

premium_m = mean(premium_x);
regular_m = mean(regular_x);

premium_s = var(premium_x);
regular_s = var(regular_x);

sp = sqrt(((premium_n - 1) * premium_s + (regular_n - 1) * regular_s) / (premium_n + regular_n - 2));

lower = premium_m - regular_m - norminv(1 - sign_level / 2) * sp * sqrt(1 / premium_n + 1 / regular_n);
upper = premium_m - regular_m + norminv(1 - sign_level / 2) * sp * sqrt(1 / premium_n + 1 / regular_n);

fprintf("a) The %2.0f%%  confidence interval is (%5.3f, %5.3f).\n", conf_level * 100, lower, upper);
