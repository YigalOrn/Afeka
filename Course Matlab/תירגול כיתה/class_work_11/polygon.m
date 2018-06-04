function polygon(n,k)
teta=linspace(0,2*pi,n+1);
for i=1:k
x=i*cos(teta);
y=i*sin(teta);
plot(x,y)
hold on
end
hold off
