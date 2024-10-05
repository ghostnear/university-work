# Ex. 1

# Approximately 100 steps taken, just for the sake of it.
step = 0.005
y=1
x=0
while x <= 0.5:
    x = x + step
    y = y + step * (1 + x^2) * y

print("a) The apporixmate value using the normal method for y(0.5) is: ", y.n(digits=5))

def improved_euler(x0, y0, t, n):
    h = (t - x0) / n
    xx = [x0]
    yy = [y0]
    for step in range(n):
        xx.append((x0 + (step + 1) * h).n())
        m1 = yy[step] * (1 + xx[step]^2)
        yyy = yy[step] + m1 * h
        m2 = yyy * (1 + xx[step + 1]^2)
        yy.append((yy[step] + 1.0 / 2 * (m1 + m2) * h).n())
    return yy[-1]

print("b) The same value using the improved method for y(0.5) is: ", improved_euler(0, 1, 0.5, 100).n(digits=5))

x = var('x')
y = function('y')(x)

dy = diff(y, x) == (1 + x^2) * y

exact_solution = desolve(dy, y, ics=[0, 1], ivar=x)

print("The exact solution is: ", exact_solution(x = 0.5))