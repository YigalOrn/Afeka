function [y]= egool(x,m)
%This function  rounds numbers according to an input that defines the number of digits. 
% The function receives two inputs: 
% The first input is an array of random fractions (scalar, vector or a matrix),
% and the second input determines the number of the rounded digits.
a=x*10^m;
b=round(a)
y=b/10^m