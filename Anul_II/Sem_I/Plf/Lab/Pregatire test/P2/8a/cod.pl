% inversare(L:list, C:list, R:list)
% (i, i, o) - determinist
% L - lista de inversat
% C - colectorul (initial [])
% R - rezultatul: inversa lui L

inversare([],C,C).
inversare([H|T],C,R) :- inversare(T,[H|C],R).

% succ1(L:list, R:list)
% (i, o) - determinist
% L - cifrele numarului, inversate
% R - cifrele succesorului, inversate

succ1([],[1]).
succ1([9|T],[0|R]) :- succ1(T,R).
succ1([H|T],[H1|T]) :- H < 9, H1 is H+1.

% succesor(L:list, R:list)
% (i, o) - determinist
% L - numarul, cifra cu cifra
% R - succesorul lui L, cifra cu cifra

succesor(L,R) :- inversare(L,[],LR), succ1(LR,RI), inversare(RI,[],R).

% ?- succesor([1,9,3,5,9,9],R).                 R = [1,9,3,6,0,0]
% ?- succesor([9,9],R).                         R = [1,0,0]
% ?- succesor([0],R).                           R = [1]
% ?- succesor([1,2,0],R).                       R = [1,2,1]
