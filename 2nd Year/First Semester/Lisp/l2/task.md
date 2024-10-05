Write recursive Lisp functions for the following problems (optionally, you may use MAP functions):
    A binary tree is memorised in the following two ways:
        (node no-subtrees list-subtree-1 list-subtree-2 ...)    (1)
        (node (list-subtree-1) (list-subtree-2) ...)            (2)
    As an example, the tree
         A
        / \
       B   C
          / \
          D E

is represented as follows:
    (A 2 B 0 C 2 D 0 E 0) (1)
    (A (B) (C (D) (E))) (2)

# Task 7

Return the level of a node X in a tree of type (1).

The level of the root element is 0