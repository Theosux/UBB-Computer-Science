% inversare(L:list, C:list, R:list)
% (i, i, o) - determinist
% L - lista de inversat
% C - colectorul (initial [])
% R - rezultatul: inversa lui L

inversare([], C, C).
inversare([H|T], C, R) :- inversare(T, [H|C], R).

% adun(A:list, B:list, C:integer, R:list)
% (i, i, i, o) - determinist
% A - cifrele primului numar, inversate
% B - cifrele celui de-al doilea numar, inversate
% C - transportul (0 sau 1)
% R - cifrele sumei, inversate

adun([], [], 0, []).
adun([], [], 1, [1]).
adun([H|T], [], C, [D|R]) :- S is H + C, D is S mod 10, C1 is S div 10, adun(T, [], C1, R).
adun([], [H|T], C, [D|R]) :- S is H + C, D is S mod 10, C1 is S div 10, adun([], T, C1, R).
adun([H1|T1], [H2|T2], C, [D|R]) :- S is H1 + H2 + C, D is S mod 10, C1 is S div 10, adun(T1, T2, C1, R).

% suma(A:list, B:list, R:list)
% (i, i, o) - determinist
% A - primul numar, cifra cu cifra
% B - al doilea numar, cifra cu cifra
% R - suma A + B, cifra cu cifra

suma(A, B, R) :- inversare(A, [], AI), inversare(B, [], BI), adun(AI, BI, 0, RI), inversare(RI, [], R).

% ?- suma([1,2,3],[9,9],R).                     R = [2,2,2]
% ?- suma([9,9],[1],R).                         R = [1,0,0]
% ?- suma([5],[5],R).                           R = [1,0]
% ?- suma([1,9,3,5,9,9],[1,9,3,5,9,9],R).       R = [3,8,7,1,9,8]
% ?- suma([0],[7],R).                           R = [7]




