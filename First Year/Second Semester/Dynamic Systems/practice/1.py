t=var('t')
y=function('y')(t)

dy=diff(y,t)==1+y^2

exact_solution=desolve(dy, y,ics=[0,1], ivar=t)
show(exact_solution)

step=var('step')
result=[]
t=0
y=1
step=0.1
while(t <= 0.5):
    t = t + step
    y = y + step*(1+y^2)
    result.append((t, y))

show("The approximate value for y(0.5) is: ", y.n(digits=5))

show("The solution of eq=", tan(exact_solution.rhs()))

p = plot(tan(exact_solution.rhs()), -0.5, 0.6)

for i in range(0, len(result) - 1):
    p += line([result[i], result[i + 1]], color='red')

show(p)