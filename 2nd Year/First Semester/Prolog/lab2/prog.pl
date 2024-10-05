%
% Find all the ways in which a number can be written as a sum of numbers.
% ex: 6 = 1 + 5, 2 + 4, 1 + 2 + 3.
%

% decompose(N - number, C - current number, R - result)
% flow model: (i, i, o)

decompose(0, _, []).
decompose(N, C, [C | T]) :-
  N >= C,
  N1 is N - C,
  C1 is C + 1,
  decompose(N1, C1, T).
decompose(N, C, T) :-
  N > C,
  C1 is C + 1,
  decompose(N, C1, T).

