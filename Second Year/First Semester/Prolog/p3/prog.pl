%
% 14.
% Write a program to generate the list of all subsets of sum S with the elements of a list (S - given).
% Eg: [1,2,3,4,5,6,10] and S=10 => [[1,2,3,4], [1,4,5], [2,3,5], [4,6], [10]] (not necessary in this order)
% Command: subset_sum([1, 2, 3, 4, 5, 6, 10], R, 10).
%

% Auxiliary to find a method to write the number as a sum of numbers from the set.
% subset_sum_one(L - list, R - result list, S - sum)
% flow model: (i, o, i)
% subset_sum_one(S, D)  = [] if S = 0 or L = []
%                       = subset_sum_one(S, T) if S < H
%                       = H + subset_sum_one(S - H, T) if S >= H
subset_sum_one([], [], _) :- fail.
subset_sum_one(_, [], 0) :- !.
subset_sum_one([H|T], [H|RT], S):-
  S >= H,
  S1 is S - H,
  subset_sum_one(T, RT, S1).
subset_sum_one([_|T], R, S):-
  subset_sum_one(T, R, S).

% Final predicate.
% subset_sum(L - list, R - result list, S - sum)
% flow model: (i, o, i)
subset_sum(L, R, S) :-
  findall(RT, subset_sum_one(L, RT, S), R).