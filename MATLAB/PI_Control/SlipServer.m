
% Create tcpip object
t=tcpip('192.168.5.2',8000,'NetworkRole','server');

while true
    % Open tcpip
    fopen(t);

    Vr=2;
    % Read message
    read_buffer=fread(t,2,'int8');
    Vo=read_buffer(1)/25;
    V1=read_buffer(2)/25;
    Vi=control(Vr-Vo);
    disp([Vr Vo V1 Vi]);
    % Send Voltage Input
    fwrite(t,Vi*25,'int8');
    
    % Close tcpip
    fclose(t);
end