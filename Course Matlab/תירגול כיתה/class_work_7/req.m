function REQ=req(R)
%This function calculatases the equivalent resistance of
%n electrical resistorsconnected in parallel
REQ=1/sum(1./R);
