function [coeff,score,latent] = do_pca( X_train_normlz )
% score: 
% is the X_train_normlz in the principal component space. 
% rows of score correspond to observations, and columns correspond to features.
%

    % option 1
    % https://www.mathworks.com/help/stats/pca.html
    [coeff,score,latent] = pca(X_train_normlz);
    
    % FinalData = RowFeatureVector x RowDataAdjust
    % Z_train1 = X_train_normlz*coeff;

    % option 2
    % https://www.mathworks.com/help/stats/pcacov.html
    % [W, LAMBDA] = pcacov(X_train_normlz);
    % Z_train2 = X_train_normlz*W;

end

