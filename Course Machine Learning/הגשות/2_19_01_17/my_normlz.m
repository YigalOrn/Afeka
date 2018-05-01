function [X_test_normlz] = my_normlz(mean, std, X_test)
%
%

% funny outputs using this code... 
%     fix = find(std==0);
%     std(fix)=1;
%     for i=1:size(X_test,1)
%       X_test_normlz(i,:) = (X_test(1,:)-mean)./std;  
%     end

    [rowsX_test, colsX_test] = size(X_test);
    X_test_normlz = zeros(rowsX_test, colsX_test);
    for i=1:rowsX_test
        for j=1:colsX_test
            if std ~= 0
                X_test_normlz(i,j) = (X_test(i,j) - mean(j))/std(j);
            else
                X_test_normlz(i,j) = (X_test(i,j) - mean(j));
            end
        end
    end

%     if sum(sum(isnan(X_test_normlz)))
%         disp('NaN')
%         break
%     end

end

