; list_append(first second) -> second if first == {}
;                           -> first if second == {}
;                           -> first[0] + list_append(first[1..n] second) otherwise
(defun list_append(first second)
    (cond
        ((null first) second)
        ((null second) first)
        (t (cons (car first) (list_append (cdr first) second)))
    )
)

; a) Write a function to return the difference of two sets.
; set_diff(first second)    ->  {} if first == {}
;                           ->  first[0] == second[0]   ->  set_diff(first[1..n] second[1..m])
;                           ->  first[0] < second[0]    ->  first[0] + set_diff(first[1..n] second)
;                           ->  first[0] > second[0]    ->  first[0] + set_diff(first second[1..m])
(defun set_diff(first second)
    (if (= (length first) 0) (return-from set_diff ()))
    (if (= (car first) (car second))
        (set_diff (cdr first) (cdr second))
        (if (< (car first) (car second))
            (cons (car first) (set_diff (cdr first) second))
            (set_diff first (cdr second))
        )
    )
)

(format t "a) The set difference of ~A and ~A is: ~A" '(1 2 3) '(2 4 6) (set_diff '(1 2 3) '(2 4 6)))
(terpri)

; b) Write a function to reverse a list with its all sublists, on all levels.
; reverse_list(givenList)   ->  {} if givenList == {}
;                           ->  reverse_list(givenList[1..n]) + reverse_list(givenList[0]) if listp(givenList[0])
;                           ->  reverse_list(givenList[1..n]) + givenList[0] otherwise
(defun reverse_list(givenList)
    (if (= (length givenList) 0)
        (return-from reverse_list ())
    )
    (if (listp (car givenList))
        (list_append (reverse_list(cdr givenList)) (list(reverse_list(car givenList))))
        (list_append (reverse_list(cdr givenList)) (list(car givenList)))
    )
)

(format t "b) The reverse of ~A is: ~A" '(1 (2 1 4) 5 3 4) (reverse_list '(1 (2 1 4) 5 3 4)))
(terpri)

; c) Write a function to return the list of the first elements of all list elements of a given list with an odd number of elements at superficial level.
; Example: (1 2 (3 (4 5) (6 7)) 8 (9 10 11)) => (1 3 9).
; weird_fun_collect(givenList)  -> {} if givenList == {}
;                               -> weird_fun(givenList[0]) + weird_fun_collect(givenList[1..n]) if listp(givenList[0])
;                               -> weird_fun_collect(givenList[1..n]) otherwise
(defun weird_fun_collect(givenList)
    (if (= (length givenList) 0)
        (return-from weird_fun_collect ())
    )
    (if (listp (car givenList))
        (list_append (weird_fun (car givenList)) (weird_fun_collect (cdr givenList)))
        (weird_fun_collect (cdr givenList))
    )
)
; weird_fun(givenList)  ->  givenList[0] + weird_fun_collect(givenList) if length(givenList) % 2 == 1
;                       ->  weird_fun_collect(givenList) otherwise
(defun weird_fun(givenList)
    (let ((result ()))  
        (if (= (mod (length givenList) 2) 1)
            (setq result (list(car givenList)))
        )
        (setq result (list_append result (weird_fun_collect givenList)))
        result
    )
)

(format t "c) The resulting list of ~A is: ~A" '(1 2 (3 (4 5) (6 7)) 8 (9 10 11)) (weird_fun '(1 2 (3 (4 5) (6 7)) 8 (9 10 11))))
(terpri)

; d) Write a function to return the sum of all numerical atoms in a list at superficial level.
; sum_all(givenList)    ->  0 if givenList == {}
;                       ->  sum_all(givenList[1..n]) if givenList[0] is not a number
;                       ->  givenList[0] + sum_all(givenList[1..n]) otheriwise
(defun sum_all(givenList)
    (if (= (length givenList) 0)
        (return-from sum_all 0)
    )
    (if (numberp (car givenList))
        (+ (car givenList) (sum_all (cdr givenList)))
        (sum_all (cdr givenList))
    )
)

(format t "d) The sum of numerical atoms of list ~A is: ~A" '(1 2 "a" 3  "b" (1 2 3 4) 4) (sum_all '(1 2 "a" 3  "b" (1 2 3 4) 4)))