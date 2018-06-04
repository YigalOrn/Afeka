function [  ] = func1( )

%close all ;
figure(2) ;
hold on ;

for (x=-6:0.001:6 )
    
    if (   (-6<=x)&(x<=-2)   )
        
       y1 = 4*exp(x+2) ;
        plot(x,y1,'r');
       
    elseif (   (-2<=x)&(x<=2) )
        
          y2 = x^2 ;
        plot(x,y2,'m');
        
    else
      
          y3 = (x+62)^(1/3) ;
        plot(x,y3,'b');
        
    end
    
end %for
hold off ;

end

