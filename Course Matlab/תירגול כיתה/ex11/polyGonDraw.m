function [ ] = polyGonDraw(n,k)

%
%

r = 50 ;
theta = 0:(2*pi)/(n+1):(2*pi);
%NOTICE the plus 1! , 
%becuase of the angles!!


for (i=1:k)
    
    x = r.*cos(theta);
    y = r.*sin(theta);
    hold on;
    if(rem(i,2)==0)
    plot(x,y,'m');
    else
      plot(x,y,'b');  
    end
    
    r = r-15 ;
    
    
    
end%for






end

