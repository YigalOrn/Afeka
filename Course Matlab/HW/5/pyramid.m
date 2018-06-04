function [] = pyramid( k, h )

%
%

%first we draw a polygon using the Gauss method i.e with the aid of a circle
R = 3 ;
theta = linspace(0,2*pi,k+1) ;

x1 = R*cos(theta);
y1 = R*sin(theta);
len = length(x1) ;
z1 = zeros(1,len);

%plot the base
plot3(x1,y1,z1);

%create the top coordinates
x2 = zeros(1,len);
y2 = zeros(1,len);
z2 =ones(1,len)*h ;

hold on ;
grid on;
%connect the base with the pyramid top
for (i=1:len)
    
    plot3([x1(i), x2(i)],[y1(i),y2(i)],[z1(i),z2(i)] );
    
end

hold off ;

end

