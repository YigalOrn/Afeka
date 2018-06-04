%% quadroots.m
a=input('a=');
b=input('b=');
c=input('c=');
D=b^2-4*a*c;
if D>0
    r1=(-b+sqrt(D))/(2*a);
    r2=(-b-sqrt(D))/(2*a);
    disp('The eq. has 2 roots:') 
    disp(['r1=',num2str(r1),',   r2=',num2str(r2)])
elseif D==0
    r=-b/(2*a);
    disp('The eq. has 1 root:') 
    disp(['r=',num2str(r)])
else
    disp('The eq. has no real roots') 
end
    
    
