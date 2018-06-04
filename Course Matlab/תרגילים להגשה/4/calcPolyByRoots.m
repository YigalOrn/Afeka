function [ p ] = calcPolyByRoots( polyRootsVec )

%By the given roots i will use the
%conv function to calc the original polynomial

% disp('**************');

res = [1,0];% --->  (x-t) , where t is on of the roots
p2 = [1,0] ;
polyRootsVec=polyRootsVec' ;% change to a row vector
vec = polyRootsVec(2:end);
res(1,2) =  -1*polyRootsVec(1,1);

%(x-5)(x+4), roots given in abs!!!!<<<<--------------
%roots()--> 5,4
%wanted value is---> 5,-4

for (i=vec)
    
    p2(1,2) = -1*i;
    res = conv(res,p2);
    
    %     %DEBUG
    %     if(i==vec(end-1) )
    %     res
    %     i+1
    %     end
    
end%for

p = res ;


% disp('**************');

end%func

