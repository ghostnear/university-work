% mulk(L-list, K-number, R-result list)
% flow model: (i, i, o)
mulk([], _, []).
mulk([H|T], K, R) :-
    mulk(T, K, TR),
    NewHead is H * K,
    R = [NewHead|TR].

% addE(L-list, E-element, R-result list)
% flow model: (i, i, o)
addE([], E, [E]).
addE([H|T], E, [H|TR]) :-
    addE(T, E, TR).

% sum(L-list, R-result list)
% flow model: (i, o), (i, i)
sum([], 0).
sum([H|T], S) :-
    sum(T, ST),
    S is H + ST.

% insert(L-list, E-element, M-position, R-result list)
% flow model: (i, i, i, o)
insert([], E, 1, [E]).
insert([], _, M, []) :- M > 1.
insert([H|T], E, 1, [E, H|T]).
insert([H|T], E, M, [H|TR]) :-
    M1 is M-1,
    insert(T, E, M1, TR).

% del(L-list, E-position, R-result list)
% flow model: (i, i, o)
del([], _, []).
del([_|T], 1, T).
del([H|T], E, [H|TR]) :-
    E1 is E-1,
    del(T, E1, TR).
