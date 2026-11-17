% nuAreDivizori(N:integer, D:integer)
% (i, i) - determinist
% N - numarul verificat
% D - divizorul curent incercat

nuAreDivizori(N,D) :- D*D > N.
nuAreDivizori(N,D) :- D*D =< N, N mod D =\= 0, D1 is D+1, nuAreDivizori(N,D1).

% ePrim(N:integer)
% (i) - determinist
% N - numarul de verificat daca este prim

ePrim(2).
ePrim(N) :- N > 2, nuAreDivizori(N,2).

% dubluPrime(L:list, R:list)
% (i, o) - determinist
% L - lista de numere intregi
% R - lista L in care fiecare numar prim apare de 2 ori

dubluPrime([],[]).
dubluPrime([H|T],[H,H|R]) :- ePrim(H), dubluPrime(T,R).
dubluPrime([H|T],[H|R]) :- \+ ePrim(H), dubluPrime(T,R).

% ?- dubluPrime([1,2,3,4,5],R).                 R = [1,2,2,3,3,4,5,5]
% ?- dubluPrime([1,3,7,9,10],R).                R = [1,3,3,7,7,9,10]
% ?- dubluPrime([0,-3,4],R).                    R = [0,-3,4]
% ?- dubluPrime([],R).                          R = []
