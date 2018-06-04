function B=change(A)
% "change" change the minimum elements in an  array with its maximum value
mnA=min(A(:));
mxA=max(A(:));
i=find(mnA==A);
A(i)=mxA;
B=A;
 