clear all;
clc;
clf;

pkg load statistics;

% in normal:
% P(x=0) = pdf(0)
% P(x<=0) = cdf(0)
% P(x<0) = P(x<=0)-P(x=0)

% in continous:
% P(x<0) = P(x<=0)

% normal - norm
% student - t
% chi2 - chi2
% fisher - f
% poisson - poiss

n = input("Input model:\nNormal (N)\nStudent (T)\nFisher (F)\nChi2 (C)\nInput: ", "s");

switch n
  case "N"
    mu = input("Input mu parameter: ");
    sigma = input("Input sigma parameter: ");
    normcdf(0, mu, sigma);
  case "T"
    n = input("Input n parameter: ");
    tcdf(0, n);
  case "F"
    n = input("Input n parameter: ");
    m = input("Input m parameter: ");
    fcdf(0, n, m);
  case "C"
    nu = input("Input ny parameter: ");
    chi2cdf(0, nu);
  otherwise
     fprintf("Unknown input!");
end

fprintf("%f\n", ans);
