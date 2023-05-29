t=var('t')
x=function('x')(t)

deq=diff(x,t, 2)+x==t^3

s=desolve(deq, x, ics=[0, 0, 4], ivar=t)

show(s)

plot(s, -20, 20)