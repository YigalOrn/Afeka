function [ cVec ] = FtoC( fVec )

% °C  x  9/5 + 32 = °F
% 
% (°F  -  32)  x  5/9 = °C


cVec = (fVec - 32)*(5/9) ;


end

