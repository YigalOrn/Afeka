%%  Class_Work_5
%% General
clear all, clc, format compact
%% String
% A special variable type for characters.
% In MATLAB a sting is actually a vector which each element is a single character. 
% Defining a string - using "'" :
s='red' %creates a 3-element character array 
a1=5
s1=s(1)
s3=s(3)
g1=double(s) %returns the ascii value for s
g2=char(g1)
x=['ab' 'cd' 'ef']  %This line creates a new string variable from three other strings

y=['hello'; 'world'] %each row of such an array must have exactly the same length
r1=['g', s(2), 't','  ','r',s(2),'a',s(3),'y']
r2=[r1, '2010']
%% num2str(number)- creates a string from a number
clc
f1=750;
f2=num2str(f1);
f3=[f2(2),f2(3),f2(1),f2(2)]
%% str2num(string)-does the opposite (from string to number)
clc
f4=str2num(f3)+3
%% class_assignment_5-1
clc
%x=9*round(rand*1111)
x=1303
x1=num2str(x)
x2=x1' %separate digits number
x3=str2num(x2)
s=sum(x3)
result=round(s/9)-s/9
%% Combine numerical variables in a string
clc
a=5;
s='The number of the element is:  ';
s1=[s num2str(a)]
%% disp (a) - to display a single variable (either numerical or string) 
clc;
b=45;
disp(b)
disp('hello')
disp(b^2)
disp([s, num2str(a)])
disp(s1)
%% input- waits for input from the user
clc
% t=input('time=?  ') % can be string or numeric variable (matrice, vector, function...)
% t=input('time=?  ','s')     %returns the entered text as a MATLAB string
%%  class_assignment_5-3
clc
 d=input('day=');
 m=input('month=','s');
 y=input('year=');
 disp(['Today is: ', num2str(d), ',', m, ' ', num2str(y)])
%%  class_assignment_5-4
clc
% A=input ('what is your name?  ');
% A=sort(A);
% l=length(A)
% S=[A,'_',num2str(l)]
% %%Second option
% A=sort(input ('what is your name?  '));
% S=[A,'_',num2str(length(A))];
% disp(['your password is:  ', S])
%% class_assignment_5--5
A=round(rand(3,5)*30-20);
[l m]=size(A);
b=['The matrice size is:  ',num2str(l), 'X',num2str(m)];
disp (b)
%% Display a table
clc
x=1:10;
y=exp(x);
disp('     x        exp(x)')
disp([x' y'])
%% class_assignment_5-6
clc
A=(10-6)*rand(4,5)+6;
disp('      Min     Max     Mean')
disp([min(min(A)), max(A(:)), mean(A(:)) ]) 
%%  Plot- plot(x,y)
plot([3 4 6],[4 5 3]) % several coordinates

%% Generate plot of continious function
% LineSpec- Line specification syntax - line style, marker, and color
% specifiers
x=0:5:360;
y=sind(x);
%plot(x,y,'r:s') 
%plot(x,y,'b--d')
plot(x,y,'m--o')
%% class_assignment_5-8
x=-10:0.1:10;
y=(x.^2-x+1)./(x.^2+x+1);
plot(x,y)






