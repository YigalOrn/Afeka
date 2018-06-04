%% Ornes Yigal_HW2
%% 1)
%qs1a
v = linspace(7, 40, 14)
%qs1b
b = v(1,[1,5,6])  
%qs1c
c = [ v(8:end), v(1:7) ] 
%qs1d  ??????
d = v(1,2:end)
%qs1h
%because vecotr v is made using linspace! we can just sort the vector.
h = sort(v,2,'descend') 


%% 2)
clc;format bank;format compact;
x = -2.5:0.5:3 ;
y = (x.^2+1).^3.*x.^3 ;
% y' % for your convenient
%% 3)
clc;
g = 9.81 ;
t = 1:1:9 ;
d = (0.5*g).*(t.^2) ;
% d' % for your convenient
%% 4)
clc; format long;
ln2 = log(2)
%a
n = 0:50 ;
y = 1./( (2.*n+1).*(2.*n+2) ) ;
summation_a = sum(y)

%b
n = 0:500 ;
y = 1./( (2.*n+1).*(2.*n+2) ) ;
summation_b = sum(y)
%c
n = 0:5000 ;
y = 1./( (2.*n+1).*(2.*n+2) ) ;
summation_c = sum(y)

%% 5)
clc;
x = 1:10 ; 
y = 1:10 ; 
MULT = x'*y % column vector multiplies with a row vector

%% 6)
clc;format bank;
A = [2,-3,4 ; 1,1,4 ; 3,4,-2] ;
%the postion of the coefficient of the variable 
%in the equation counts !!!!
c = [5,10,0] ;

% A*x=c , pseudo code not matlab syntax !
x = A^-1 *c'

%% 7)
clc;
x = [-2,-0.5,1,2.5] ;
y = [-3.4,5.525,16.7,70.625] ;

A = [reshape([x.^3,x.^2,x],4,3), ones(4,1)] 

% remark for me , look at 6 !
c = A^-1 *y'

%% 8)
clc;
A = reshape(2:2:70,7,5)' % its ok we can look at the WorkSpace !
B = A(3:5,4:7)

%% 9)
clc;

MAX_LIM = 60 ;
MIN_LIM = 10 ;

MAT = round( rand(1000)*(MAX_LIM-MIN_LIM)+MIN_LIM ) ;
mean(mean(MAT))
% some of the results :
% 34.99
% 35.01
% 35.00
% 34.98

%% 10)
clc;

MAX_LIM = 10 ;
MIN_LIM = 3 ;

n = round( rand(1)*(MAX_LIM-MIN_LIM)+MIN_LIM )
x = linspace(3,(2*n))
descend = sort(x,'descend')
sum_x = sum(x) 













