function p=polyadd(p1,p2,operation)
% p1 are the coefficienat of the 1st polynomial
% p2 are the coefficienat of the 2nd polynomial
% operation is the string 'add' or 'sub'
m1=length(p1);
m2=length(p2)
if m1>m2
    p2=[zeros(1,m1-m2),p2];
elseif m2>m1
    p1=[zeros(1,m2-m1),p1];
end
if length(operation)==3
    if operation=='add'
        p=p1+p2;
    elseif operation=='sub'
           p=p1-p2;
    else
        p=[];
        disp('wrong input')
    end
    else
        disp('wrong input')
        p=[];
end