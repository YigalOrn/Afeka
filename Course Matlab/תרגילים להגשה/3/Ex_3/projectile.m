function [ maxHeight,  maxDis ] = projectile( initialVelocityVec,  angle )

%Notice - there is an equetion for the projectile path, i did not use it

% initialVelocityVec
% angle

%calculated data
g = 9.8 ;
tMax = ( initialVelocityVec*sind(angle)  )/g ;
tTot = 2*tMax ;

% outputs
maxHeight = 0 +  (  ( initialVelocityVec*sind(angle)  )*tMax )...
    - ( 0.5*g*(tMax^2) )

maxDis = ( initialVelocityVec*cosd(angle)  )*tTot


%projectile plot


xForMaxHeight = ( initialVelocityVec*cosd(angle)  )*tMax ; %for text
xMax =  ( initialVelocityVec*cosd(angle)  )*tTot; %for text

figure(10) ;

t = linspace(0, tTot) ;

y = 0 +  (  ( initialVelocityVec*sind(angle)  )*t )...
    - ( 0.5*g*(t.^2) ) ;
x = ( initialVelocityVec*cosd(angle)  )*t ;

plot(x,y,'-m');

xlabel('x ( t ) - distance');
ylabel('y ( t ) - height');
text(xForMaxHeight, maxHeight,...
    ['(x,yMax) = ','( ', num2str(xForMaxHeight),' , ',num2str(maxHeight),' )']) ;

text(xMax-1000, 100,...
    ['xMax = ', num2str(xMax)]) ;



end

