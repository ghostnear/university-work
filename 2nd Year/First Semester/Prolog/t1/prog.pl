% list_minimum(L - list, R - result)
% flow model: (i, io)
% list_minimum(L, R)    =   L1 if L = [L1]
%                       =   L1 if L1 < list_minimum(LT), L = [L1|LT]
%                       =   list_minimum(LT) otherwise.
list_minimum([L1], L1).
list_minimum([L1 | LT], L1) :-
    list_minimum(LT, RL),
    L1 < RL, !.
list_minimum([_|LT], RL) :-
    list_minimum(LT, RL).

% list_element_indexes(L - list, E - element, R - result, I - index)
% flow model: (i, i, io, i)
% list_element_indexes(L, E, R, I)  =   [] if L = []
%                                   =   I + list_element_indexes(LT, E, R, I + 1) if L1 = E, L = [L1|LT]
%                                   =   list_element_indexes(LT, E, R, I + 1) otherwise
list_element_indexes(L, E, R) :-    % Alias
    list_element_indexes(L, E, R, 1).
list_element_indexes([], _, [], _).
list_element_indexes([L1|LT], L1, [I|R], I) :-
    Inc is I + 1,
    list_element_indexes(LT, L1, R, Inc).
list_element_indexes([_|LT], E, R, I) :-
    Inc is I + 1,
    list_element_indexes(LT, E, R, Inc).

% list_minimum_element_positions(L - list, R - result)
% flow model: (i, io)
% Command for testing: list_minimum_element_positions([10, -14, 12, 13, -14], R).
list_minimum_element_positions(L, R) :-
    list_minimum(L, Mini),
    list_element_indexes(L, Mini, R).
