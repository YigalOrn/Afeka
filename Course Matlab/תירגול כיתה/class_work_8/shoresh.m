function [y1 y2]=shoresh(a,b,c)
% This is the function for ex 5 part 1
% This function calculate the roots of second order equation
% You have to write: [x1 x2]=shoresh(a,b,c)
y1=(-b+sqrt(b^2-4*a*c))/(2*a);
y2=(-b-sqrt(b^2-4*a*c))/(2*a);
 