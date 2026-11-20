% parcurgere(L:list, E:integer, P:integer, PN:integer, R:list)
% (i,i,i,i,o); determinist
% L - lista care se da, E - elementul care se da
% P - pozitia la care suntem acum
% PN - pozitia la care va urma sa adaugam E-uri
% R - lista finala

parcurgere([],_,_,_,[]).
parcurgere([H|T],E,P,PN,[H|R]) :- P =\= PN, P1 is P+1, parcurgere(T,E,P1,PN,R).
parcurgere([H|T],E,P,PN,[H,L1|R]) :- P =:= PN, P1 is P+1, PN1 is 2*PN+1,adaugare(E,PN,L1), parcurgere(T,E,P1,PN1,R).

% adaugare(E:integer, N:integer, R:list)
% (i,i,o); determinist
% E - elementul care se da, N - numarul care se da
% R - lista care contine E de N ori

adaugare(_,N,[]) :- N =< 0.
adaugare(E,N,[E|R]) :- N > 0, N1 is N-1, adaugare(E,N1,R).

% parcurgere([1,2,3],0,1,1,R).
% parcurgere([1,2,3,4,5,6],0,1,1,R).
