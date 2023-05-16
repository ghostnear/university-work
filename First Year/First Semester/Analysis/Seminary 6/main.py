import math

def main():
    print("Our chosen function is sin(x). The derivative is cos(x).")
    print("x = 0 => sin(0) = 0, cos(0) = 1")

    for h in [0.5, 0.1, 0.01]:
        aproximate_value = (math.sin(h) - math.sin(0)) /  h
        print(f"Using h = { h } we get the aproximated value of cos(0) as: { aproximate_value }")
        print(f"O(h) is: { 1 - aproximate_value }")
        print(f"O(h) / h is: { (1 - aproximate_value) / h }")
        print("")

    print("We can see that O(h) is dependent on h.")

    for h in [0.5, 0.1, 0.01]:
        aproximate_value = (math.sin(h) - math.sin(-h)) / (2 * h)
        print(f"Using h = { h } we get the aproximated value of cos(0) as: { aproximate_value }")
        print(f"O(h^2) is: { 1 - aproximate_value }")
        print(f"O(h^2) / h^2 is: { (1 - aproximate_value) / (h * h) }")
        print("")

    print("We can see that O(h^2) is dependent on h^2.")

main()