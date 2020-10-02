function Vi = control(Vo,V1,Vr)
    persistent esum
    if isempty(esum)
        esum = 0.0;
    end
    esum = esum + (Vo-Vr) * 100e-3;
    Vi = -2.0802 * Vo - 0.0562 * V1 - 0.8211 * esum;
    if(Vi>2.5)
        Vi=2.5;
    elseif(Vi<-2.5)
        Vi=-2.5;
    end
    return;
end