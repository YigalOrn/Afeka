%% ex11
clc;clear all;close all;format compact;format long;

%% 
clc;

x = linspace(1,50);
y = linspace(-50,50);
p = polyfit(x,y,4);



%% 3
clc;

x = [-5 ,-4 ,-2.2,-1  ,0    ,1  ,2.2,4  ,5  ,6  ,7];
y = [0.1,0.2,0.8 ,2.6 ,3.9  ,5.4,3.6,2.2,3.3,6.7,8.9];


figure(3)

p1 = polyfit(x,y,1);%this is a proximity
x1 = -10:0.001:10 ;
y1 = polyval(p1,x1);%same polynomial with more points!
subplot(2,1,1);
plot(y1);

res1 = y(find(x==2.2))-polyval(p1,2.2)


p3 = polyfit(x,y,4);
x3 = 0:0.001:10 ;
y3 = polyval(p3,x3);
subplot(2,1,2);
plot(y3);
grid on ;
%axis([-10,10,-10,10]);

y(find(x==2.2))
polyval(p3,2.2)

res3 = y(find(x==2.2))-polyval(p3,2.2)

%%
clc;close all;

x=[1 2 3 3.5 4 4.1];
y=[1 0.5 1.5 1.3 0.55 -1];
xi=3.5:0.001:3;
yi=interp1(x,y,xi);
hold on;
plot(x,y,'m');
plot(xi,yi,'r');


%%
clc;close all;


t = 0:0.04:0.6;
ecg = [-0.244,-0.2284,-0.2108,-0.131,-0.402,-0.0342,-0.1046,...
    -0.153,-0.1886,-0.1956,-0.1938,-0.1864,...
    -0.1456,-0.1108,-0.2252,-0.2368];


plot(t,ecg,'or');


p = polyfit(t,ecg,8);

t_i = linspace(0,0.6,60);

y = polyval(p,t_i);

hold on;

plot(t_i,y,'m');

ecg_i = interp1(t,ecg,t_i,'spline');
plot(t_i,ecg_i,'g')



%% 5
clc;close all;

x = linspace(0,5,50);
y = rand(1,50)*(20-0)+0 ;

y = sort(y,'ascend');

plot(x,y,'ob');

p = polyfit(x,y,1);

Pp = polyval(p,2.5);

res = min( abs(y-Pp) );

%
xi = 0:0.1:5;

Pi = interp1(x,y,xi,'spline');

hold on;
plot(xi,Pi);



%%
clc;clear all;close all;format compact;format long;


polyGonDraw(5,10);

% polyGonDraw(8,80);


















