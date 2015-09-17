path = ('c:\show.jpg');
RGB = imread(path)
% figure, imshow(RGB);

G = rgb2gray(RGB);
% figure,imshow(G);

[r,c] = size(G);
x = 1:c;
plot(x, G(26,:))

