% occurences(L-list, E-element, N-no of occurences)
% (i, i, io)
occurences([], _, 0).
occurences([H|T], H, N) :-
  occurences(T, H, NT),
  N is NT + 1.
occurences([H|T], E, N) :-
  H =\= E,
  occurences(T, E, N).

% occurencesCollector(L-list, E-elemnent, C-collector, R-result)
% (i, i, o, io)
occurencesCollector([], _, C, C).
occurencesCollector([H|T], H, C, R) :-
  NewC is C + 1,
  occurencesCollector(T, H, NewC, R).
occurencesCollector([H|T], E, C, R) :-
  H =\= E,
  occurencesCollector(T, E, C, R).

% main for the collector function.
occurencesWrapper(L, E, R) :-
  occurencesCollector(L, E, 0, R).

% removeUnique(L-list, C-copy of list, R-result)
% (i, i, io)
removeUniqueHandler([], _, []).
removeUniqueHandler([H|T], L, R) :-
  occurences(L, H, NOcc),
  NOcc == 1, !,
  removeUniqueHandler(T, L, R).
removeUniqueHandler([H|T], L, [H|R]) :-
  removeUniqueHandler(T, L, R).

removeUnique(L, R) :-
  removeUniqueHandler(L, L, R).


