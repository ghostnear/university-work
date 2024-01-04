; list_sum(currentBlock)    = currentBlock if currentBlock is a number
;                           = 0 if currentBlock is an atom
;                           = list_sum(currentBlock[0]) + ... + list_sum(currentBlock[n])
;                               if currentBlock is a list
(DEFUN list_sum(currentBlock)
    (COND
        ((numberp currentBlock) currentBlock)
        ((atom currentBlock) 0)
        (T (APPLY '+ (mapcar #'list_sum currentBlock)))
    )
)

(format t "~A" (list_sum '(1 a 3 2 (4 (5 b 6) 7) (8 9 c 10))))