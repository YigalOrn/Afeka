%% Class_Work_6
%% General
clc, clear all, format compact;
%% Plot
% Syntax: plot(x,y)
clc
%its a house!, points order matters
x=[5 5 2.5 0 0 5];
y=[0 5 7.5 5 0 0];
plot(x,y) %note length of x and y must be the same
%%  Multiple graphs on the same plot
clc
figure(1)
x=0:5:360;
plot(x,sind(x),'+-m',x,cosd(x),'g:s') %Line properties (in MATLAB help: under Linespec)

%% class_assignment_6,1
x=-10:0.1:10;
y=(x.^2-x+1)./(x.^2+x+1);
plot(x,y)
%% Create figure graphics object
figure(1) % creates a new figure object
close(1) % close the figure
%%  Design the Graph
% title ('title_string') - title the graph
% xlabel('x_label_string') -  adding x axis label to the graph 
% ylabel('y_label_string ') - adding y axis label to the graph 
% legend ('string1', 'string2'...)
% legend off
% grid on/off
% axis ([xmin xmax ymin ymax]) - sets the limits for the x- and y axis
% xlim ([xmin, xmax]) - sets the x axis limits in the current axes to the specified values
% ylim ([ymin, ymax])
% grid on/off - turns the current axes' grid lines on and off

%% Titles and labels can be a combination of strings and numbers
clc
figure(2)

a=0:10:360;
b=sind(a).^2;
plot(a,b)

N=2; x_unit='degrees';
xlabel(['x in  ', x_unit]) 
ylabel ('sin(x)^2_A') 
title(['graph #', num2str(N)])
%% using text in the graph
% text (x_place, y_place, 'text')
clc
x=0:0.2:2*pi;
y=sin(x);z=cos(x);
plot(x,y,x,z)
text(3.3,0,'sin(x)')
text(1.7,0,'cos(x)')
%%  hold function
% The hold function determines whether new graphics objects are added to the graph 
% or replace objects in the graph
figure(2)
x=0:5:360;
plot(x,sind(x))
hold on
plot(x,cosd(x))
hold off

figure(3)
plot(x,tand(x))
%% class_assignment_6,2
clc
close all
x1=-4:0.05:4;
x2=-2.7:0.05:2.7;
y=0.6*x1.^5-5*x1.^3+9*x1+2;
figure(4)
plot(x1,y)
figure(5)
y=0.6*x2.^5-5*x2.^3+9*x2+2;
plot(x2,y)
%% class_assignment_6,3
clc
figure(6)
x1=-10:0.1:3.7;
x2=4.3:0.1:10;
y1=1.5*x1./(x1-4);
y2=1.5*x2./(x2-4);
plot(x1,y1,x2,y2) ;
%% class_assignment_6,4
clc, 
% x^2-2x-3=0 for x=-1 and x=3
x1=-10:0.01:-1.1;
x2=-0.9:0.01:2.9;
x3=3.1:0.01:10;
y1=(x1.^2-5*x1+10)./(x1.^2-2*x1-3);
y2=(x2.^2-5*x2+10)./(x2.^2-2*x2-3);
y3=(x3.^2-5*x3+10)./(x3.^2-2*x3-3);
figure(7)
plot(x1,y1,x2,y2,x3,y3)
title('question 5'), xlabel('x'), ylabel('f(x)')
%grid on
axis([-10 10 -20 20])
% or can use : ylim ([-20 20])
legend ('-10<x<-1','-1<x<3','3<x<10')
%%  class_assignment_6,5
x=-2*pi:0.01:2*pi;
x_text=x(end);
y=3*x.*sin(x)-2*x;
yd=3*sin(x)+3*x.*cos(x)-2;
sx='x'
sy1='f(x)'
sy2='df(x)/dx'

% 
figure(8)
plot(x,y,'-',x,yd,'--')
title('question 6')
xlabel(sx)
ylabel([sy1, 'and' ,sy2])
legend(sy1,sy2)
text (x_text,y(end)-5,sy1)
text (x_text-0.5,y(end)+25,sy2)

%% subplot function
% subplot(mnp) breaks the Figure window into an m-by-n matrix of small
% figures
figure(9)
x=0:5:360;

subplot(2,2,1)
plot(x,sind(x))
title('sin')

subplot(2,2,2)
plot(x,cosd(x))
title('cos')

subplot(2,2,3)
plot(x,cotd(x))
title('cot')

subplot(2,2,4)
plot(x,tand(x))
title('tg')
%% class_assignment_6,6-7
subplot(2,1,1)
n=11;
t=0:0.1:n;
f=sqrt(n*t).*sin(t).^n;
plot(t,f,'r')
xlabel('t')
ylabel('f')
title('f(t),n=11')

%
subplot(2,1,2)
k=10;
q=0:0.1:k;
g=(q-k).*cos((2*q.^2)/k);
plot(q,g,'g')
xlabel('q')
ylabel('g')
title('g(q),k=40')



