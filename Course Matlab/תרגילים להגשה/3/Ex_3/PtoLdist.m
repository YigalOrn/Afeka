function [ d ] =PtoLdist(x0,y0,A,B,C)

%........................

d = abs(     (A*x0+B*y0+C)/sqrt(A^2 + B^2)              ) ;

end

