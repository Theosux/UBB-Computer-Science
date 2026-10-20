% interval(M:Element, N:Element, R:Lista)
% (i, i, o) - determinist
% M - numarul de la care incepe multimea
% N - numarul la care se termina
% R - multimea de nr crescatoare

interval(M,N,[]) :- M>N.
interval(M,N,[M|R]) :- M=<N,M1 is M+1, interval(M1,N,R).

% ?- interval(1,5,R).   R = [1,2,3,4,5]
% ?- interval(1,1,R).   R = [1]
% ?- interval(2,1,R).   R = []

