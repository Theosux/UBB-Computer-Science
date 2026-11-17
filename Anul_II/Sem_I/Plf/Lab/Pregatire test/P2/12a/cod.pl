% inlocuieste(L:list, E:element, X:element, R:list)
% (i, i, i, o) - determinist
% L - lista initiala
% E - elementul inlocuit
% X - elementul cu care inlocuim
% R - lista L cu fiecare E inlocuit cu X

inlocuieste([],_,_,[]).
inlocuieste([H|T],E,X,[X|R]) :- H = E, inlocuieste(T,E,X,R).
inlocuieste([H|T],E,X,[H|R]) :- H \= E, inlocuieste(T,E,X,R).

% ?- inlocuieste([1,2,1,3],1,9,R).              R = [9,2,9,3]
% ?- inlocuieste([a,b,c],d,x,R).                R = [a,b,c]
% ?- inlocuieste([],1,2,R).                     R = []
