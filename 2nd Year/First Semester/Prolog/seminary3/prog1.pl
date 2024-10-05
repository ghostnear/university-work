% Given a list of numbers and sublists of numbers,
% substitute the sublists in which the sum of elements is odd with the first element of that sublist.
% ex: [1,2,[2,4],7,3,[4,6,7],[1],8,10,[3,2]] -> [1,2,[2,4],7,3,4,1,8,10,3]

% sum(L - list, S - sum)
% flow model: (i,o)
% sum(l1...ln)  =   0   if n = 0
%               =   sum(l2...ln) if n != 0
list_sum([], 0).
list_sum([H|T], R) :-
    list_sum(T, IR),
    R is IR + H.

% sublist(L - list, R - list)
% flow model: (i, o)
% sublist(l1...ln)  =   []  if n = 0
%                   =   l1' + sublist(l2...ln) if l1 is list [l1=l1'...lm'] and sum(l1) % 2 = 1
%                   =   l1 + sublist(l2...ln) otherwise
sub_list([], []).
sub_list([H|T], [H1|R]) :-
    is_list(H),
    list_sum(H, IR),
    IR mod 2 =:= 1, !,
    H = [H1 | _],
    sub_list(T, R).
sub_list([H|T], [H|R]) :-
    sub_list(T, R).