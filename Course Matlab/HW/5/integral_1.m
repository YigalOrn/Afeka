function [ area ] = integral_1( fVec , x )

%using the trpezoid formula,
%where the two bases are the functions values and the height is the x
%value.

tic
sum = 0 ;
k = length(x)-1;

for (i= 1:k)
    
    h = x(i)-x(i+1) ;
    base1 = fVec(i) ;
    base2 = fVec(i+1) ;
    temp = ( base1+base2 )*h/2 ;
    sum = sum +temp ;
       
    
end %for

area = abs(sum) ;

toc


end %func

