%% Ex_5
clc;clear all;format short;format compact;close all;
%% ex5_1
clc;clear all;

h = 0:3:33 ;
D = [1.2,0.91,0.66,0.47,0.31,0.19,0.12,0.075,0.046,0.029,0.018,0.011] ;

% a)
n = 3 ;
p = polyfit(h,D, n);

% b)

hi = linspace(0,33);
yi = interp1(h,D,hi,'spline');

y_p = polyval(p,hi);

subplot(2,1,1);
plot(h,D,'bo',hi,yi,'g-');%%check this plot please !
legend('Data points','interpolation');
xlabel('h [km]');
ylabel('D [kg/m^3]');
title('standard air density estimation plot ');

subplot(2,1,2);
plot(h,D,'bo', hi,y_p,'r--');
legend('Data points','polynomial(polyval)');


%% ex5_2
clc;clear all;



R = 1.5;
h = 3 ;
n = 3 ;

t = linspace(0,300) ; % Dr Yaniv told me, it is missing

x = R*cos(2*pi*n*t/h) ;
y = R*sin(2*pi*n*t/h) ;
z = t/h ;


plot3(x,y,z);




%%  ex5_3
clc;clear all;


pyramid( 8, 3) ;
% pyramid( 15, 6) ;
% pyramid( 6, 10) ;
% pyramid( 6, 6) ;

%%  ex5_4
clc;clear all;close all;


% a)

x = linspace(-4,4);
y = linspace(-40,40);

[X, Y] = meshgrid(x,y);

z = -0.25*X.^4 + -1/6*Y.^2 ;

grid on;
colormap Autumn

subplot(2,2,1);
mesh(X,Y,z);
colorbar('location','EastOutside');

subplot(2,2,2);
surf(X,Y,z,'FaceColor','red','EdgeColor','none');
camlight left; lighting phong;
%surf(X,Y,z);
colorbar('location','EastOutside');

subplot(2,2,3);
contour3(X,Y,z);
colorbar('location','EastOutside');

subplot(2,2,4);
surfc(X,Y,z);
colorbar('location','EastOutside');


%% b)
close all;clc;clear all;

x = linspace(-180,180);
y = x ;

[X, Y] = meshgrid(x,y);

z = sind(X).^2; % sin(X).*sin(Y) = sin(X).*sin(X)

grid on;
colormap Autumn

subplot(2,2,1);
mesh(X,Y,z);
colorbar('location','EastOutside');

subplot(2,2,2);
surf(X,Y,z);
colorbar('location','EastOutside');

subplot(2,2,3);
contour3(X,Y,z);
colorbar('location','EastOutside');

subplot(2,2,4);
surfc(X,Y,z);
colorbar('location','EastOutside');



%% ex5_5
clc;clear all;close all;

f = 'x*exp(-x)-0.2'  ;
ezplot(f,[0,8]) ;
%fplot(f,[0,8]) ;

vec = [0,3] ;%assumed roots , from the previous plot.
k = 1 ;
for(i=vec)
    
    r(k)= fzero(f,i);
    k = k+1;
    
end


hold on;
plot(r,zeros(1,length(r)),'rd')
grid on;


%% ex5_6
clc;clear all;close all;

f = 'x^3-12*x^2+40.25*x-36.6' ;
ezplot(f,[0,8])
grid on;

vec = [2,6] %assumed min/max points , from the previous plot.
k = 1 ;
hold on;
for (i=vec)
    
    %can be done recursively without the k parameter.
    [xmin(k) ymin(k)] = fminsearch(f,i);
    [xmax(k) ymax(k)] = fminsearch(['-(',f,')'],i);
    k = k+1 ;
    
end


plot(xmin,ymin,'b^');
plot(xmax ,-1*ymax,'b^');


%% ex5_7
clc;clear all;close all;


% 1) using trapz()
x = linspace(0,8);
y = x.*exp(-x.^0.8)+0.2' ;
s1 = trapz(x,y)

f = 'x.*exp(-x.^0.8)+0.2';

% 2)
s2 = quad(f,0,8)
% 3)
s3 = quadl(f,0,8)



% msgbox({['using trapz :  ',num2str(s1)], ['using quad :  ',num2str(s2)]...
%     ['using quadl :  ',num2str(s3)]}, 'ex5_7');

% h = msgbox({['using trapz :  ',num2str(s1)], ['using quad :  ',num2str(s2)]...
%     ['using quadl :  ',num2str(s3)]}, 'ex5_7');
% ah = get( h, 'CurrentAxes' );
% ch = get( ah, 'Children' );
% set( ch, 'FontSize', 12 );


%% ex5_8
clc;clear all;close all;

figure(1);
% 1)
y = 'exp(x).*sin(x)-cos(x)' ;
fplot(y,[-2*pi,pi],'k-');
% grid on;
hold on;

x = linspace(-2*pi,pi,100) ; % the 100 is just for me !
y = exp(x).*sin(x)-cos(x) ;

% 2)

dx1 = diff(x);
dy1 = diff(y);
y1 = dy1./dx1 ;
xnew1 = x(1:99);
plot(xnew1, y1, '-g');


% 3)

dx2 = diff(xnew1);
dy2 = diff(y1);
y2 = dy2./dx2 ;
xnew2 = x(1:98) ;
plot(xnew2, y2, 'r-')


% % CHECK
% figure(2);
%
% f1 = 'exp(x)*sin(x) - cos(x)'
% fplot(f1,[-2*pi,pi],'b-');
% % grid on ;
%  hold on;
%
% f2 = 'sin(x)*(exp(x)+1) + exp(x)*cos(x)'
% fplot(f2,[-2*pi,pi],'g-');
%
% f3 = 'cos(x)*(2*exp(x)+1)'
% fplot(f3,[-2*pi,pi],'r-');




%% ex5_9,10
clc;clear all;close all;

%sorry i dont think i understood this ex!!
%if it is not hard for you can you please please write your remarks here
%i will not tell or show any one and this is the last assignment....
%thank you very much!!


% -------
x = linspace(-pi,pi,10000);
y = exp(x./2).*sin(x) - x./2 ;
s1 = trapz(x,y)

f = 'exp(x./2).*sin(x) - x./2';
s2 = quad(f,-pi,pi)
tic
s3 = quadl(f,-pi,pi)
toc
% -------
disp('------------------');

res1 = integral_1(y,x)
res2 = integral_2(y,x)




































