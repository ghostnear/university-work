def an(A, n):
    result = A
    for index in range(1, n):
        result = result * A
    return result

A=matrix([[1, 1/2], [0, 0.6]])
show("A=", A)
show("A^2=", A^2)
show("A^3=", A^3)

A_N=an(A, 100)
show("A^100=", A_N)

A_N=an(A, 10000)
show("A^10000=", A_N)
 
print("We can conclude that A^n tends to the matrix [[1, 1.25], [0, 0]] as n tends to infinity.")

A=matrix([[3, 0], [0, 2]])
print("A's eigenvalues are: ", A.eigenvalues())
