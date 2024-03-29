fs = 10000; % Sampling frequency (samples per second) 
dt = 1/fs; % seconds per sample 
StopTime = 0.4096; % seconds 
t = (0:dt:StopTime); % seconds 
F = 1004; % Sine wave frequency (hertz) 
data = sin(2*pi*F*t);

FID = fopen('samples.txt', 'w');
if FID == -1, error('Cannot create file.'); end
fprintf(FID, '%f,\n', data);
fclose(FID);

plot(t,data);
Y = fft(data)

P2 = abs(Y/length(t));
P1 = P2(1:length(t)/2+1)
P1(2:end-1) = 2*P1(2:end-1);

f = fs*(0:(length(t))/2)/length(t);

FID = fopen('f.txt', 'w');
if FID == -1, error('Cannot create file.'); end
fprintf(FID, '%f\n', f);
fclose(FID);

plot(f,P1) 
title('Single-Sided Amplitude Spectrum of X(t)')
xlabel('f (Hz)')
ylabel('|P1(f)|')