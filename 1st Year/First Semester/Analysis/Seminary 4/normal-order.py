import math
import matplotlib.pyplot as gfx

def buildLists(length):
    points_x = []
    points_y = []
    sum = 0
    for index in range(1, length + 1):
        points_x.append(index)
        value = 1
        if index % 2 == 0:
            value = -1
        value /= index
        sum += value
        points_y.append(sum)
    return (points_x, points_y)

def main():
    n = 100
    try:
        n = int(input("Give max value for which to plot: "))
    except:
        print("The input should be a number, try again...")
        main()
    (points_x, points_y) = buildLists(n)
    gfx.plot(points_x, points_y)
    gfx.plot([-10, n], [math.log(2), math.log(2)])
    gfx.show()
    pass

main()