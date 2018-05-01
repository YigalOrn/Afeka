function [X_train, X_test, Y_train, Y_test] = train_test_division(X, Y, bin_indices, i)
% i: a number in a bin, according to current cross-valid' iter'
%

    % calc logical train/test indices of X
    test_indices = (bin_indices == i);
    train_indices = ~test_indices;

    % do the division accordingly
    X_test  = X(test_indices, :);
    X_train = X(train_indices, :);

    Y_test = Y(test_indices);
    Y_train = Y(train_indices);

end

