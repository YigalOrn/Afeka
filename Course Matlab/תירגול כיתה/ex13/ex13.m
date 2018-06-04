%%  ex13
clc;clear all;close all;format short;format compact

%%
clc;clear all;close all;


f  = 'sin(x)*exp(0.1*x)' ;
fplot(f,[-6,6]);
grid on;

%% ex12_1


y = 'cos(x)-2*x^3' ;
fplot(y,[-2*pi,2*pi]);
grid on;
xh = fzero(y, 0) ;
hold on;
plot(xh,0,'ro');


%% ex12_2
clc;clear all;close all;

y = '2*sin(x)-x^(0.5)+2.5' ;
fplot(y,[1,10]) ;
grid on;
hold on ;
x1 = fzero(y,3);
x2 = fzero(y,6);
x3 = fzero(y,9);
plot([x1,x2,x3],[0,0,0],'ro');

%% ex12_3
clc;

[xmin1 ymin1] = fminsearch(y,4) ;
plot(xmin1,ymin1,'go')
text(xmin1+0.5,ymin1,'MIN')

[xmax2 ymax2] = fminsearch(['-(',y,')'],8) ;
plot(xmax2,-1*ymax2,'go')

%%
clc;clear all;close all;

x = linspace(0,2*pi) ;
y = x.*sin(x) ;

plot(x,y,'k','LineWidth', 3)
xlim([0,2*pi]) ;
grid on;

dy_dx = diff(y)./diff(x);
xnew =  linspace(0,2*pi,99) ;
hold on;
plot(xnew,dy_dx,'LineWidth', 5);

dy = sin(xnew)+xnew.*cos(xnew) ;
plot(xnew,dy,'g')

%%
clc;clear all;close all;
x = 0:pi/4:pi ;
y = sin(x) ;

s1 = trapz(x,y)
ys = 'sin(x)' ;
s2 = quad(ys,0,pi)
s3 = quad(ys,0,pi)

%%
clc;clear all;close all;

ys ='1./(0.8*x.^2+0.5*x+2)';
x = linspace(0,5,20); % n=100 makes them equal!
y = 1./(0.8*x.^2+0.5*x+2);% 1./ <<<-------------
s1 = trapz(x,y)
s2 = quad(ys,0,5)

%% 4
clc;clear all;close all;

f = 'x.^(0.5)+5*sin(x)';
fplot(f,[1,14],'b-')
grid on;
xlim([1,14]);
x = linspace(1,14);

s = quad(f,1,14) ;
disp(['The area is  ',num2str(s)]);

t = [0,4,5,9,12];
k = 1;
% vec = []
for i=t
    
    % vec = [vec ,fzero(f,i) ] ;
    vec(k) = fzero(f,i);
    k = k+1;
end

hold on;
plot(vec,zeros(1,length(vec) ) ,'ro');


t = [1,4,8];
k = 1;
for i=t
    
    [xmin(k), ymin(k)] = fminsearch(f,i) ;
    [xmax(k), ymax(k)] = fminsearch( ['-(',f,')'],i) ;
    k=k+1 ;
end

plot(xmin,ymin,'mo', xmax,-1*ymax,'gs')

x = linspace(1,14) ;
y = x.^(0.5)+5*sin(x) ;

dy_dx = diff(y)./diff(x) ;
xnew =  linspace(1,14,99) ;
plot(xnew,dy_dx,'r-');


%% 5
clc;clear all;close all;

f = 'sin(x)' ;
fplot(f,[0,2*pi],'r-')
grid on ;
 a = 0 ;
  b = 2*pi ;
 [vecx, nx] = uniqsol(f,a,b) 
 % some point can be the same because of the round func!


