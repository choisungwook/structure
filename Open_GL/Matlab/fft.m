clear all
close all
f0=20;
f1=2*f0
f2=3*f0;
T=1/f0;
Ns=256;
t=linspace(0,T,Ns);
Ts=t(2)-t(1);
fs=1/Ts;
freq=1/(Ts*Ns)*[-Ns/2:(Ns/2-1)];
ft=0.5*ones(1,length(t));
plot(t,ft,'r','LineWidth',2);
hold on
ft=0.5*sin(2*pi*f1*t);
plot(t,ft,'b','LineWidth',2);
hold on
ft=0.2*sin(2*pi*f2*t);
plot(t,ft,'k','LineWidth',2);
hold on
ft=0.5+sin(2*pi*f0*t)+0.5+sin(2*pi*f1*t)+0.2*sin(2*pi*f2*t);
plot(t,ft,'m','LineWidth',2);
grid on
FT=fft(ft);
Mag=abs(FT);
figure, stem(freq, Mag)
title('Magnitude spectrum'),xlabel('f(Hz)'), ylabel('Magnitude')
title('Magnitude spectrum'),xlabel('f(Hz)'), ylabel('Magnitude')
FT=fftshift(fft(ft));
Mag=abs(FT);
Ang=angle(FT);
figure, stem(freq, Mag)
title('Magnitude spectrum'),xlabel('f(Hz)'), ylabel('Magnitude')
figure, stem(freq(123:135),Mag(123:135))
title('Magnitude spectrum'),xlabel('f(Hz)'), ylabel('Magnitude')
figure, stem(freq(123:135),Ang(123:135))
title('Magnitude spectrum'),xlabel('f(Hz)'), ylabel('Phase')
figure, stem(123:135),Mag(123:135)
figure, stem(123:135),Mag(123:135)
FT(128:130)=0;
ift=ifft(ifftshift(FT));
figure,plot(t,real(ift), 'LineWidth',2),grid
ft=sin(2*pi*f0*t);
plot(t,ft,'g','LineWidth',2);
hold on
FT(126:127)=0;
FT(131:132)=0;
ift=ifft(ifftshift(FT));
figure, plot(t,real(ift),'LineWidth',2),grid


grid on
%Fourier transform
FF = fft(ft);
Mag = abs(FT);
figure, stem(freq, Mag)
title('Magnitue spectrum'), xlabel('f(Hz)'), ylabel('Magnitue')

FT = fftshift(fft(ft));
Mag = abs(FT);
Ang = angle(FT);
figure, stem(freq, Mag);
title('Magnitue spectrum'), xlabel('f(HZ'), ylabel('Magnitue')
figure, stem(freq(123:135), Mag(123:135));
title('Magnitue spectrum'), xlabel('f(HZ'), ylabel('Magnitue')
figure, stem(freq(123:135), Ang(123:135));
title('Magnitue spectrum'), xlabel('f(HZ'), ylabel('Phase')
figure, stem(123:135, Mag(123:135));

FT(128:130) = 0;
ift = ifft(ifftshift(FT));
figure, plot(t, real(ift), 'LineWidth',2), grid
