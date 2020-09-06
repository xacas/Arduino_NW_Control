% Create tcpip object
t=tcpip('192.168.5.2',8000,'NetworkRole','server');
% Setting Server name
name=int8(sprintf('MATLAB\r\n'));

while true
    % Open tcpip
    fopen(t);
    % Read message
    data=fread(t,26,'int8');
    disp(char(data'));
    % Write name
    fwrite(t,name,'int8');
    % Read message
    data=fread(t,6,'int8');
    disp(char(data'));
    data=fread(t,11,'int8');
    disp(char(data(1:length(name))'));
    % Close tcpip
    fclose(t);
end