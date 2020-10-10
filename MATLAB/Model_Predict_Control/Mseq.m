function ret = Mseq()
    persistent Xn;
    persistent count;
    if isempty(Xn)
        Xn = uint32(1);
    end
    if isempty(count)
        count = uint32(40);
    end
    
    count=count-1;
    ret = double(bitxor(bitshift(bitand(Xn,64),-6),bitand(Xn,1)));
    if(count == 0)
        Xn = bitshift(Xn,1) + ret;
        count = 40;
    end
    return;
end