t=var('t')
x=function('x')(t)
y=function('y')(t)

dx=diff(x,t)==-2*y
dy=diff(y,t)==-3*x

solution=desolve_system([dx, dy], [x,y])
show(solution[0].expand())
show(solution[1].expand())