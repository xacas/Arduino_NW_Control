clear all;
Q_GAIN=48;
dt=0.1;
time=30;

x=dt:dt:time;
len=length(x);
Vo=zeros(len,1);
V1=zeros(len,1);
Vi=zeros(len,1);
Vr=2;

% Create tcpip object
sock=tcpip('192.168.5.2',8000,'NetworkRole','server');

% Create Output Signal Figure
haxes1=subplot(2,1,1);
h1=animatedline(haxes1,'MaximumNumPoints',len*2);
axis([0 time -3 3])
title(haxes1,'Output Signal')
line=refline(haxes1,[0 Vr]);
line.LineStyle='--';
grid on

% Create Input Signal Figure
haxes2=subplot(2,1,2);
h2=animatedline(haxes2,'MaximumNumPoints',len*2);
axis([0 time -3 3])
title(haxes2,'Input Signal')
grid on

% Control Loop
for k=1:len
    % Open tcpip
    fopen(sock);

    % Read message
    read_buffer=fread(sock,2,'int8');
    Vo(k)=read_buffer(1)/Q_GAIN;
    V1(k)=read_buffer(2)/Q_GAIN;
    Vi(k)=control(Vo(k),V1(k),Vr);
    disp([Vr Vo(k) V1(k) Vi(k)]);
    % Send Voltage Input
    fwrite(sock,Vi(k)*Q_GAIN,'int8');
    % Close tcpip
    fclose(sock);
    addpoints(h1,x(k),Vo(k));
    addpoints(h1,x(k)+dt,Vo(k));
    addpoints(h2,x(k),Vi(k));
    addpoints(h2,x(k)+dt,Vi(k));
    drawnow limitrate
end
