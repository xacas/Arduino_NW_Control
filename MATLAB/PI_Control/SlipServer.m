clear all;
Q_GAIN=25;
dt=0.01;
time=1;

x=dt:dt:time;
len=length(x);
% Create tcpip object
sock=tcpip('192.168.5.2',8000,'NetworkRole','server');
k=1;
h=animatedline;
axis([0 time -3 3])
grid on
while k<len
    % Open tcpip
    fopen(sock);

    Vr=2;
    % Read message
    read_buffer=fread(sock,2,'int8');
    Vo=read_buffer(1)/Q_GAIN;
    V1=read_buffer(2)/Q_GAIN;
    Vi=control(Vr-Vo);
    disp([Vr Vo V1 Vi]);
    % Send Voltage Input
    fwrite(sock,Vi*Q_GAIN,'int8');
    % Close tcpip
    fclose(sock);
    addpoints(h,x(k),Vo);
    drawnow limitrate
    k=k+1;
end
