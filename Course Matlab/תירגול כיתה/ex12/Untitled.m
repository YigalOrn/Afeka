%%12
clc;clear all;format compact;
%% ex1

t = 0:0.1:20 ;
x = (2+4*cos(t)).*cos(t) ;
y =  (2+4*cos(t)).*sin(t) ;
z = t.^2 ;

plot3(x,y,z);

xlabel('x');
ylabel('y');
zlabel('z');


%%

x = 0:0.2:4;
y = 0:0.2:5;
[x1,y1] = meshgrid(x,y)

z = -(x1.^2+y1.^2)/4 ;
mesh(x1,y1,z);

%%
x = linspace(-pi,pi);
y=x;

[x1,y1] = meshgrid(x);
z = sin(x1).*y1.^3;
%  mesh(x1,y1,z);
% surf(x1,y1,z);

contour3(x1,y1,z,50)
surfc(x1,y1,z)

xlabel('x');
ylabel('y');
zlabel('z');


%%


x = linspace(-90,90);
y = x ;


[x1,y1] = meshgrid(x) ;
z = sind( (x1.*y1)/50).^2+(2*exp(-(x1.^2+y1.^2)/1500) ) ;

mesh(x1,y1,z);
surf(x1,y1,z);
%
% contour3(x1,y1,z,50);
% surfc(x1,y1,z);
% view()% (az,el) or ([x,y,z])




%%

x = [0,1,1,0,0];
y = [0,0,1,1,0];
z = zeros(1,5);

plot3(x,y,z)
hold on
z1 = z+1 ;
plot3(x,y,z1)

plot3([0,0],[0,0],[0,1]);
plot3([0,0],[1,1],[0,1]);



%%


m = 8;



for k=1:15
    r = 50 ;
    theta = 0:(2*pi)/(m+1):(2*pi);
    
    
    x = (r-k).*cos(theta);
    y =  (r-k).*sin(theta);
    
    
    
    z = zeros(1,length(x))+k ;
    plot3(x,y,z)
    hold on;
    z1 = k+z+15 ;
    plot3(x,y,z1)
    
    plot3([x,x],[y,y],[z,z1]);
    
    for i = 1:m+1
        
        plot3([x(i),x(i)],[y(i),y(i)],[z(i),z1(i)]);
        
    end
    
    
end%outer for

%%
subplot(2,1,1)
fplot('1/x + 1/(x-2)',[0,2*pi],'m')
subplot(2,1,2)
ezplot('1/x + 1/(x-2)',[0,2*pi])


%%

fplot('[sin(x), cos(x)]',[0,2*pi])

%%

fplot('sin(x)', [0,2*pi])
vec = fzero('sin(x)', (pi/2) )

grid on;






















