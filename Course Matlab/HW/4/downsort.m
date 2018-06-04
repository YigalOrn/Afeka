function [ y ] = downsort( x )

%i will implement an ordinary bubble sort.

%isChanged = false ;
n = length(x) ;
y = x ;

for (   i=(n-1):-1:1  )

    for(j=1:i)
    
        if( y(j)<y(j+1) )
            % swap
            temp = y(j) ;
            y(j) = y(j+1) ;
            y(j+1) = temp ;
            
          
        end %if
            
    end %for_j
    
end %for_i
    


end


