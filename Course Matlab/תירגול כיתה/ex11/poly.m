function [ ] = poly(n,k)
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here

r = 50 ;
theta = 0:(2*pi)/(n+1):(2*pi);


for (i=1:k)
    
    x = r.*cos(theta);
    y = r.*sin(theta);
    hold on;
    plot(x,y);
    r = r-15 ;
    
    
    
end%for










end

