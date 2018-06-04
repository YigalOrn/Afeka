function [] =help( monthvec, lowTempInF , highTempInF )


 lowTempInC  = FtoC(lowTempInF) ;
 highTempInC = FtoC(highTempInF) ;

 figure(8) ;
 
 plot(monthvec,lowTempInC,'-b',monthvec,highTempInC,'-r' )
 xlabel('month');
 ylabel('temp in °C');
xlim([1,12]);
legend('lowTempInC', 'highTempInC');
grid on ;
title('Tel-Aviv Temp Chart');
text(2,8,'Cool');


end

