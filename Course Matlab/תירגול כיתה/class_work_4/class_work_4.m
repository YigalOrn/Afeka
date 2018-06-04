%% Class_Work_4
%% General
clear all, clc, format compact
%% Expand Matrices and  substitute elements
clc
a=-5, b=7, m=4,n=5
A=round(rand(m,n)*(b-a)+a)
A(3,1:2:end)=[1 ,0 ,pi] % end- last index
d1=A([3 3 3 ],:) %extract the third row 3 times
d2=A(ones(1,3)*3,:) %the same as d1
A(1:2,4:5)=[3 6; 8 6]
A(7:8,7)=[3;4] % Expanding matrice A
%% Complex_Numbers
clc
e1=3+4*j %  is defined by i or j
e3=angle(e1)
e2=complex(3,4) %is defined by a function
%% assignment_4,  1
clc,clear
a=10, b=15
r=(b-a)*rand(20,1)+a
a=-1, b=1
im=(b-a)*rand(20,1)+a

z=r+im*i %vector element-wice op
z=complex(r,im)
% z(:,2)=abs(z)
% z(:,3)=angle(z(:,1))
%z=[z,abs(z),angle(z)]

%% Arithmetic Operation with Matrices 
%% Scalar and Matrice
clc
g1=reshape(1:6,3,2)'
g2=g1*2 %the scalar value is multiplied by every element in the matrix 
g3=g1/2
g4=sin(g1)
%%  Adding/Substracting Matrices
%Matrix arithmetic operations are defined by the rules of linear algebra.
%Notice that addition and subtraction of matrices works element by element (add a(1,1) to b(1,1) 
%then add a (1,2) to b(1,2), etc...)
%Also note that the number of rows and columns of each array must be the same.
clc
A=[2 1 5; 6 8 4] %2x3
B=[8 5 1; 0 9 2] %2x3
AB=A+B %  Matrix dimensions must agree
BA=A-B
C=A'*B %2x3-->3x2 * 2x3-->3x3 matrix multiplication involving inner products between rows and columns
%% Dot(scalar)  multiplication  of vectors 
% C = dot(A,B) returns the scalar product of the vectors A and B
clc
u=2:2:10
v=2*u
uv=u*v'% 1xn * nx1 -->1
uv=dot(u,v)

%% Cross  multiplication  of vectors
% C = cross(A,B) returns the cross product of the vectors A and B. That is,
% C = A x B. A and B must be 3-element vectors.
clc
a=1:3
b=[2 5 7.5]
c=cross(a,b)
%% Linear equations
clc
A=[1 2 3;4 5 6; 7 8 0]
b=[366;804;351]
%Ax=B is a linear system in matrix form
%A^(-1)Ax=A^(-1)*B --> x=A^(-1)B
x=A\b % '\' is not "normal" division op '/'
x=A^(-1)*b
x=inv(A)*b
%% 	Element by element operations on arrays
% A.*B denotes element-by-element multiplication. A and B must have the same dimensions.
% The period character (.) distinguishes the array operations from the  matrix operations.
clc
A=[1 2; -4 0]
B=[1 2 ; -3 3]
c1=A.*B
c2=A+B
c3=A./B
c4=A.^2
c5=2.^A
%% assignment_4, 2
clc;
A=(reshape (1:9,3,3)')^2
B=(reshape (1:9,3,3)').^2
%% assignment_4,  3
clc;
x=2:2:10, y=3:3:15
z=(x.*y+y./x)./((x+y).^(y-x))+12.^(x./y)
%% assignment_4, 4
% Main-> Moshe Brand course -> Homework -> Questions -> Home Work - English
x=linspace(23,67,25) %a
y=sin(x)' %b
A=rand(2,3) %c
B=rand(2) %d
D=rand(2) %e
G=B+D %f
K=A'*B %g
K1=B*A %g-not the same!!
L=G+55; %h
M=[A, B;fliplr(x(1:5));y((end-4):end)'] %i
M1=[A, B;fliplr(x(5:-1:1));y((end-4):end)'] %i the same as M
q8=x(1:2:25);%j
q12=y([3 6 21 9 17]);%k
%% assignment_4, 5

w=linspace(0,2*pi)
z=2*sin(w).*w+2*w.^2





