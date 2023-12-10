; next_branch(tree, partialSum) =   tree[2...] if (partialSum - 1 + tree[1]) == 0
;                                   next_branch(tree[2...], (partialSum - 1 + tree[1])) otherwise
(defun next_branch(tree &optional (partialSum 0))
    (setq partialSum (+ (- partialSum 1) (car (cdr tree))))
    (if (equal partialSum 0)
        (return-from next_branch (cdr (cdr tree)))
        (next_branch (cdr (cdr tree)) partialSum)
    )
)

; tree_level(tree, value, currentLevel) = nil if tree == nil
;                                       = currentLevel if tree[0] == value
;                                       = nil if tree[1] == 0 and nothing above is true
;                                       = tree_level(tree[2...], value, currentLevel + 1) if tree[1] == 1
;                                       = tree_level(tree[2...], value, currentLevel + 1) or tree_level(next_branch(tree), value, currentLevel + 1) if tree[1] == 2
; NOTE: this assumes the elements of the trees are different.
(defun tree_level(tree value &optional (currentLevel 0))
    (if (equal tree nil)
        (return-from tree_level nil)
    )
    (if (equal (car tree) value)
        (return-from tree_level currentLevel)
    )
    (let ((currentChildren (car (cdr tree))))
        (if (> currentChildren 0)
            (let ((result (tree_level (cdr (cdr tree)) value (+ currentLevel 1))))
                (if (> currentChildren 1)
                    (return-from tree_level (or result (tree_level (next_branch tree) value (+ currentLevel 1))))
                    (return-from tree_level result)
                )
            )
        )
    )
)

(let ((tree '("A" 2 "B" 0 "C" 2 "D" 0 "E" 1 "F" 0)))
    (format t "The current tree is: ~A" tree)
    (terpri)
    (format t "The level of A is: ~A" (tree_level tree "A"))
    (terpri)
    (format t "The level of B is: ~A" (tree_level tree "B"))
    (terpri)
    (format t "The level of C is: ~A" (tree_level tree "C"))
    (terpri)
    (format t "The level of D is: ~A" (tree_level tree "D"))
    (terpri)
    (format t "The level of E is: ~A" (tree_level tree "E"))
    (terpri)
    (format t "The level of F is: ~A" (tree_level tree "F"))
    (terpri)
    (format t "The level of G is: ~A" (tree_level tree "G"))
    (terpri)
)
