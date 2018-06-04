function minsara2(n,b,h,r)
teta=linspace(0,2*pi,n+1);
x=r*cos(teta);
y=r*sin(teta);
z=ones(1,n+1)*b;
plot3(x,y,z)
hold on
z1=z+h;
plot3(x,y,z1)

for i=1:n
    plot3([x(i) x(i)], [y(i) y(i)],[z(i) z1(i)]);
end

grid on
hold off
    