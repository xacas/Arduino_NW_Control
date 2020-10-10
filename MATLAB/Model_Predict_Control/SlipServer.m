clear all;
Q_GAIN=48;
Ts=300e-3;
time=300;
plotting=1;

x=Ts:Ts:time;
len=length(x);
Vo=zeros(len,1);
V1=zeros(len,1);
Vi=zeros(len,1);
Vr=zeros(len,1);

for i=1:len
    Vr(i)=4*(Mseq()-0.5);
end

%%
%Create Model Predict Controller

A = [ 0.951847 0.036224;0.0413406  0.583318];
B = [ 0.011505;0.377747];
C = [1 0;0 1];
D = 0;
CSTR = d2d(ss(A,B,C,D,0.1),Ts);

CSTR.InputGroup.MV = 1;
CSTR.OutputGroup.MO = 1;

MPCobj = mpc(CSTR,Ts);

MPCobj.PredictionHorizon = 15;

MPCobj.MV.Min = -2.5;
MPCobj.MV.Max = 2.5;
MPCobj.MV.RateMin = -1;
MPCobj.MV.RateMax = 1;

MPCobj.W.ManipulatedVariablesRate = 0.3;
MPCobj.W.OutputVariables = [1 0;0 1];

mpc_state = mpcstate(MPCobj);
%%

% Create tcpip object(note that this function will be removed)
sock=tcpip('192.168.5.2',8000,'NetworkRole','server');

if plotting==1
    % Create Output Signal Figure
    haxes1=subplot(2,1,1);
    h1=animatedline(haxes1,'MaximumNumPoints',len*2);
    axis([0 time -3 3])
    title(haxes1,'Output Signal')
    grid on

    % Create Input Signal Figure
    haxes2=subplot(2,1,2);
    h2=animatedline(haxes2,'MaximumNumPoints',len*2);
    axis([0 time -3 3])
    title(haxes2,'Input Signal')
    grid on
end

% Control Loop
for k=1:len
    % Open tcpip
    fopen(sock);

    % Read message
    read_buffer=fread(sock,2,'int8');
    Vo(k)=read_buffer(1)/Q_GAIN;
    V1(k)=read_buffer(2)/Q_GAIN;
    Vi(k)= mpcmove(MPCobj,mpc_state,[Vo(k) V1(k)],[Vr(k) Vr(k)]);
    disp([Vr(k) Vo(k) V1(k) Vi(k)]);
    % Send Voltage Input
    fwrite(sock,Vi(k)*Q_GAIN,'int8');
    % Close tcpip
    fclose(sock);
    if plotting==1
        addpoints(h1,x(k),Vo(k));
        addpoints(h1,x(k)+Ts,Vo(k));
        addpoints(h2,x(k),Vi(k));
        addpoints(h2,x(k)+Ts,Vi(k));
        drawnow limitrate
    end
end
