% Given a heterogenous list made of atoms and lists of numbers,
% remove all increasing sequences of numbers from the sublists of the list.
% ex: [[1,2,4,4,7,9,0,1,1], 3, [], 24, a, [12, 4], [3, 5], b]
%       => [[1], 3, [], 24, a, [12, 4], [], b]

% list_remove_increasing(L - list, R - result)
% flow model: (i, o)
% list_remove_increasing(L1...LN)   =   L1  if N = 1 
%                                   =   []  if N = 2 and L1 < L2 or L is empty
%                                   =   list_remove_increasing(L2...LN) if L1 < L2 < L3
%                                   =   list_remove_increasing(L3...LN) if L1 < L2 >= L3
%                                   =   L1 + list_remove_increasing(L2...LN) otherwise
list_remove_increasing([], []).
list_remove_increasing([H], [H]).
list_remove_increasing([H1, H2], []) :-
    H1 < H2.
list_remove_increasing([H1, H2, H3 | T], R) :-
    H1 < H2,
    H2 < H3,
    list_remove_increasing([H2, H3 | T], R).
list_remove_increasing([H1, H2, H3 | T], R) :-
    H1 < H2,
    H2 >= H3,
    list_remove_increasing([H3 | T], R).
list_remove_increasing([H1, H2 | T], [H1 | R]) :-
    H1 >= H2,
    list_remove_increasing([H2 | T], R).

% list_process(L - list, R - result)
% flow model: (i, o)
% list_process(L1...LN)     =   []  if L is empty
%                           =   L1 + list_process(L2...LN) if L1 is not list
%                           =   list_remove_increasing(L1) + list_process(L2...LN) if L1 is list
list_process([], []).
list_process([H|T], [HR | R]) :-
    is_list(H), !,
    list_remove_increasing(H, HR),
    list_process(T, R).
list_process([H|T], [H | R]) :-
    list_process(T, R).