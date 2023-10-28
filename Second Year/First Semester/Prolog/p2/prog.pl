%
% 3.
% a. Merge two sorted lists with removing the double values.
% b. For a heterogeneous list, formed from integer numbers and list of numbers, merge all sublists with removing the double values.
% [1, [2, 3], 4, 5, [1, 4, 6], 3, [1, 3, 7, 9, 10], 5, [1, 1, 11], 8] => [1, 2, 3, 4, 6, 7, 9, 10, 11].
%

% Auxiliary predicate that removes duplicates.
% remove_duplicates(S - source, R - result)
% flow model: (i, io)
remove_duplicates([], []).
remove_duplicates([H|T], R) :-
  member(H, T),
  remove_duplicates(T, R).
remove_duplicates([H|T], [H|R]) :-
  remove_duplicates(T, R).

% merge(FS - first source, SS - second source, R - result)
% flow model: (i, i, io)
merge(L, [], L).                      % When any of the lists are empty, it's done.
merge([], L, L).
merge([HF|TF], [HS|TS], [HF|R]) :-    % On first smaller, add it to the list.
  HF < HS,
  merge(TF, [HS|TS], R).
merge([HF|TF], [HS|TS], [HS|R]) :-    % On second smaller, add it to the list. 
  HF > HS,
  merge([HF|TF], TS, R).
merge([HF|TF], [HS|TS], [HF|R]) :-    % On equal elements, remove both and keep only one.
  HF == HS,
  merge(TF, TS, R).

% mergeWithoutDuplicates(FS - first source, SS - second source, R - result)
% flow model: (i, i, io)
merge_without_duplicates(FS, SS, R) :-
  merge(FS, SS, Merged),
  remove_duplicates(Merged, R).

% flattened_merge(S - Source, R - result)
% flow model: (i, o)
flattened_merge([], []).
flattened_merge([SH|ST], R) :-       % Head is a list, merge it normally.
  is_list(SH),
  flattened_merge(SH, FlattenedSH),
  flattened_merge(ST, FlattenedST),
  merge_without_duplicates(FlattenedSH, FlattenedST, R).
flattened_merge([SH|ST], R) :-       % Head is a number, merge it by turning it into a list.
  flattened_merge(ST, FlattenedST),
  merge_without_duplicates([SH], FlattenedST, R).
