function [Radius,Zavit]=merucav(c)
% This function calculates the radius and the angle of a complex number in Cartesian coordinates.
c1=real(c);
c2=imag(c);
Radius=sqrt(c1^2+c2^2);
Zavit=atan2(c2,c1);
 