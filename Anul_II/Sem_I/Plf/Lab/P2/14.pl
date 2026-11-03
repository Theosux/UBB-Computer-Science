% inversare(L:list, C:list, R:list)
% (i, i, o) - determinist
% L - lista de inversat, C - colectorul, R - rezultatul

inversare([], C, C).
inversare([H|T], C, R) :- inversare(T, [H|C], R).

% predecesor(L1:list, L2:list)
% (i, o) - determinist
% L1 - lista inversata la care facem predecesor, L2 - lista rezultata

predecesor([H|T], [H1|T]) :- H =\= 0, H1 is H-1.
predecesor([0|T], [9|R]) :- predecesor(T, R).

% eliminaZero(L1:list, L2:list)
% (i, o) - determinist
% L1 - lista care verificam sa nu aiba 0 la inceput, L2 - lista fara 0

eliminaZero([H|T], T) :- H =:= 0, T \= [].
eliminaZero([H|T], [H|T]) :- H =\= 0.
eliminaZero([0], [0]).

% predecesorMain(L:list, R:list)
% (i, o) - determinist
% L - nr scris ca lista de cifre, R - predecesorul lui L

predecesorMain(L, R) :- inversare(L, [], L2),
	predecesor(L2, P1),
	inversare(P1, [], P2),
	eliminaZero(P2, R).

% pentru b):

% predecesorListaEterogena(L:list, R:list)
% (i, o) - determinist
% L - lista eterogena
% R - lista in care fiecare sublista e inlocuita cu predecesorul ei

predecesorListaEterogena([], []).
predecesorListaEterogena([H|T], [P|R]) :- is_list(H), predecesorMain(H, P),
	predecesorListaEterogena(T, R).
predecesorListaEterogena([H|T], [H|R]) :- number(H), predecesorListaEterogena(T, R).


% Teste a):
% ?- predecesorMain([1,9,3,6,0,0],R).   R = [1,9,3,5,9,9]
% ?- predecesorMain([2,3],R).           R = [2,2]
% ?- predecesorMain([1,2,0],R).         R = [1,1,9]
% ?- predecesorMain([4,0,9],R).         R = [4,0,8]
% ?- predecesorMain([2,0,0,1],R).       R = [2,0,0,0]
% ?- predecesorMain([1,0,0],R).         R = [9,9]
% ?- predecesorMain([1,0,0,0,0],R).     R = [9,9,9,9]
% ?- predecesorMain([1,0],R).           R = [9]
% ?- predecesorMain([9,9,9],R).         R = [9,9,8]
% ?- predecesorMain([5],R).             R = [4]
% ?- predecesorMain([1],R).             R = [0]
% ?- predecesorMain([0],R).             false
% ?- predecesorMain([],R).              false
% ?- predecesorMain([1,0,0],[9,9]).     true
% ?- predecesorMain([1,0,0],[0,9,9]).   false

% Teste b):
% ?- predecesorListaEterogena([1,[2,3],4,5,[6,7,9],10,11,[1,2,0],6],R).
%    R = [1,[2,2],4,5,[6,7,8],10,11,[1,1,9],6]
% ?- predecesorListaEterogena([],R).              R = []
% ?- predecesorListaEterogena([1,2,3],R).         R = [1,2,3]
% ?- predecesorListaEterogena([[1,0,0],[1]],R).   R = [[9,9],[0]]
% ?- predecesorListaEterogena([7,[1,0],8],R).     R = [7,[9],8]
% ?- predecesorListaEterogena([3,[0]],R).         false
