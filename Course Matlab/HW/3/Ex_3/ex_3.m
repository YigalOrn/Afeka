%% ex_1
format compact;
close all;
clc;

x = -300:0.001:300 ;
y= 693.8 - 68.8*cosh(x./999.7) ;

figure(1);
plot(x,y,'--k');
title('ex_1 graph');

%% ex_2
close all;
clc;

R = 4;   %omega
V = 12; %volt
L = 1.7;%...inductor

figure(2);

t1 = 0:0.00001:0.5 ;
i1 = (V/R)*(1-exp((-R*t1)./L) ) ;

t2 = 0.5:0.0001:2;
i2 = exp((-R*t2)./L)*(  (V/R)*(exp((0.5*R)/L)-1)  );

plot(t1,i1,'--r', t2,i2,':k');
legend('i1','i2');
xlabel('t in sec');
ylabel('i ( t ) in ampers');

%% ex_3

close all;
clc;

figure(3);

a0 = 52.92*(1e-11) ; 
lowerLim = 0 ;
higherLim = a0*15 ;
r = linspace(lowerLim, higherLim) ;
p = (1/(8*a0))*(r/a0).^2.*(2-r./a0).*exp(-r/a0) ;

plot(r,p,'m');
xlabel('r');
ylabel('p ( r )');


%% ex_4

% a)
close all;
clc;

x = -30:0.001:30;

figure(4);

subplot(2,2,1);
y = 7*x.^3 + 5*x.^2  + 7*x ;
plot(x,y,'b');
xlabel('x');
ylabel('f ( x )');

subplot(2,2,2);
y1 = 21*x.^2 + 10*x +7 ;
plot(x,y);
plot(x,y1,'r');
xlabel('x');
ylabel('f(1)( x )');

subplot(2,2,3);
y2 = 42*x + 10 ;
plot(x,y);
plot(x,y2,'g');
xlabel('x');
ylabel('f(2)( x )');
%xlim([-30,30])


% b)

close all;
clc;

t = linspace(0,7);

figure(4);

subplot(3,1,1);
x = 0.4*t.^3 - 2*t.^2 - 5*t +13 ;
plot(t,x,'b');
xlabel('t');
ylabel('x ( t ) in m');

subplot(3,1,2);
v = 1.2*t.^2 - 4*t -5 ;
plot(t,v);
plot(t,v,'r');
xlabel('t');
ylabel('v ( t ) in  m/s');

subplot(3,1,3);
a = 2.4*t - 4 ;
plot(t,a);
plot(t,a,'g');
xlabel('t');
ylabel('a ( t ) in m/s^2');

%% ex_5

close all;
clc;

x = linspace(-36,36);
y = x ;
c = 0.05 ;
b = 3 ;

func5(x,c,b);


%% ex_6
close all;
clc;


[x,y] = maxmin(3, -18, 48);
disp(['The local extremum has the coor.  (',num2str(x),',',num2str(y),')']);

[x,y] = maxmin(-5, 10, -3);
disp(['The local extremum has the coor.  (',num2str(x),',',num2str(y),')']);


%% ex_7
close all;
clc;

distance = PtoLdist(2,-4,-2,3.5,-6)
distance = PtoLdist(11,2,-2,1,-6)

%% ex_8
close all;
clc;

%FtoC plots and does he math , 
%help only present info about the FtoC
%Remark - Dr Yaniv told me how it should be i.e what every function should
%do...
%nevertheless it works and the order is incorrect not the logic.

monthvec = 1:12 ;
lowTempInF    = [49,48,51,54,63,67,70,72,69,59,54,47] ;
highTempInF = [65,66,69,72,77,83,86,86,89,83,76,66] ;

 help(monthvec, lowTempInF , highTempInF);




%% ex_9
close all;
clc;

n = randint(1,49)
n = randint(-35,-2)


%% ex_10
close all;
clc;
format compact ;

 [ maxHeight,  maxDis ] = projectile(230, 39) ;%( [m/s],  [degree] )

%[ maxHeight,  maxDis ] = projectile(150, 90) ;










