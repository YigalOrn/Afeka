function [ x,y,w] = maxormin( a,b,c )

%use the symetric axle formolas!


if(a>0)
    
    %smiling parabola
    w = 2
else
    %sad parabola
    w = 1 ;
end


x = -b/(2*a);
y = -(b^2 - (4*a*c))/(4*a) ;

    
end%func

