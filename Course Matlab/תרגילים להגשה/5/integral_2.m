function [ area ] = integral_2( fVec , x )

%
%

tic

dx = diff(x);

len = length(x) ;

j = 2 ;
tmp = 0 ;
while(j<=len-1)
    
    tmp = tmp + fVec(j) ;
    j = j+1 ;
    
end%while


vecTemp = ( (fVec(1)+fVec(len))/2 +tmp )*dx ;

area = vecTemp(1);

toc

end %func




% sum = 0 ;
% k = length(x)-1;
%
% for (i = 1:k)
%
%     tmp = 0 ;
%     j = 2 ;
%     while (j<=i-1)
%
%         tmp = tmp+fVec(j);
%         j = j+1 ;
%     end%while
%
%     sum = sum + ( x(i+1)-x(i) )*(  fVec(1)+fVec(i) )/2 + tmp  ;
%
%
% end %for
%
%
% area = sum ;
