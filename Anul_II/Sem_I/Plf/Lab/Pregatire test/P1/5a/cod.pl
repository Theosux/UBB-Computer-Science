% sterge(E:element, L:list, R:list)
% (i, i, o) - determinist
% E - elementul de sters
% L - lista din care stergem
% R - lista finala

sterge(_,[],[]).
sterge(E,[H|T],[H|R]) :- H \= E, sterge(E, T, R).
sterge(E,[H|T],R) :- H = E, sterge(E, T, R).

% ?- sterge(a,[a,b,a,c],R).   R = [b,c]
% ?- sterge(x,[a,b],R).       R = [a,b]
% ?- sterge(a,[a,a],R).       R = []
% ?- sterge(1,[1,2,1,3],R).   R = [2,3]

