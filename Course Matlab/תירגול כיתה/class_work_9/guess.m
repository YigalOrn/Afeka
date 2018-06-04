clc;
clear all;
%%
a=round(rand*1000)
j=0;
num=0
while j~=1
    x=input('gues a number betweem 0 to 1000  ');
    num=num+1;
    if a>x
        disp('your gues is smaller than the computer number, try again...')
    elseif (a<x)
        disp('your gues is bigger than the computer number, try again...')
    else
        j=1
        disp(['your gues is right and you did it in  ' num2str(num) '  guesses'])
    end
end