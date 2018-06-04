function [  ] = diamondGlamour( k )

%
%

angle = ( ( (2*pi)-(k*pi/25) )/k )+(pi/50);
theta = 0:angle:(2*pi-angle);

r1 = 12 ;
r2 = 11 ;
r3 = 10 ;

hold on;

for (i=theta)%should run k-times
    
    % xu , yu - are the coordinate
    %for the upper vertex of the upper triangle
    
    % xl , yl - are the coordinate
    %for the left vertex of the  triangle
    
    
    % xr , yr - are the coordinate
    %for the right vertex of the  triangle
    
    
    xu = r2*cos( i+(pi/50) );
    yu = r2*sin( i+(pi/50) );
    
    xl = r3*cos( i );
    yl = r3*sin( i );
    
    xr = r1*cos( i );
    yr = r1*sin( i );
    
    
    % xb , yb - are the coordinate
    %for the bottom vertex of the bottom triangle
    
    
    xb = r2*cos( i-(pi/50) );
    yb = r2*sin( i-(pi/50) );
    
    
    %uper triangle
    plot([xu,xr],[yu,yr])
    plot([xu,xl],[yu,yl])
    
    
    %bottom triangle
    plot([xb,xr],[yb,yr])
    plot([xb,xl],[yb,yl])
    
    title(['k = ',num2str(k)]);
    
end%for

hold off ;


end%func

