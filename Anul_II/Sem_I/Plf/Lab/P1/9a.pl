% eInMultime(E:element, L:List)
% (i, i) - determinist
% E - element de cautat in lista, L - lista

eInMultime(E,[H|_]) :- E =:= H.
eInMultime(E,[H|T]) :- E =\= H, eInMultime(E,T).


% intersectie(L1:List, L2:List, R:List)
% (i, i, o) - determinist
% L1 - prima multime, L2 - a doua multime, R - multimea intersectii lor

intersectie([],_,[]).
intersectie([H|T],L2,[H|R]) :- eInMultime(H,L2), intersectie(T,L2,R).
intersectie([H|T],L2,R) :- \+ eInMultime(H,L2), intersectie(T,L2,R).

% ?- intersectie([1,2,3,4],[3,4,5],R).   R = [3,4]
% ?- intersectie([],[1,2],R).            R = []
% ?- intersectie([1,2],[],R).            R = []
% ?- intersectie([1,2,3],[4,5],R).       R = []
% ?- intersectie([1,2,3],[3,2,1],R).     R = [1,2,3]
