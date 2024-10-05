# Ex. 4

t=var('t')
x=function('x')(t)
y=function('y')(t)

dx=diff(x,t) == x
dy=diff(y,t) == x + 2*y

print("a) The general solution is: ")
solution=desolve_system([dx, dy], [x,y])
print(solution[0].expand())
print(solution[1].expand())

print("b) The solution with initial conditions x(0) = 1 and y(0) = 0 is: ")
solution=desolve_system([dx, dy], [x,y], ics=[0,1,0])
print(solution[0].expand())
print(solution[1].expand())

print("c) The planar curve on -0.5, 0.5 is: ")
parametric_plot((solution[0].rhs(), solution[1].rhs()), (t, -0.5, 0.5))
