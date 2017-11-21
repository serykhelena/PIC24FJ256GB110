%clear all
%clc
global dat
delete(instrfind);
dat = serial('COM2', 'BaudRate', 115200);
dat.InputBufferSize = 4096;

fopen(dat)
set(dat, 'ByteOrder', 'bigEndian')

disp 'Ok!'

A=[];
B = [];
t = 3;
 for i = 1:t
%     A = fread(dat, 1, 'uint16');
    A=fread(dat, [1000,1], 'uint16');
    %A1 = A;
    B = [B; A];
 end
fclose(dat);

disp 'Close'
n4 = length(B);
B_f = [];
for p = 3: 1: n4-2
    b_f = (B(p-2, 1) + B(p-1, 1) + B(p, 1) + B(p+1, 1) + B(p+2, 1))/5;
    
    B_f = [B_f; b_f];
end


M = [];

for j = 2: 2: n4
    M = [M; B(j, 1)];
end

m = length(M);
M_f = [];
for a = 3: 1: m-2
    m_f = (M(a-2, 1) + M(a-1, 1) + M(a, 1) + M(a+1, 1) + M(a+2, 1))/5;
    
    M_f = [M_f; m_f];
end


T = [];

for t = 1: 2: (n4-1)
    T = [T; B(t, 1)];
end


tt = length(T);
T_f = [];
for x = 3: 1: tt-2
    tt_f = (T(x-2, 1) + T(x-1, 1) + T(x, 1) + T(x+1, 1) + T(x+2, 1))/5;
    
    T_f = [T_f; tt_f];
end