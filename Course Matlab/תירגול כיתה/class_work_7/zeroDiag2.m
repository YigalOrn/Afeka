function res = zeroDiag2(A)
[l m]=size(A);
A(1:l+1:l*m)=0;
res=A;