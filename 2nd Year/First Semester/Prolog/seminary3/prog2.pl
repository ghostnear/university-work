% Given a list of numbers and sublists of numbers,
% remove the odd numbers from the sublists with
% mountain aspect.
% -> 3+ members, /\ aspect

% list_remove_odd(L - list, R - result)
% flow model: (i, io)
% remove_odd(L, R)  =   []  if N = 0
%                   =   L1 + remove_odd(L2...LN) if L1 % 2 = 0
%                   =   remove_odd(L2...LN) otherwise
list_remove_odd([], []).
list_remove_odd([H|T], [H|R]) :-
    H mod 2 =:= 0, !,
    list_remove_odd(T, R).
list_remove_odd([_|T], R) :-
    list_remove_odd(T, R).

% list_mountain(L - list, F - direction flag)
% flow model: (i, i)
% list_mountain(L, F)   =   True    if N = 1 and F = 1
%                       =   list_mountain(L2...LN, 0) if l1 < l2 and F = 0
%                       =   list_mountain(L2...LN, 1) if l1 > l2 and F = 0
%                       =   list_mountain(L2...LN, 1) if l1 > l2 and F = 1
list_mountain(L) :-         % Alias
    list_mountain(L, 0).
list_mountain([_], 1).
list_mountain([H1, H2 | T], 0) :-
    H1 < H2,
    list_mountain([H2|T], 0).
list_mountain([H1, H2 | T], _) :-
    H1 > H2,
    list_mountain([H2|T], 1).

% list_process(L - list, R - result)
% flow model: (i, io)
% list_process(L1...LN) =   []  if N = 0
%                       =   list_remove_odd(L1) + list_process(L2...LN) if is_list(L1) and list_mountain(L1)
%                       =   L1 + list_process(L2...LN) otherwise
list_process([], []).
list_process([H|T], [HEven | R]) :-
    is_list(H),
    list_mountain(H), !,
    list_process(T, R),
    list_remove_odd(H, HEven).
list_process([H|T], [H | R]) :-
    list_process(T, R).