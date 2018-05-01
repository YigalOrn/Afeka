function [Y_hat_test_kernel_SV] = my_svm_2(Z_train, Y_train, Z_test )
%
%

    % https://www.mathworks.com/help/stats/fitcsvm.html?requestedDomain=www.mathworks.com
    % https://www.mathworks.com/help/stats/support-vector-machines-for-binary-classification.html
    SVMModel = fitcsvm(Z_train,Y_train);
    Y_hat_test_kernel_SV = predict(SVMModel, Z_test);
    
end

