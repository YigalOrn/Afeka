function [  ] = func5( x,c,b )

%The functions plots a graph from the given arguments and
%the equation y = sin(cx) *e^(-by)

figure(5);

y = sin(c*x).*exp(-b*x) ;

plot(x,y,'m');
xlabel('x');
ylabel('sin(c*x).*exp(-b*x)');


end

