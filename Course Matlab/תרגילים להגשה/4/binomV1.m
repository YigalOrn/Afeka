function [ A  ] = binom( n  )

%calculating Pascals triangle of size  - n
%using a help function -  binomCoefficient(n, k)

B = zeros(n) ;

for  (i = 1:n)
   
    j=1;
    
    while (j<=i)
        
     val =  binomCoefficient(i-1, j-1) ;
       B (i, j)  =  val ; 
        
        j = j +1 ;
        
    end % while
        
end % for


A = B ;

end % end of func


