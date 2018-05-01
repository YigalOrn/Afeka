function [Y_hat_test] = my_logistic_regression(Z_train, Y_train, Z_test)
%
%

    % train using logistic regression: Z_train/Y_train
    LR_coeff = glmfit(Z_train, Y_train, 'binomial', 'logit');
    % predict using logistic regression: Z_test/Y_test
    % notice: logistic regression predicts probabilities
    Y_hat_test = glmval(LR_coeff, Z_test,'logit');


end

