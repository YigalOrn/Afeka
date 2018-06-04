function [ res] = polyAdd( p1,p2,op )
%
%
p1Len = length(p1) ;
p2Len = length(p2) ;

if(p1Len>p2Len)
    p2 = [zeros(1,p1Len-p2Len), p2] ;  
else  
        p1 = [zeros(1,p2Len-p1Len), p1] ;    
    end%if
    
    if( op == 'add')
    res =  p1+p2 ;
    elseif(op =='sub')
   res =  p1-p2  ;     
    end%if
        
    end%func
    
