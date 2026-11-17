% select(L:list, E:integer, R:element)
% (i, i, o) - determinist
% L - lista
% E - pozitia (E >= 1)
% R - elementul de pe pozitia E

select([H|_],1,H).
select([_|T],E,R) :- E > 1, E1 is E-1, select(T,E1,R).

% ?- select([a,b,c,d],3,R).                   R = c
% ?- select([a,b,c,d],1,R).                   R = a
% ?- select([a,b],5,R).                       false
