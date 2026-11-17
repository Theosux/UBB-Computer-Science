% ePrim(N:integer)
% (i) - determinist
% N - nr de verificat daca este prim

ePrim(2).
ePrim(N) :- N > 2, nuAreDivizori(N, 2).

% nuAreDivizori(N:integer, D:integer)
% (i, i) - determinist
% N - numarul verificat, D - divizorul pe care il incercam

nuAreDivizori(N, D) :- D*D > N.
nuAreDivizori(N, D) :- D*D =< N, N mod D =\= 0, D1 is D+1, nuAreDivizori(N, D1).

% listaPrime(I:integer, N:integer, L:list)
% (i, i, o) - determinist
% I - numarul curent din interval, N - capatul intervalului,
% L - lista numerelor prime din intervalul [I, N]

listaPrime(I, N, []) :- I > N.
listaPrime(I, N, [I|R]) :- I =< N, ePrim(I), I1 is I+1, listaPrime(I1, N, R).
listaPrime(I, N, R) :- I =< N, \+ ePrim(I), I1 is I+1, listaPrime(I1, N, R).

% descompunere(L:list, S:integer, C:list)
% (i, i , o) - nedeterminist
% L - lista de numere prime de unde alegem, S - suma de obtinut
% C - o lista de elemente distincte din L care au suma S

descompunere([H|_], H, [H]).
descompunere([_|T], S, C) :- descompunere(T, S, C).
descompunere([H|T], S, [H|C]) :- S1 is S-H, S1 > 0, descompunere(T, S1, C).

% descompunerePrime(N:integer, C:list)
% (i, o) - nedeterminist
% N - numarul dat, C - o descomp a lui N ca sum de nr prime distincte

descompunerePrime(N, C) :- listaPrime(2, N, L), descompunere(L, N, C).

% toateDescompunerile(N:integer, LC:list)
% (i, o) - determinist
% N - numarul dat, LC - lista tuturor descompunerilor lui N

toateDescompunerile(N, LC) :- findall(C, descompunerePrime(N, C), LC).

% Teste:
% ?- toateDescompunerile(10, LC).      LC = [[3,7],[2,3,5]]
% ?- toateDescompunerile(7, LC).       LC = [[7],[2,5]]
% ?- toateDescompunerile(5, LC).       LC = [[5],[2,3]]
% ?- toateDescompunerile(2, LC).       LC = [[2]]
% ?- toateDescompunerile(12, LC).      LC = [[5,7],[2,3,7]]
% ?- toateDescompunerile(17, LC).      LC = [[17],[2,3,5,7]]
% ?- toateDescompunerile(20, LC).      LC = [[7,13],[3,17],[2,7,11],[2,5,13]]
% ?- toateDescompunerile(4, LC).       LC = []
% ?- toateDescompunerile(1, LC).       LC = []
% ?- descompunerePrime(10, C).	       C = [3,7]; C = [2,3,5] ; false

