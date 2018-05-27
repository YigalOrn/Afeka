%% primary plot
clc;
close all;
clear all;

hold on;
figure(1);

title('primary graph');
xlabel('x1');
ylabel('x2');
grid on;
axis([-7, 7, -7,7]);

%---------------------------
y = linspace(-7, 7);
x = zeros(1, 100);
plot(x, y, '-k', 'LineWidth', 3);


x = linspace(-7, 7);
y = zeros(1, 100);
plot(x, y, '-k', 'LineWidth', 3);

%---------------------------


% 1 constraint
x1 = linspace(-4,6);
x2 = x1;
plot(x1, x2, '-k');

% 2 constraint
x1 = linspace(-4,6);
x2 = -2*x1+2;
plot(x1, x2, '-k');

% 3 constraint
% x1 = linspace(-4,4);
% x2 = x1+1;
% plot(x1, x2, '-k');

% 4 constraint
% x1 = linspace(-2,4);
% x2 = x1-1;
% plot(x1, x2, '-k');


% % fill the feasible solutions area
% verx = [1,2];
% very = [0,1];
% fill(verx, very,'y');

%line fill
% x1 = linspace(-2,2);
% x2 = x1-1;
% plot(x1, x2, '-y','LineWidth',5);
%infinity cont.
% x1 = linspace(-4,-2);
% x2 = x1-1;
% plot(x1, x2, '--y','LineWidth',3);


% add vertices to graph
%text(1, -0.5, '(1, 0)', 'color', 'r' );
text(2/3, 2/3+0.5, '(2/3,2/3)', 'color', 'r' );


%circle them
%plot(1,0, 'ro')
plot(2/3,2/3, 'ro')

% arrowline([3,5],[-2,-1]);


% add line details to graph
% text(0.3, 9.8, 'm=(-2)', 'color', 'b' );
% text(0.3, 5.8, 'm=(-1)', 'color', 'b' );





%----------------------------------------
% 1)

% 1.a

% z = 0;
% d = 0.5;
% c = ( 1/(1-d) )*z;
% m = (-d)/(1-d);
% x = linspace(-7,7);
% y = m*x+c;
% plot(x, y, '--m');
% 
% 
% z = 1;
% d = 0.5;
% c = ( 1/(1-d) )*z;
% m = (-d)/(1-d);
% x = linspace(-7,7);
% y = m*x+c;
% plot(x, y, '--m');
% 
% 
% 
% z = 3;
% d = 0.5;
% c = ( 1/(1-d) )*z;
% m = (-d)/(1-d);
% x = linspace(-7,7);
% y = m*x+c;
% plot(x, y, '--m');
% 
% 
% 
% 
% z = 5;
% d = 0.5;
% c = ( 1/(1-d) )*z;
% m = (-d)/(1-d);
% x = linspace(-7,7);
% y = m*x+c;
% plot(x, y, '--m');
% 
% 
% 
% 
% z = -4;
% d = 0.5;
% c = ( 1/(1-d) )*z;
% m = (-d)/(1-d);
% x = linspace(-7,7);
% y = m*x+c;
% plot(x, y, '--m');



%1.b
% 
% z = 1;
% d = 1/10;
% c = ( 1/(1-d) )*z;
% m = (-d)/(1-d);
% x = linspace(-7,7);
% y = m*x+c;
% plot(x, y, '--m');
% 
% 
% 
% z = 2;
% d = 1/10;
% c = ( 1/(1-d) )*z;
% m = (-d)/(1-d);
% x = linspace(-7,7);
% y = m*x+c;
% plot(x, y, '--m');
% 
% 
% 
% z = 5;
% d = 1/10;
% c = ( 1/(1-d) )*z;
% m = (-d)/(1-d);
% x = linspace(-7,7);
% y = m*x+c;
% plot(x, y, '--m');
% 

%1.c


% z = 0;
% d = 0;
% c = ( 1/(1-d) )*z;
% m = (-d)/(1-d);
% x = linspace(-7,7);
% y = m*x+c;
% plot(x, y, '--m');
% 
% z = 2;
% d = 0;
% c = ( 1/(1-d) )*z;
% m = (-d)/(1-d);
% x = linspace(-7,7);
% y = m*x+c;
% plot(x, y, '--m');
% 
% 
% 
% z = 3;
% d = 0;
% c = ( 1/(1-d) )*z;
% m = (-d)/(1-d);
% x = linspace(-7,7);
% y = m*x+c;
% plot(x, y, '--m');
% 
% 
% 
% z = 5;
% d = 0;
% c = ( 1/(1-d) )*z;
% m = (-d)/(1-d);
% x = linspace(-7,7);
% y = m*x+c;
% plot(x, y, '--m');








% 2


% 2.a

% z = 0;
% d = 0.5;
% c = ( 1/(1-d) )*z;
% m = (-d)/(1-d);
% x = linspace(-7,7);
% y = m*x+c;
% plot(x, y, '--m');
% 
% z = 2;
% d = 0.5;
% c = ( 1/(1-d) )*z;
% m = (-d)/(1-d);
% x = linspace(-7,7);
% y = m*x+c;
% plot(x, y, '--m');
% 
% 
% 
% z = 5;
% d = 0.5;
% c = ( 1/(1-d) )*z;
% m = (-d)/(1-d);
% x = linspace(-7,7);
% y = m*x+c;
% plot(x, y, '--m');

% 2.b

% 
% z = 0;
% d = 8/9;
% c = ( 1/(1-d) )*z;
% m = (-d)/(1-d);
% x = linspace(-7,7);
% y = m*x+c;
% plot(x, y, '--m');
% 
% 
% 
% z = 2;
% d = 8/9;
% c = ( 1/(1-d) )*z;
% m = (-d)/(1-d);
% x = linspace(-7,7);
% y = m*x+c;
% plot(x, y, '--m');
% 
% 
% 
% 
% z = 4;
% d = 8/9;
% c = ( 1/(1-d) )*z;
% m = (-d)/(1-d);
% x = linspace(-7,7);
% y = m*x+c;
% plot(x, y, '--m');
% 
% 
% z = 6;
% d = 8/9;
% c = ( 1/(1-d) )*z;
% m = (-d)/(1-d);
% x = linspace(-7,7);
% y = m*x+c;
% plot(x, y, '--m');



% 2.c

% x = ones(1, 100)*2;
% y = linspace(-7,7);
% plot(x, y, '--m');
% 
% x = ones(1, 100)*4;
% y = linspace(-7,7);
% plot(x, y, '--m');
% 
% 
% x = ones(1, 100)*1;
% y = linspace(-7,7);
% plot(x, y, '--m');
% 
% x = ones(1, 100)*5;
% y = linspace(-7,7);
% plot(x, y, '--m');
% 
% 
% x = ones(1, 100)*6;
% y = linspace(-7,7);
% plot(x, y, '--m');









% 3

% 3.a


% z = -1;
% d = -1/3;
% c = ( 1/(1-d) )*z;
% m = (-d)/(1-d);%0.25
% x = linspace(-7,7);
% y = m*x+c;
% plot(x, y, '--m');
% 
% 
% z = 0;
% d = -1/3;
% c = ( 1/(1-d) )*z;
% m = (-d)/(1-d);
% x = linspace(-7,7);
% y = m*x+c;
% plot(x, y, '--m');
% 
% 
% z = 2;
% d = -1/3;
% c = ( 1/(1-d) )*z;
% m = (-d)/(1-d);
% x = linspace(-7,7);
% y = m*x+c;
% plot(x, y, '--m');
% 
% 
% 
% z = 6;
% d = -1/3;
% c = ( 1/(1-d) )*z;
% m = (-d)/(1-d);
% x = linspace(-7,7);
% y = m*x+c;
% plot(x, y, '--m');




% 3.b

% 
% z = -100;
% d = -20;
% c = ( 1/(1-d) )*z;
% m = (-d)/(1-d);
% x = linspace(-7,7);
% y = m*x+c;
% plot(x, y, '--m');
% 
% z = -50;
% d = -20;
% c = ( 1/(1-d) )*z;
% m = (-d)/(1-d);
% x = linspace(-7,7);
% y = m*x+c;
% plot(x, y, '--m');
% 
% z = -1;
% d = -20;
% c = ( 1/(1-d) )*z;
% m = (-d)/(1-d);
% x = linspace(-7,7);
% y = m*x+c;
% plot(x, y, '--m');
% 
% 
% z = 0;
% d = -20;
% c = ( 1/(1-d) )*z;
% m = (-d)/(1-d);
% x = linspace(-7,7);
% y = m*x+c;
% plot(x, y, '--m');
% 
% 
% z = 2;
% d = -20;
% c = ( 1/(1-d) )*z;
% m = (-d)/(1-d);
% x = linspace(-7,7);
% y = m*x+c;
% plot(x, y, '--m');
% 
% 
% 
% z = 6;
% d = -20;
% c = ( 1/(1-d) )*z;
% m = (-d)/(1-d);
% x = linspace(-7,7);
% y = m*x+c;
% plot(x, y, '--m');
% 
% 
% z = 60;
% d = -20;
% c = ( 1/(1-d) )*z;
% m = (-d)/(1-d);
% x = linspace(-7,7);
% y = m*x+c;
% plot(x, y, '--m');
% 
% 
% 
% z = 120;
% d = -20;
% c = ( 1/(1-d) )*z;
% m = (-d)/(1-d);
% x = linspace(-7,7);
% y = m*x+c;
% plot(x, y, '--m');

% 3.c
% z = -1;
% d = 0;
% c = ( 1/(1-d) )*z;
% m = (-d)/(1-d);
% x = linspace(-7,7);
% y = m*x+c;
% plot(x, y, '--m');
% 
% 
% z = 0;
% d = 0;
% c = ( 1/(1-d) )*z;
% m = (-d)/(1-d);
% x = linspace(-7,7);
% y = m*x+c;
% plot(x, y, '--m');
% 
% 
% z = 2;
% d = 0;
% c = ( 1/(1-d) )*z;
% m = (-d)/(1-d);
% x = linspace(-7,7);
% y = m*x+c;
% plot(x, y, '--m');
% 
% 
% 
% z = 6;
% d = 0;
% c = ( 1/(1-d) )*z;
% m = (-d)/(1-d);
% x = linspace(-7,7);
% y = m*x+c;
% plot(x, y, '--m');




% 4


% 4.a


% 
% z = -10;
% d = 2;
% c = ( 1/(1-d) )*z;
% m = (-d)/(1-d);
% x = linspace(-7,7);
% y = m*x+c;
% plot(x, y, '--m');
% 
% z = -1;
% d = 2;
% c = ( 1/(1-d) )*z;
% m = (-d)/(1-d);
% x = linspace(-7,7);
% y = m*x+c;
% plot(x, y, '--m');
% 
% 
% z = 0;
% d = 2;
% c = ( 1/(1-d) )*z;
% m = (-d)/(1-d);
% x = linspace(-7,7);
% y = m*x+c;
% plot(x, y, '--m');
% 
% 
% z = 2;
% d = 2;
% c = ( 1/(1-d) )*z;
% m = (-d)/(1-d);
% x = linspace(-7,7);
% y = m*x+c;
% plot(x, y, '--m');
% 
% 
% 
% z = 6;
% d = 2;
% c = ( 1/(1-d) )*z;
% m = (-d)/(1-d);
% x = linspace(-7,7);
% y = m*x+c;
% plot(x, y, '--m');
% 
% 
% z = 8;
% d = 2;
% c = ( 1/(1-d) )*z;
% m = (-d)/(1-d);
% x = linspace(-7,7);
% y = m*x+c;
% plot(x, y, '--m');



% 4.b



% z = -26;
% d = 5;
% c = ( 1/(1-d) )*z;
% m = (-d)/(1-d);
% x = linspace(-7,7);
% y = m*x+c;
% plot(x, y, '--m');
% 
% z = -23;
% d = 5;
% c = ( 1/(1-d) )*z;
% m = (-d)/(1-d);
% x = linspace(-7,7);
% y = m*x+c;
% plot(x, y, '--m');
% 
% z = -20;
% d = 5;
% c = ( 1/(1-d) )*z;
% m = (-d)/(1-d);
% x = linspace(-7,7);
% y = m*x+c;
% plot(x, y, '--m');
% 
% z = -1;
% d = 5;
% c = ( 1/(1-d) )*z;
% m = (-d)/(1-d);
% x = linspace(-7,7);
% y = m*x+c;
% plot(x, y, '--m');
% 
% 
% z = 0;
% d = 5;
% c = ( 1/(1-d) )*z;
% m = (-d)/(1-d);
% x = linspace(-7,7);
% y = m*x+c;
% plot(x, y, '--m');
% 
% 
% z = 2;
% d = 5;
% c = ( 1/(1-d) )*z;
% m = (-d)/(1-d);
% x = linspace(-7,7);
% y = m*x+c;
% plot(x, y, '--m');
% 
% 
% 
% z = 6;
% d = 5;
% c = ( 1/(1-d) )*z;
% m = (-d)/(1-d);
% x = linspace(-7,7);
% y = m*x+c;
% plot(x, y, '--m');
% 
% 
% z = 8;
% d = 5;
% c = ( 1/(1-d) )*z;
% m = (-d)/(1-d);
% x = linspace(-7,7);
% y = m*x+c;
% plot(x, y, '--m');

























