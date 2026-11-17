% apare(E:element, L:list)
% (i, i) - determinist
% E - elementul cautat
% L - lista in care cautam

apare(E,[H|_]) :- H = E.
apare(E,[H|T]) :- E \= H, apare(E,T).

% eMultime(L:list)
% (i) - determinist
% L - lista verificata

eMultime([]).
eMultime([H|T]) :- \+ apare(H,T), eMultime(T).


% ?- eMultime([1,2,3]).                         true
% ?- eMultime([1,2,1]).                         false
% ?- eMultime([]).                              true
% ?- eMultime([a,b,a]).                         false
