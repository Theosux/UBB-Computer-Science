% inversare(L:list, C:list, R:list)
% (i, i, o) - determinist
% L - lista de inversat
% C - colectorul (initial [])
% R - rezultatul: inversa lui L

inversare([], C, C).
inversare([H|T], C, R) :- inversare(T, [H|C], R).

% secv(L:list, C:list, LC:integer, B:list, LB:integer, R:list)
% (i, i, i, i, i, o) - determinist
% L - lista curenta
% C - secventa para curenta (colector, inversata)
% LC - lungimea lui C
% B - cea mai lunga secventa gasita pana acum (inversata)
% LB - lungimea lui B
% R - cea mai lunga secventa para (inversata)

secv([],C,LC,_,LB,C) :- LC > LB.
secv([],_,LC,B,LB,B) :- LC =< LB.
secv([H|T],C,LC,B,LB,R) :- H mod 2 =:= 0, LC1 is LC + 1, secv(T,[H|C],LC1,B,LB,R).
secv([H|T], C, LC, _, LB, R) :- H mod 2 =\= 0, LC > LB, secv(T, [], 0, C, LC, R).
secv([H|T], _, LC, B, LB, R) :- H mod 2 =\= 0, LC =< LB, secv(T, [], 0, B, LB, R).

% secvPara(L:list, R:list)
% (i, o) - determinist
% L - lista de numere intregi
% R - cea mai lunga secventa de numere pare consecutive din L

secvPara(L,R) :- secv(L, [], 0, [], 0, RI), inversare(RI, [], R).

% ?- secvPara([2,1,4,6,7],R).                   R = [4,6]
% ?- secvPara([1,4,6,8,3],R).                   R = [4,6,8]
% ?- secvPara([1,2,3,4],R).                     R = [2]
% ?- secvPara([1,5],R).                         R = []
% ?- secvPara([1,2,4,3,6,8],R).                 R = [2,4]
% ?- secvPara([],R).                            R = []
