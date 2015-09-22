I = imread('C:\\Users\\DataLab04\\Pictures\\1.png');

%흑백영상
G = rgb2gray(I);
T = G;
figure, imshow(G);

%1차원 영상을 흰색으로 표시
T(57,:) = 255; 
figure, imshow(T);

%
[m,n] = size(G);
figure, plot(1:n, G(57,:));

%
[x,y] = meshgrid(1:n, m: -1:1);
z = im2double(G);

figure, meshz(x,y,z);
