function y=fibonacci(n)


if n<=2
    y=[]
else
    for i=3:n
        y(1)=0;
        y(2)=1;
        y(i)=y(i-1)+y(i-2);
    end
end
        