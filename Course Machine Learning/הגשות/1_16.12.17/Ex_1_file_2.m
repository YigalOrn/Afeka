%%
% https://www.youtube.com/watch?v=jbwSCwoT51M
clc; clear all; close all; format compact;

%%
% This data was download from UCI, it is named “Energy efficiency Data Set”. 
% Originally there are two variables to be predicted – y_1 and y_2, here we only use y_1. 
% Originally there were 768 data rows, here we only use 760 rows.


% I downloaded this data set again!, 
% I also edited it to fit the above description!

data_set = csvread('UCI_ENB2012_data.csv');

%%
X = data_set(1:760, 1:8);
Y = data_set(1:760, 9);

%%

% linear regression
XX = [ones(760,1), X];
[B,BINT,R,RINT,STATS] = regress(Y,XX);

% https://stats.stackexchange.com/questions/250730/what-is-the-mathematical-relationship-between-r2-and-mse
disp('Orginal MSE');
Original_MSE = (1-STATS(1))*(sum( (Y-mean(Y)).^2 ))/760


% lasso regression
k = 0:1e-3:1;
length_k = length(k)
[B_Lasso,STATS_Lasso] = lasso(X,Y,'lambda', k);

figure; 
plot(k,B_Lasso,'LineWidth',2);
xlabel('k');
ylabel('B Lasso');
title('B Lasso(weights) as func of lambda');

disp('B:');
B'
disp('B_Lasso(:, 1):');
B_Lasso(:,1)'

% they are different(wrong!! they are the same when lasso-lambda is zero) and Lasso auto reduced the number of features
% (we can see that we got a coefficient of value zero  for one of them)

figure; 
plot(k, STATS_Lasso.MSE, 'b');
title('Lasso MSE');

figure;
plot(1:length_k, STATS_Lasso.MSE, 'b');
title('Lasso MSE');

% the Lasso MSE grows as k grows.
%
% we saw that when penalty lambda is not used(like in Ridge or Lasso) the
% algo tries to match the data set "crazy" perhaps higly ordered poly'...
% those functions give us a small MSE because it fits very well(although new data can mass it up)
%
% Lasso(and Ridge) on the other hand act differently, it will fit the data
% with "lower order functions" finding a more balanced hypothesis to fit
% the data, this hypothesis may not fit the data as well as the higher
% order functions making the MSE larger! but it is more realistic and
% robust as we ask it to do predication on new data...
% in other words as lambda grows the algo will prefer smaller coefficients
% over small MSE...
%
% Lasso is almost identical to Ridge regression and the difference is because Lasso uses L1 norm and not L2 
% the geometry of the boundary we get is a Diamond shaped and it allows Lasso min' process of the coefficients 
% to set exactly on one of its tips there by getting zero! which is not possible with Ridge...
% this property of Lasso also indicates which features we can omit...
%
% in conclusion:
% as we ask the Lasso algo to penalize "harder" the fitting
% using high order functions/poly' the MSE grows accordingly our work is to
% to find using learned siklls in ML course the lambda which gives the best balance between realistic and robust  
% hypothesis and a reasonable MSE....




% when using Lasso, the algo will may give zero val to one or more coefficients...
% those coefficients are the ones we can omit!
% 
% max num of features we can omit is 5.
% 
% as far as I understand:
% if we plot the Lasso MSE as function of size of k and enlarge the plot we
% can see that for the value of k who is tested as the eleventh k in order!
% we get a Lasso MSE that is approx' 8.606 which is not so bad compared to
% the original which is 8.57(if I am not worng!).
% choosing this value of lambda for Lasso regg' we can omit 2 features
% which are x2 and x3 in X.... 
% again if plot lambdas as function of the size of k and enlarge,
% then look as B_Lasso for the col 11...

k_11 = STATS_Lasso.Lambda(11)


% [B_Lasso,STATS_Lasso] = lasso(X,Y,'lambda', k);
% lassoPlot(B_Lasso, STATS_Lasso, 'PlotType', 'Lambda');

% [B_Lasso,STATS_Lasso] = lasso(X,Y,'CV', 10);
% lassoPlot(B_Lasso, STATS_Lasso, 'PlotType', 'CV');



% what is a close MSE to the original we could choose by ourself according
% to:
%
% - budget: computetional power
% - there is no oppurtunity to collect new data
%
% good choice would be to choose the lambda where at the knee of the plot,
% the point from where the plot goes up very quickly...
% approx lambda with index 113.


