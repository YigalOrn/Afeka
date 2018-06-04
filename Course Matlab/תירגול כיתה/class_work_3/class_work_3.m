 %% Class_Work_3
%% General
clc, clear all, format compact
%%  Matrix index
clc, clear all, format compact
A=[1 1 1 -2; 1,8 6 0; -1 2 5 8; 1 0 pi pi/3; 1 sin(pi/3) exp(2) 0]
a31=A(3,1)
a_2=A(:,2) %extract the 2nd column
a_odd=A([1 3 5],[1,3]) %extract every odd element from the matrix
%%  Replacing a value inside array
clc;
A=[1 1 1 -2; 1 8 6 0 ; -1 2 5 8 ; 1 0 pi pi/3; 1 sin(pi/3) exp(2) 0]
A(1,1)=-111
A(1)=-111
A(3,[1 3])=0
A(:,3)=100
A(:,3)=[100;100;100;100;100]
%% Expanding Matrice
% If a value is assigned to an element beyond the original size of a
% matrix, Matlab will expand it, filling in zeros for any new elements whose values are not specified
A(7,8)=5

%%  Deleting Rows and Columns
A(3,:)=[]
A(:,6)=[]
%% class assign_3-   1
clc
A_11=[1:7; 2:2:14; 21:-3:3;5:5:35]
B=A_11([1 3 4], 1:2:7)
u=[A_11(3,:),A_11(:,5)',A_11(:,7)']
%% Special matrices
clc
m=5, n=4
z1=zeros(m,n)
z2=zeros(n)
o1=ones(m,n)
o2=ones(m)
e1=eye(m,n)
e2=eye(n)
b=[5 6 7 8] %  The main diagonal may be extracted (as a vector) using diag
d_b=diag(b)
%% class assign_3-   2
clc
A=zeros (2,5)
B=eye(4)
C=ones (3,2)
%% sort array elements in asending or descending order
clc
d_row=[4 pi 0 1]
s1=sort(d_row)
s2=sort(d_row,'descend') % sorts the elements along the vector in descending order

A_11
s3=sort(A_11) % sorts the elements along each column in ascending order
s4=sort(A_11,2) % sorts the elements along each row in ascending order
s5=sort(A_11')' % The same

clc
A_11
s6 = sort(A_11(:)')
%% reshape: B=reshape(A,m,n) returns the m by n matrix B whose elements are
%%taken column wise from A
clc
D=1:12
m=2,n=6
D1=reshape(D,m,n)
D2=reshape(D,n,[])'
%% class assign_3-   3
clc
A=reshape(1:35,7,5)'
B=A(2:4,3:6)
%% Random numbers matrix 
r1=rand(m,n)
r2=rand(m,n)*10
%% Random numbers from a to b
clc
a=5,b=7
r3=rand(m,n)*(b-a)+a
%% Random integers from a to b
clc
r4=round(rand(m,n)*(b-a)+a)
%% class assign_3-     4
clc
R=round(rand (1,6)*(15+7)-7)
R=sort(R,'descend')
%% sum
clc
d_row=[4 pi 1 0]
sum_s1=sum(d_row)

clc
B
sum_B=sum(B) %  sums the elements in each column
sum_B_r=sum(B,2) % sums the elements in each row
sum_B_r1=sum(B')'
sum_B_all=sum(sum(B)) %sums all the elements in the matrix

% use of :
sum_B_all_2=sum(B(:)) % the same
%% max
clc
d_row
max_s1=max(d_row)

clc
B
max_B=max(B)
max_B_r=max(B')'
max_B_r2=max(B,[],2) % finds the max element in each row
max_B_all=max(B(:))
%% mean
mean_s1=mean(d_row)
mean_B=mean(B)
mean_B_r=mean(B')'
mean_B_r2=mean(B,2)
mean_B_all=mean(B(:))

%%  class assign_3-   5
a11=ones(2,2)
a12=2*ones(2,3)
a21=3*ones(3,1)
a22=4*ones(3,2)
a23=5*ones(3,2)
A=[a11 a12; a21 a22 a23]
%% class assign_3-   7
clc
m1=reshape(1:4,2,2)'
m1(5,5)=5
%% class assign_3-   8
clc
A=ones (3)
B=5*(ones(2))
A(4:5,4:5)=B
A=ones(3) % another solution
A(4:5,4:5)=5

%%  class assign_3-   9
A=reshape ([1:8],4,2)'
A(3:4,1:2)=5





