function [Y_hat_test_kernel_SV] = my_kernel_svm(Z_train, Y_train, Z_test )
%
%
    % in the most crude way!!
    % imagine a gaussian bell graph i.e. a gaussian probabillity..
    % for each point we set 

    svmstruct = svmtrain(Z_train, Y_train, 'kernel_function', 'rbf');
    %svmstruct = svmtrain(Z_train, Y_train, 'kernel_function', 'rbf', 'rbf_sigma', 3);
    Y_hat_test_kernel_SV = svmclassify(svmstruct, Z_test);
 
end

