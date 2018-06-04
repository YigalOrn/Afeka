function [ num ] = binomCoefficient(n, k )

%calculating the coeficients using Binomial theorem .
% nCk = n! / ( k! * (n-k)!  )

num  = factorial(n)/( factorial(k)*factorial(n-k)  )  ;


end

