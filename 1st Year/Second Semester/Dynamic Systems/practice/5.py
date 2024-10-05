x = var('x')
y = function('y')(x)

y = sin(x) ^ 2 + cos(x) ^ 2

show(y.trig_simplify())

g = function('g')(x)
g = e^x - sin(x)

show(g(x = 0))