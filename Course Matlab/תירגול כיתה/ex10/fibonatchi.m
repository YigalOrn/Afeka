function [ vec ] = fibonatchi( n )

%
%

if(n<=2)
    vec = [] ;
else 
    i=3;
    vec(1) = 0;
    vec(2) = 1;
    vec(3) = 1; 
    while(i<=n)  
        vec(i) = vec(i-1)+vec(i-2) ;
        i = i+1 ;
    end
    
end %%func

