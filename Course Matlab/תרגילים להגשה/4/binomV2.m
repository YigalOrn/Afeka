function [ A ] = binomV2( n )


%calculating Pascals triangle of size  - n


B = zeros(n) ;

for  (i = 1:n)
   
    j=1;
    
    while (j<=i)
        
        if( j==1)
        B(i,j) = 1 ;
        else
         B(i,j) =  B(i-1,j-1)+ B(i-1,j) ;
            
        end %if
        
        j = j +1 ;
        
    end % while
        
end % for


A = B ;

end % end of func


