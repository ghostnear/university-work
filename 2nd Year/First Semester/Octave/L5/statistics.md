# Statistical Measures

Let X be a charactersistics of a population.
- mean(X) = the average of the characteristic X.

Variance:
- psi^2 = 1/n * sum(1, n, (xi-abs(x))^2)
    - for the entire population
    - in octave: psi^2 = var(x, 1)
- s^2 = 1/(n-1) * sum(1, n, (xi-abs(x))^2)
    - for a sample
    - in octave: s^2 = var(x)

Standard Deviation:
- psi = std(x, 1)
- s = std(x)

Confidence Intervals:
- pdf(X) = f(x, theta) -> theta = unknown parameter ("target parameter")
    - Point estimate:
        - We have a sample of size n: x1, x2, ..., xn
            - theta = theta(x1, x2, ..., xn)
    - Interval estimate:
        - thetalow, thetaupper = ? such that:
            - P(theta in (thetalow, thetaupper)) = 1 - alpha
                - 1 - alpha = confidence level
                    - alpha = significance level
                - (thetalow, thetaupper) = a 100 * (1 - alpha)% confidence interval

Pivot method:
- A pivot is a variable *w* that depends on x1, x2, ..., xn, theta
    - *w* has a known pdf that does not depend on theta
        - P(w of alpha / 2 < w < w of 1 - alpha / 2) = 1 - alpha