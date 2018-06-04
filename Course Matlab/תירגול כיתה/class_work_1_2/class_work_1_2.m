%%  Class_Work_01/02
%% General
clear , clc, format compact
%% round - round to nearst integer
clc
x=1.5
y1=round(x)
y2=round(-x)
%% fix - round toward zero
clc
y3=fix(x)
y4=fix(-x)
%% ceil - round toward infinity
y5=ceil(x)
y6=ceil(-x)
%% floor - round toward minus infinity
y7=floor(x)
y8=floor(-x)

%% How to round to n digits after the decimal digit
clc
format long
number=pi
n=3
round_number=round(number*10^n)/(10^n)
%%  cd/pwd - navigating directories
%%  dir - displays the files within the directory
%%  who - lists workspace variables
%%  whos - lists workspace variables and details
%%  mkdir - generate a new folder 
%%  Use -+./.* value from  Matlab editor cell toolbar
%%
n=4
y=sin(pi/(2*n))
%% Assign vectors
format short
d_row=[4, 22, pi 4.11]
d_col=[1; 22; n/100; pi/2]
%% Transpose using  '
d_row_n=d_row' % 
d_col_n=d_col'
%% Chap 2, Exs 1-2
x1= [32 4 81 exp(2.5) 63 cos(pi/8) 14.2] % row vector
x2=[55 14 log(51) 987 0 5*sin(2.5*pi)]'  %column vector
%%  length> Length of vector
f2=length(d_col)
%%  size>Array dimensions
[l m]=size(d_row)
%% Matrices
clc
m1=[1, 4, pi; 8,1/5, 0]
m2=m1'
%% Build Vectors and Matrices from smaller Vectors and Matrices
clc
r1=[4 ,5, pi]'
m12r1=[m1 ; m2  r1]
%% Equally spaced elements:
%a:n:b;   a=first, n=increment, b=upper limit, default n=1
clc
x=1:55 
x2=1.1:5
x3=1:3:26
%% chap 2, Ex-4
x4=(15:-5:-25)'
size (x)
%% linspace(a,b,n)
%a=first, b=last, n=number of elements, n=100 default
g1=linspace(6.6,12,8)
%% Chap 2, Ex-5
g2=linspace (7,40,15)
g3=size(g2)
%% Chap 2, Ex-8
B=[1:3:25; linspace(72,24,9);0:0.125:1] %or
B=[ linspace(1,25,9); linspace(72,24,9); linspace(0,1,9)]

%%  Matrix indexes
%A(m,n)- m- vector indices of rows, n- vector indices of columns
%% Extract a single element from an array
B12=B(1,2) 
%% Extract a vector from an array
B_row1=B(1,:)
B_col3=B(:,3)
%In order to extract several elements in line 2  use "ns:ne" instead of
%column indices:
B2_24=B(2,2:4)
%In order to extract all elements in a column
B_all=B(:)
B_fifth_element=B(5)
%% Chap 2, Ex-9
A=[6 43 2 11 87; 12 6 34 0 5; 34 18 7 41 9]
va=A(2,:)
vb=A(:,4)'  %row vector
vc=[A(1,:),A(2,:)]
vd=[A(:,2);A(:,5)]'   %or vd=[A(:,2)',A(:,5)']





