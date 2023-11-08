%
% 14.
% Write a program to generate the list of all subsets of sum S with the elements of a list (S - given).
% Eg: [1,2,3,4,5,6,10] and S=10 => [[1,2,3,4], [1,4,5], [2,3,5], [4,6], [10]] (not necessary in this order)
% Command: subset_sum([1, 2, 3, 4, 5, 6, 10], R, 10).
%

% Auxiliary to find a method to write the number as a sum of numbers from the set.
% subset_sum_one(L - list, R - result list, S - sum, PR - partial result)
% flow model: (i, o, i, _)
% subset_sum(S, D) = [] if S = 0 or L = []
subset_sum_one(L, R, S) :-
  subset_sum_one(L, R, S, []).  % Alias
subset_sum_one([], [], _, _) :- fail.
subset_sum_one(_, [], 0, _) :- !.
subset_sum_one([H|T], [H|RT], S, PR):-
  S >= H,
  S1 is S - H,
  subset_sum_one(T, RT, S1, [H|PR]).
subset_sum_one([_|T], R, S, PR):-
  subset_sum_one(T, R, S, PR).

% Final predicate.
% subset_sum(L - list, R - result list, S - sum)
% flow model: (i, o, i)
subset_sum(L, R, S) :-
  findall(RT, subset_sum_one(L, RT, S), R).