function u = control(e)
    persistent esum
    if isempty(esum)
        esum = 0.0;
    end
    esum = esum + e * 100e-3;
    u = 1.0 * e + 0.3 * esum;
    return;
end