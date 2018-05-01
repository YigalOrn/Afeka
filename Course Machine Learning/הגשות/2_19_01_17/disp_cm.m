function disp_cm(CM, i, title_str)
%
%   
% https://www.mathworks.com/help/nnet/ref/plotconfusion.html
% plotconfusion(Y_test,round(Y_hat_test));
    
    disp([title_str, num2str(i)]);
    disp(CM);
    
end

