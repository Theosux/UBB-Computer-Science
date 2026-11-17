% adaugaUnu(L:list, R:list)
% (i, o) - determinist
% L - lista de numere intregi
% R - lista L in care dupa fiecare element par apare 1

adaugaUnu([],[]).
adaugaUnu([H|T],[H,1|R]) :- H mod 2 =:= 0, adaugaUnu(T,R).
adaugaUnu([H|T],[H|R]) :- H mod 2 =:= 1, adaugaUnu(T,R).

% ?- adaugaUnu([1,2,3,4],R).                    R = [1,2,1,3,4,1]
% ?- adaugaUnu([2,2],R).                        R = [2,1,2,1]
% ?- adaugaUnu([1,3],R).                        R = [1,3]
% ?- adaugaUnu([],R).                           R = []
