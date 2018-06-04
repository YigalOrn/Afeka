%% Class_Work_9
%% General
%% Conditional Statements
%% if: Conditionally execute statements
% The if statement evaluates a logical expression
%and executes a group of statements when the expression is true.
% if cond
%     statement_list
% end


% a=input('a=?');
a=6;
if a<9
    disp('small')
end
%% if-else statement
% if ( cond )
% statement_list1
% else
% statement_list2
% end

%a=input('a=?');
if a<9
    disp('small')
else
    disp('Big')
end
%% elseif
% The optional elseif and else keywords provide for the execution of
% alternate groups of statements.
% if cond(1)
%     statement_list(1)
% elseif cond(2)
%     statement_list(2)
% elseif cond(3)
%     statement_list(3)
%     :
%     :
%     :
% else
%     statement_list(0)
% end
    
%a=input('a=?');
a=17;
if a<9
    disp('small')
elseif a< 11
    disp('medium')
else
    disp('Big')
end
%% class assignment_9,1
% See quadroots.m 
%(a)
a=2; b=8; c=-3;
The eq. has 2 roots:
r1=0.34521,   r2=-4.3452

%(b)
a=15; b=10; c=5;
The eq. has no real roots

%(c)
a=18; b=12; c=2;
The eq. has 1 root:
r=-0.33333

%% For:  Execute block of code specified number of times
% Syntax
% for variable = array
%     statements 
% end
% In the for loop, array can be any vector or array of values. The for loop
% works like this: variable is set to the first value in array, and the sequence of MATLAB commands
% in the body of the for loop is executed with this value of variable. Then variable is set to the second value in array, 
% and the sequence of MATLAB commands in the body of the for loop is executed with this value of d. 
% This process continues through all of the values in array. 


clc;clear all;
a=0;
for i=1:12
    a=a+1;
end
disp(['a=   ' num2str(a)])
%%

a=0;
v=[4 8 9 2 6]
for i=v
    if i>7
        a=a+i;
    end
end
a
%% Nested For Loops
a=0;
v=[4 8 9 2 6];
for i=v
    for j=1:4
        a=i*j
    end
end
%% Example: average with 2 neighbours

clc;clear all;
a=round(rand(5,7)*10);

for i=1:5
    for j=1:7
        if j==1|j==7 % except for the 1st and 7th columns
            a_new(:,j)=a(:,j);
        else
            a_new(i,j)=(a(i,j-1)+a(i,j)+a(i,j+1))/3;
        end
    end
end
a_new
%% class_assignment_9,2
clc;clear all;

for i=1:4
    for j=1:7
        m(i,j)=i+j;%each element is the sum of its indices
    end
end
m

%%  While Loop: Repeatedly execute statements while condition is true

clear all;
a=1;flag=1;
while flag<10
    a=a*flag;
    flag=flag+1;
end
a
%% class_assignment_9,3
% The smallest odd number that is divisible by 3 and whose cube is greater
% than 4000
clc; clear all
j=0;
i=1;
while j~=1
i=i+2;
 j=( mod(i,3)==0) & (i^3>4000);
end
   i
% another option
clc; clear all;
i=1;

while (( mod(i,3)==0) & (i^3> 4000)&mod(i,2)~=0 )~=1
    i=i+1 ;

end
i
% and one more.....
clc; clear all
j=0;
i=1;
while ~(( mod(i,3)==0) & (i^3>4000))
    i=i+2;
end
   i
%% class_assignment_9,4-guess a number
a=round(rand(1)*1000);
x=input('guess a number between 0 to 1000   ');
  num=0;
  while (a~=x)
      num=num+1;
      if a>x
          x=  input('your number is smaller than my, try again ');
      else
          x= input('your number is bigger than my, try again  ')
      end
  end
     disp(['your gues is the right gues and you did it with   ' num2str(num)  '   guesses' ] )
 %%
a=round(rand(1)*1000);
b=-1;
num=0;
while a~=b
    b=input('guess number between 0 to 1000');
    num=num+1;
    if b>a
        disp('your number bigger than my')
    else
        disp('your number lower than my')
    end
end
disp(['you guessed thr right number, and you did it with ',num2str(num ),' guesses'])


%% class_assignment_9,5-fibonacci
% see fibonacci.m
 y=fibonacci(5)


     
     




   

