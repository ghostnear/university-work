%
% 3.
% a. Merge two sorted lists with removing the double values.
% b. For a heterogeneous list, formed from integer numbers and list of numbers, merge all sublists with removing the double values.
% [1, [2, 3], 4, 5, [1, 4, 6], 3, [1, 3, 7, 9, 10], 5, [1, 1, 11], 8] => [1, 2, 3, 4, 6, 7, 9, 10, 11].
%

% Auxiliary predicate that checks if the element is part of a list.
% check_existance(E - element, L - list)
% flow model: (i, i)
% check_existance(E, L) = false, L is []
%                       = check_existance(E, T), H is not E
%                       = true, H is E
check_existance(_, []) :- fail.
check_existance(E, [H|T]) :-
  H =\= E, !,
  check_existance(E, T).
check_existance(E, [E|_]).

% Auxiliary predicate that removes duplicates.
% remove_duplicates(S - source, R - result)
% flow model: (i, io)
% remove_duplicates(S) =  [], S is []
%                         remove_duplicates(T, R), H is in T
%                         [H | remove_duplicates(T, R)], H is not in T
remove_duplicates([], []).
remove_duplicates([H|T], R) :-
  check_existance(H, T),
  remove_duplicates(T, R).
remove_duplicates([H|T], [H|R]) :-
  remove_duplicates(T, R).

% mergeList(FS - first source, SS - second source, R - result)
% flow model: (i, i, io)
% mergeList(FS, SS) = FS, SS is []
%                   = SS, FS is []
%                   = [HF | mergeList(TF, SS)], HF < HS
%                   = [HS | mergeList(FS, TS)], HS < HF
%                   = [HF | mergeList(TF, TS)], HF == HS
mergeList(L, [], L).                      % When any of the lists are empty, it's done.
mergeList([], L, L).
mergeList([HF|TF], [HS|TS], [HF|R]) :-    % On first smaller, add it to the list.
  HF < HS,
  mergeList(TF, [HS|TS], R).
mergeList([HF|TF], [HS|TS], [HS|R]) :-    % On second smaller, add it to the list. 
  HF > HS,
  mergeList([HF|TF], TS, R).
mergeList([HF|TF], [HS|TS], [HF|R]) :-    % On equal elements, remove both and keep only one.
  HF == HS,
  mergeList(TF, TS, R).

% mergeWithoutDuplicates(FS - first source, SS - second source, R - result)
% flow model: (i, i, io)
% Alias function.
merge_without_duplicates(FS, SS, R) :-
  mergeList(FS, SS, Merged),
  remove_duplicates(Merged, R).

% flattened_merge(S - Source, R - result)
% flow model: (i, io)
% flattened_merge(S) = []. S is [].
%                      merge_without_duplicates(flattened_merge(SH), flattened_merge(ST)), SH is list.
%                      flattened_merge(ST), SH is number.
flattened_merge([], []).
flattened_merge([SH|ST], R) :-       % Head is a list, merge it normally.
  is_list(SH), !,
  flattened_merge(ST, FlattenedST),
  merge_without_duplicates(SH, FlattenedST, R).
flattened_merge([_|ST], R) :-       % Head is a number, we don't really care about that.
  flattened_merge(ST, R).
