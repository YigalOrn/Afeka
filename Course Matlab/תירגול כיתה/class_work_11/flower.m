
function flower(n,R,r)

teta=linspace(0,2*pi);
x=R*cos(teta);
y=R*sin(teta);
plot(x,y,'g*-')
hold on
axis square
for alpha=linspace(0,2*pi,n+1)
    x1=(R+r)*cos(alpha)+r*cos(teta);
      y1=(R+r)*sin(alpha)+r*sin(teta);
      plot(x1,y1,'r*-')
end
hold off

