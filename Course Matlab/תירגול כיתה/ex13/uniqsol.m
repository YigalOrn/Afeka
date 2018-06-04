function [ vecx, nx] = uniqsol( f,a,b )

%
%
k=1 ;
r = a:0.2:b ; 

bool = false ;
for (i=r)    

    tmp = fzero(f,i) ;
   
    if(tmp>=a & tmp<=b)
    vecx(k) = tmp ;
    vecx(k) = ( round(vecx(k)*100) )/100  ;
   k = k+1 ;
    end
     
end%for

  
nx = length(vecx) ;


end%function

