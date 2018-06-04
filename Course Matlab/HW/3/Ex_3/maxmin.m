function [ x ,y] = maxmin( a,b,c )

%return the coordinates (x,y) for the max or min of the quadratic
%equation that has the coefficients a,b,c .
%I will use some known math tricks.

x = -b/(2*a) ;
y = -(b^2 - (4*a*c))/(4*a) ;


end

