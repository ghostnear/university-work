% 
% 11.
% a. Write a predicate to substitute an element from a list with another element in the list.
% b. Write a predicate to create the sublist (lm, …, ln) from the list (l1,…, lk).
%

% substitute(L-list, N-first position, M-second position, R-result list)
% flow model: (i, i, i, o)
% substitute(L, N, M, E1, E2) = L, N is M,
%                               [H | substitute(LT, N-1, M-1, E1, E2)], N is not 1,
%                               [H | substitute(LT, 1, M-1, E1, E2)], N is 1 and M is not 1.
%                               [R | LT], M is 1.
substitute(L, N, M, L) :-           % Base case.
  N = M.
substitute(L, N, M, R) :-           % Aliases to make sure N <= M
  N =< M,
  substitute(L, N, M, R, _, _).
substitute(L, N, M, R) :-
  M < N,
  substitute(L, M, N, R, _, _).
substitute([E2|LT], _, 1, [E1|LT], E1, E2) :- !.
substitute([E1|LT], 1, M, [E2|RT], E1, E2) :-
  NewM is M - 1,
  substitute(LT, 0, NewM, RT, E1, E2),!.
substitute([H|LT], N, M, [H|RT], E1, E2) :-
  NewN is N - 1,
  NewM is M - 1,
  substitute(LT, NewN, NewM, RT, E1, E2).

% sublist(L-list, N-first position, M-second position, R-result list)
% flow model: (i, i, i, io)
% sublist(L, N, M) =  [], L is []
%                     [], N is 1, M is 0
%                     sublist(T, N-1, M-1), N > 1
%                     [H | sublist(T, 1, M-1)], N is 1, M >= N
sublist([], _, _, []).
sublist(_, 1, 0, []).
sublist([_ | T], N, M, R) :-    % Not using the head as it gets popped.
  N > 1, N =< M,                % Check that we don't need to add to result.
  sublist(T, N-1, M-1, R).
sublist([H | T], N, M, [H | RT]) :-
  1 is N, N =< M,
  NewM is M-1,
  sublist(T, 1, NewM, RT).
