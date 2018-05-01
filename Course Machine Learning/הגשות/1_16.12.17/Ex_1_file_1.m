%%
clc; clear all; close all; format compact;

%%
% This data was download from UCI, it is named “Energy efficiency Data Set”. 
% Originally there are two variables to be predicted – y_1 and y_2, here we only use y_1. 
% Originally there were 768 data rows, here we only use 760 rows.

% I downloaded this data set again!, 
% I also edited it to fit the above description!

data_set = csvread('UCI_ENB2012_data.csv');

%%
% Split the data into X and Y the following way:
X = data_set(1:760, 1:8);
Y = data_set(1:760, 9);

[rowsX, colsX] = size(X);

%%
% https://www.youtube.com/watch?v=TIgfjmp-4BA
% Neta's Class Lab

% 1) Use a 10-fold cross validation to split the data into train and test.
k = 10;
bin_size = rowsX/k;

% create indices for cross validation.
% every kth bin will have indices 1 to k.
% in the following for loop, we take from each bin: 
% the i-th index for the test set and
% any other index for the train set
% meaning that upon completion we have used all data alternatly for train and test. 

% what is the purpose of the k-fold cross validation ?
% we could assume we are given a data-set from some company that wish to
% make predictions from the learning of this data and we are asked to tell 
% them in what certainty in percent we could predict...
% we always separate the data set to train and test sets... 
% but what if the first seperation gave us: very "comfortobale" points in
% train and very "hard" points in test...?
% and we can think on any combination: {train easy/test easy, train hard/test easy, etc...}
% the certainty in percent of our predictions could be wrong!
% doing the k-fold cross-validation we can check each such train-test pair
% and conclude bounds on our certainty in percent of our predictions !!!


bin_indices = crossvalind('kfold', rowsX, k);

results = ones(k, 3);

for i=1:k
    
    % returns actuall indices in X where there is a match in the bin_indices and
    % i
    test_indices = (bin_indices == i);
    % using negation we find the rest i.e. actuall indices in X for test
    % set
    train_indices = ~test_indices;

    % we can see in the workplace that each X_test has the bin size in our
    % data set it will be: 760/10=76
    % while the rest of the data is "labled" as train
    X_test  = [ones(bin_size, 1), X(test_indices, :)];
    X_train = [ones(rowsX-bin_size, 1), X(train_indices, :)];
    
    Y_test = Y(test_indices);
    Y_train = Y(train_indices);
    
    % B is the theta vector, coefficients
    [B,BINT,R,RINT,STATS] = regress(Y_train, X_train);
    
    % The MSE is a measure of the quality of an estimator - it is always non-negative, 
    % and values closer to zero are better.
    % 
    % MSE = sqrt(RSS) which is the expression in liniar regg cost function
    % J without 1/2m
    
    y_hat_train = X_train*B;
    MSE_train = sqrt((sum(y_hat_train - Y_train).^2)./(rowsX-bin_size));
    
    y_hat_test  = X_test*B;
    MSE_test = sqrt((sum(y_hat_test - Y_test).^2)./bin_size);
    
    results(i,:) = [STATS(1), MSE_train, MSE_test];
    
    if i==k
        figure(1);
        plot(Y_test, 'b*');
        hold on;
        plot(y_hat_test, 'mo');
        legend('test', 'hat test');
    end;
    
end;

% plot results
figure(2);

subplot(3,1,1);
plot(results(:, 1)', 'b*');
title('R^2');

subplot(3,1,2);
plot(results(:, 2)', 'g*');
title('MSE train');

subplot(3,1,3);
plot(results(:, 3)', 'r*');
title('MSE test');
















