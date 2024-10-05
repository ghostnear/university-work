import math
import matplotlib.pyplot as gfx

def buildListsByLearningRate(length, learning_rate):
    points_x = [0]
    points_y = [35]
    for index in range(1, length + 1):
        points_x.append(index)
        points_y.append(points_y[len(points_y) - 1] * (1 - learning_rate * 2))
    return (points_x, points_y)

def buildListsByLearningRateNonConvex(length, learning_rate):
    points_x = [0]
    points_y = [120]
    for index in range(1, length + 1):
        points_x.append(index)
        points_y.append(points_y[len(points_y) - 1] - learning_rate * math.cos(points_y[len(points_y) - 1]))
    return (points_x, points_y)

def main():
    n = 100
    try:
        n = int(input("Give max value for which to plot: "))
    except:
        print("The input should be a number, try again...")
        main()
    # F is x^2
    print("Showing the graph for a small value of the learning rate (0.1).")
    (points_x, points_y) = buildListsByLearningRate(n, 0.1)
    gfx.plot(points_x, points_y)
    gfx.show()
    print("Showing the graph for a bigger value of the learning rate (0.5).")
    (points_x, points_y) = buildListsByLearningRate(n, 0.5)
    gfx.plot(points_x, points_y)
    gfx.show()
    print("Showing the graph for an even bigger value of the learning rate (1.1) leading to divergence.")
    (points_x, points_y) = buildListsByLearningRate(n, 1.1)
    gfx.plot(points_x, points_y)
    gfx.show()
    # F is sin(x)
    print("Showing the graph for a non convex function with a small learning rate (0.1).")
    (points_x, points_y) = buildListsByLearningRateNonConvex(n, 0.1)
    gfx.plot(points_x, points_y)
    gfx.show()

main()