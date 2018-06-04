%% Class_Work_10
%% General
clc;clear all;format compact;clf;
%% Polynomial in Matlab
%MATLAB represents polynomials as row vectors containing coefficients 
%ordered by descending powers.
% For example: to enter this polynomial into MATLAB, use
%y=2x4 + 3x3 ? 10x2 ? 11x + 22

p=[2, 3, -10, -11, 22] %coefficients of the polynomial starting 
%with the highest power and ending with the constant term
%%  Polynomial- examples
clc;clear all;
%y=8*x+5
p1=[8 5];
%y=6*x^2-50
p2=[6 0 -150]
%y=7*x^3+3
p3=[7 0 0 3]
%% Polyval -returns the value of the polynomial p evaluated at x.
%% y=polyval(p,x)
%,Polyval evaluates p at each element of x.
p1=[3 2 1]
y1=polyval(p1,5) %x is scalar
x=[5 7 9];
y2=polyval(p1,x);
x=-5:0.1:5;
y2=polyval(p1,x);%x is a vector
%% Plotting the polynomial
clear all;clc;clf
p=1:4;%y=x^3+2x^2+3x+4
x=-10:0.1:10;%defining the x range
y=polyval(p,x);
plot(x,y)
%% class assignment_10, 1
clear all;clc;clf
x=-2:0.01:2;
p=[1.5 0 -5 1 2];
y=polyval(p,x);
plot(x,y)
%% class assignment_10, 2
% See m-file polyadd
f1=[1 -7 11 -4 -5 -2];
 f2=[-9 -10 6];
 p=polyadd(f1,f2,'add')
 
 %% polyder, roots, conv, deconv – individual study!!!

%% Polyfit- Fitting Data to a Polynomial
%% p=polyfit(x,y,n)
%p = polyfit(x,y,n) finds the coefficients of a polynomial p(x) of degree n
%that fits the data (x,y), p(x(i)) to y(i), in a least squares sense
% Consider the following set of data:
clf;clear all;clc
x=[1 2 3 3.5 4 4.1];
y=[1 ,0.5,1.5 , 1.3, 0.55, -1];
plot(x,y,'o') %plotting the given data
axis([-1 5 -2 2])
n=3;% you can change  the ploynomial order to improve the fit of the curve
% make a polynomial of order n that fits the data
p=polyfit(x,y,n);
xp=0:0.1:5; %in the range of the given data
yp=polyval(p,xp);% evaluate the polynomial p
hold on%plot data and the polynomial together
plot(xp,yp,'r*-')
hold off
y2=polyval(p,2) %evaluate the polynomial at x=2
ydata=y(x==2) % the measured data at x=2
%% class assignment_10, 3
clc;clear all;clf
x=[ -5 -4  -2.2 -1   0   1   2.2 4   5   6   7];
y=[0.1  0.2 0.8  2.6 3.9 5.4 3.6 2.2 3.3 6.7 8.9];
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
subplot(2,2,1)
n=1
p1=polyfit(x,y,n);
x1=-10:0.1:10;
y1=polyval(p1,x1);
%1st degree curve created
plot(x,y,'o',x1,y1,'-') ;axis([-10 10 -10 10]) 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
subplot(2,2,2)
n=3
p2=polyfit(x,y,n);
x1=-10:0.1:10;
y1=polyval(p2,x1);
%3rd degree curve created
plot(x,y,'o',x1,y1,'-'); axis([-10 10 -10 10]) 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
subplot(2,2,3)
n=4
p3=polyfit(x,y,n);
x1=-10:0.1:10;
y1=polyval(p3,x1);
%4th degree curve created
plot(x,y,'o',x1,y1,'-'); axis([-10 10 -10 10]) 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
subplot(2,2,4)
n=10
p4=polyfit(x,y,n);
x1=-10:0.1:10;
y1=polyval(p4,x1);
%10th degree curve created
plot(x,y,'o',x1,y1,'-') ;axis([-10 10 -10 10]) 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% interp1:  One-dimensional data interpolation
% yi = interp1(X,Y,xi,'Method') interpolates to find yi, 
% the values of the underlying function Y at the points in the vector or array xi.
% Default: linear interpolation (options for other interpolations – see help)
clf;clear all;clc
% Consider the following set of data:
x=[1 2 3 3.5 4 4.1];
y=[1 ,0.5,1.5 , 1.3, 0.55, -1];
xi=2.5 % must be in the range of x
yi = interp1(x,y,xi)
xi1=1:0.1:2 ;
yi1=interp1(x,y,xi1);
figure(1)
plot(x,y,'bo',xi1,yi1,'r*-')
% Cubic Spline Interpolation
% yi = interp1(X,Y,xi,method) 
figure(2)
xi1=1:0.1:3.5 ;% must be in the range of x
yi1=interp1(x,y,xi1,'spline');
plot(x,y,'bo',xi1,yi1,'r*-')
%% class assignment_10, 4
%Exam Moed A 2008
clc;clear all;clf
t=0:0.04:0.6;
ecg=-[0.2440 0.2284 0.2108 0.1310 0.0402 0.0342 0.1046 0.1530 0.1886 0.1956 0.1938 0.1864 0.1456 0.1108 0.2252 0.2368];
plot(t,ecg,'ro')
t_i=linspace(0,0.6,60);
p=polyfit(t,ecg,8);
ecg_p=polyval(p,t_i);
hold on
plot(t_i,ecg_p,'-b')
ecg_i=interp1(t,ecg,t_i,'spline')
plot(t_i,ecg_i,'g:')

%%  class assignment_10, 5
% Exam Moed A, 2010
clc;clear all;clf
x=linspace(0,5,50);
y=rand(1,50)*20;
y=sort(y);
plot(x,y,'bo')
p=polyfit(x,y,1);
Pp=polyval(p,2.5)
Cp=min(abs(y-Pp))
xi=0:0.1:5;
yi=interp1(x,y,xi);
Pi=yi(find(xi==2.5))
Ci=min(abs(y-Pi))
if Cp>Ci
   xt=0;0.1:5;
   yt=polyval(p,xt);
   hold on
   plot(xt,yt,'--k')
   legend('Points','1^{st} degree polynomial')
   title('Cp>Ci')
   
else
    hold on
    plot(xi,yi,'r--')
    legend('Points','Interpolation')
   title('Ci>Cp')
end







