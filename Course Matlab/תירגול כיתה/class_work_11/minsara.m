function minsara(n,h)
teta=linspace(0,2*pi,n+1)


x=cos(teta);
y=sin(teta)
z=zeros(1,n+1);
s='krm'
plot3(x,y,z)
hold on
z1=z+h;
plot3(x,y,z1)

for i=1:n
    plot3([x(i) x(i)], [y(i) y(i)],[z(i) z1(i)])
   
end

grid on
hold off
    