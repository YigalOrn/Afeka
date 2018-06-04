%% Ornes Yigal_HW1

%% 1)
clc;
x = 9.6 ;
z = 8.1 ;

a = (x*z^2) - ( (2*z)/(3*x)  )^(3/5) % a = 629.1479
b = ( (443*z)/(2*x^3) ) + ( exp(-x*z)/(x+z) ) % b = 2.0279

%% 2)
clc;
x = (5/24)*pi ;

a1 = sin( (2*x) ) % a1 = 0.9659
a2 = ( 2 * sin(x) * cos(x) ) % a2 = 0.9659

b1 = cos(x/2) % b1 = 0.9469 
b2 = sqrt( ((1+cos(x))/2)) % b2 = 0.9469  

%% 3)
clc;
x =  (3/17)*pi ;

a1 = tan( (2*x) ) % a1 = 2.0083
a2 = ( 2*tan(x) ) /( 1-tan(x)^2 ) % a2  = 2.0083 

b1 = tan( (x/2) ) % b1 = 0.2845
b2 = sqrt( (  (1-cos(x))/(1+cos(x))   )  ) % b2 = 0.2845 

%% 4)
clc;
x = (5/9)*pi ; % alpha = x
y = pi/7 ; % beta = y

left = cos(x) - cos(y) % left = -1.0746
right = 2*sin(  (0.5*(x+y))  )*sin( (0.5*(y-x)) ) % right = -1.0746

%% 5)
clc;
a = 11 ; 
c = 21 ;

%q5a
% b = sqrt( c^2 - a^2 ) 
b = sqrt( (c^2-a^2)  ) % b = 17.8885

%q5b
%result should be in degrees.
alpha = tand( (a/b)  ) % alpha = 0.0107

%% 6)
clc;
a = 18 ;
b = 35 ;
c = 50 ;

gama = acosd(  ( (c^2-(a^2+b^2))/(-2*a*b) )   ) % gama = 139.0046

%% 7)
clc;
% 3x+5y-6=0 , (2,-3)
A = 3 ;
B = 5 ;
C = -6 ;
x0 = 2 ;
y0 = -3 ;

d = abs((A*x0+B*y0+C))/sqrt((A^2+B^2)) % d = 2.5725


%% 8)
clc;
flowersInBox = 12 ;
flowers = 751 ;

boxes = ceil((flowers/flowersInBox)) % boxes = 63

%% 9)
clc;
table_price = 256.95 ;
chair_price = 89.99 ;
tax = (5.5/100) ;

a = (8*chair_price) + (2*table_price) % a = 1.2338e+03
b = a +(a*tax) % b = 1.3017e+03
c = round(b) % c = 1302 

%% 10)
clc;
%lcm()

a = lcm(4, 10) % a = 20
b = lcm(6, 38) % b = 114


%% END