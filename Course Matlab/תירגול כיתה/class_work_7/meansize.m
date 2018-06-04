function [l,m,c]=meansize (M) 
%  For a given array the function returns:
%1. Number of lines , 2. Mean of the arrays’s elements  3. Number of columns
m=mean (M(:));
[l, c]=size(M);
