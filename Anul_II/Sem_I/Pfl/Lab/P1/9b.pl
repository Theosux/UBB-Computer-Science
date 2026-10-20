% interval(M:Element, N:Element, R:Lista)
% (i, i, o) - determinist
% M - numarul de la care incepe multimea
% N - numarul la care se termina
% R - multimea de nr crescatoare

interval(M,N,[]) :- M>N.
interval(M,N,[M|R]) :- M=<N,M1 is M+1, interval(M1,N,R).


