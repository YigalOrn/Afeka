%% ex10
clc; clear all; format compact;

%%
clc;clear all ;
vec = 2:1:52 ;

a = 0 ;
b= 1 ;

tur1x(1) = 0 ;
tur1y(1) = 50 ;

tur2x(1) = 50 ;
tur2y(1) = 0 ;

for (i=vec)

 x =  rand(1)*(b-a)+a  ;
  y = rand(1)*(b-a)+a  ;
   
  tur1x(i) = tur1x(i-1)+x ;
   tur1y(i) = tur1y(i-1)-y ;
    
    tur2x(i) = tur2x(i-1)+(x*-1) ;
   tur2y(i) = tur2y(i-1)+y;
   
end

dis = sqrt(   (  tur1x(i)-tur2x(i)   )^2  + (  tur1y(i)-tur2y(i)   )^2      ) 

%  tur1x
%  tur1y
%   tur2x
%   tur2y
 
close all;
figure(1) ;
hold on;
plot(  tur1x, tur1y  ,'r'  );
plot(  tur2x, tur2y  , 'g' );
plot(    [tur1x(i),tur2x(i)] , [tur1y(i),tur2y(i) ] , 'm' )
 hold off;




%%
clc;clear all ;

flag = 1 ;
num = 1;
while (flag)
    if(  (rem(num,3)==0) & (num^3>4000) &(rem(num,2)~=0)  )
    flag = 0 ;
    else
        num = num+1 ;
    end
end
disp(['the required num is: ', num2str(num) ] );

%%
clc;clear all ;


num = 10 ;
 fibonatchi(num)
 num = 2 ;
fibonatchi(num)


%%

clc;clear all ;

x = -2:0.001:2 ;
p = [1.5, 0,-5,1,2];

y = polyval(p,x);
plot(y,'m');

%%
clc;clear all ;

op1 = 'add';
op2 = 'sub';

p1 = [1,-7,11,-4,-5,-2] ;
p2 = [9,-10,6] ;

 A = polyAdd( p1,p2,op1 )
 B = polyAdd( p1,p2,op2 )


%%
clc;clear all ;

x = [-5,-4,-2.2,-1,0,1,2.2,4,5,6,7] ;

%% polynom related functions

% conv()
% deconv()
% roots()
% polyder()





