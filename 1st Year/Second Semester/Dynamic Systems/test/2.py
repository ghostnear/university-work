# Ex. 2

A = matrix([[1, 0.5], [0, 0.6]])

def a_to_n(A, n):
    if(n == 1):
        return A

    if(n % 2 == 0):
        return a_to_n(A, n / 2) * a_to_n(A, n / 2)

    return A * a_to_n(A, (n-1))

show("a) A^2 is:", a_to_n(A, 2))
print("b) A^3 is:", a_to_n(A, 3))
print("c) A^1000 is:", a_to_n(A, 1000))
print("From this we can conclude that A^n tends to [[1, 1.25], [0, 0]] when n tends to infinity.")