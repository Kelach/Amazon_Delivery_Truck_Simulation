% Test Plotting

A = readmatrix('route_001.txt');

X = A(:, 1);
Y = A(:, 2);

figure;
scatter(X, Y);
hold on;
plot(X, Y);

