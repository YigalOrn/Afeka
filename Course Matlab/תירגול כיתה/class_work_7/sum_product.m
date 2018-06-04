function [s m]=sum_product(a,b,c)
%This function calculates the sum and product of 3 numbers
%and displays it on the CW.
s=a+b+c;
m=a*b*c;
disp(['The sum and the product of this array are:   ' num2str(s)  '   and    ' num2str(m) ])