; append_to_list(value, list) = list U value
(defun append_to_list(value inputList)
    (cond
        ((null inputList) (list value))
        (t (cons (car inputList) (append_to_list value (cdr inputList))))
    )
)

; merge_lists(list1, list2) = list1 U list2
(defun merge_lists(list1 list2)
    (cond
        ((null list1) list2)
        ((null list2) list1)
        (t (cons (car list1) (merge_lists (cdr list1) list2)))
    )
)

; collect_numbers(list) = nil if list is empty
;                       = list[0] U collect_numbers(list[1...]) if list[0] is a number.
;                       = collect_numbers(list[0]) U collect_numbers(list[1...]) if list[0] is a list.
;                       = collect_numbers(list[1...]) otherwise.
(defun collect_numbers(inputList)
    (cond
        ((null inputList) nil)
        ((numberp (car inputList)) (append_to_list (car inputList) (collect_numbers (cdr inputList))))
        ((listp (car inputList)) (merge_lists (collect_numbers (car inputList)) (collect_numbers (cdr inputList))))
        (t (collect_numbers (cdr inputList)))
    )
)

; is_in(value, list) = true if list[0] == value
;                    = false if list is empty
;                    = is_in(value, list[1..]) otherwise
(defun is_in(value inputList)
    (cond
        ((null inputList) nil)
        ((= (car inputList) value) t)
        (t (is_in value (cdr inputList)))
    )
)

; unique(list)  = nil if list is empty
;               = list[0] U unique(list[1...]) if list[0] is not in unique(list[1...])
;               = unique(list[1...]) otherwise
(defun unique(inputList)
    (cond 
        ((null inputList) nil)
        (t (let ((previousResult (unique (cdr inputList))))
            (cond
                ((not (is_in (car inputList) previousResult)) (append_to_list (car inputList) previousResult))
                (t previousResult)
            )
        ))
    )
)

; numbers_set(inputList) returns the set of numerical atoms from the list.
(defun numbers_set(inputList)
    (unique (collect_numbers inputList))
)

(format t "~A" (numbers_set '(1 F (2 (1 3 E (2 4) 3) E 1) (1 4))))
; (numbers_set '(1 F (2 (1 3 E (2 4) 3) E 1) (1 4)) -> (1 4 2 3)
; Does not really return the results in order but it is what it is.