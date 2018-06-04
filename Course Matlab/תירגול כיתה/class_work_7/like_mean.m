function  like_mean(A)
%This function calculates an average of  array
[l,m]=size(A);
y=sum(A(:))/(l*m);
disp(['The average of the array is:   ' num2str(y)])
end