%% Class_Work_7
clear all;clc
%% User Defined in Function:   M-file function
%% Function Header:  function [output_arguments]=function_name (input_arguments)
 % *The M-file should have the same name as the function name (+.m)
% *The M-file must be saved in the working directory
% *Note that when you save the function, you are automatically suggested to name the file as the function
% *The function name can include alphabetic, numeric and�_� characters
%%  Help text: give details about the required inputs and the outputs
% Each function should start with its name, then a comment line giving the
% purpose of the function,
%% Example:  y=x^2
x=3;% x can be scalar
y=myfunc1(x)
v=4;%Not necessarily the same local arguments
u=myfunc1(v)
v=1:5;%Input argument can be a vector
u=myfunc1(v)
v=sin(pi/3);%or an expression 
u=myfunc1(v)
%b=myfunc1(input('a=? ')) % or a user input
b =     64

%% The function can have more than one output
clc;clear all
[r t]=func2(10,3)
[u v]=func2(ones(3),eye(3))
%% class_assignment_7,1
clc
r=3;
[p r]=circle(r)
%% class_assignment_7,2
clc
y=prob7_2(-3)
y =   -20.1000;
y= prob7_2 (5)
y =   237.5000;
x=-4:0.1:4;
y=prob7_2(x);
plot(x,y), xlabel('x'), ylabel('y')

%% class_assignment_7,3
clc
[x, y, z]=meansize (reshape (1:42,6,7))
%% class_assignment_7,4
clc; clear all
[height,mass]=SI2ST(180,75)
%% class_assignment_7,5
clc
R=[50 75 300 60 500 180 200];
Req=req(R)
%% class_assignment_7,6
% Note that this function doesn't return a value.
clc
B=reshape(1:35, 5,7);
like_mean(B)
%% class_assignment_7,7
clc
x=8;b=9;z=12;
[s m]=sum_product(x,b,z)
%% class_assignment_7,8
clc
A=reshape(1:36,6,6)
B = zeroDiag(A)
%% Another option of zero_Diag
clc;
D=reshape(1:25,5,5);
E=zeroDiag1(D)
%%  Another option of zero_Diag
clc;
M=reshape(1:49,7,7)';
N=zeroDiag2(M)


