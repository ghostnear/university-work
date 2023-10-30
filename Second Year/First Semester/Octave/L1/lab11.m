x = linearspace(0, 3);
y = x .^ 5 / 10;
y1 = x .* sin(x);
y2 = cos(x);

hold on

plot(x, y)
plot(x, y1)
plot(x, y2)

legend("x^5/10", "x*sin(x)", "cos(x)")
title("idk")

hold off
