function [Y_hat_test_SVM] = my_svm_1(Z_train, Y_train, Z_test)
%
%

    svmstruct = svmtrain(Z_train, Y_train);
    Y_hat_test_SVM = svmclassify(svmstruct, Z_test);

end

