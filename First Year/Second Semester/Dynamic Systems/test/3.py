# Ex. 3

t=var('t')
x=function('x')(t)

dt=diff(x,t, 2) + x == t^3

solution = desolve(dt, x, ics=[0, 0, -4], ivar=t)

print("The solution of the IVP is: ", solution)

plot(solution, -2, 2)