function [  ] = stairs( x0,y0,xf,yf )
%
%

%***************************************************


%DEBUG ONLY
% disp('********************');
% x0
% y0
% xf
% yf
% disp('********************');

figure(6);
hold on;

leftEdgeX = [x0,x0];
% leftEdgeY = [x0,yf];
leftEdgeY = [y0,yf];


rightEdgeX = [xf,xf];
rightEdgeY = [y0,yf];

upperEdgeX = [x0,xf] ;
upperEdgeY = [yf,yf];

bottomEdgeX = [x0,xf] ;
bottomEdgeY = [y0,y0] ;


%leftEdge
plot(leftEdgeX,leftEdgeY,'m');
%rightEdge
plot(rightEdgeX,rightEdgeY,'m');
%upperEdge
plot(upperEdgeX,upperEdgeY,'m');
%bottomEdge
plot(bottomEdgeX,bottomEdgeY,'m');


%DEBUG ONLY
% grid on ;
% xlim([-15,15]);
% ylim([-15,15]);


end

%***************************************************



