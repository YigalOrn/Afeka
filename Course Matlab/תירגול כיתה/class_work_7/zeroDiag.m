function res = zeroDiag(A)
% This function  zeros the main diagonal of a given matrix
d=-diag(A);
B=diag(d);
res=A+B;