function res = zeroDiag1(A)
[l m]=size(A);

g=ones(l)-eye(l);

res=A.*g;