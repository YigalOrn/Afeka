function [ x0,nx]=uniqsol(f,xmin,xmax)


i=0;
for x=xmin:0.2:xmax
xzero=round(fzero(f,x)*100)/100;
if xzero>=xmin &xzero<=xmax
    i=i+1
  sol(i)=xzero; 
end
end

x0(1)=sol(1);
n=1;
for j=2:length(sol)

    if sol(j)~=sol(j-1)
        n=n+1;
        x0(n)=sol(j);
    end
end
nx=length(x0)

        

