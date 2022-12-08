% Delivery Truck Simulation
% Plot graphs from experimental data

data1 = readmatrix('../Experimental/dataout/experiment1_data.dat');
data2 = readmatrix('../Experimental/dataout/experiment2_data.dat');
dim1 = size(data1);
dim2 = size(data2);

% Experiment 1 results
figure();
for r = 1:dim1(1)
    plot(data1(r, 2:end));
    hold on;
end
title('Impact of Distance Limit on Order Backlog', '20 orders/day, 30 days, 3 trucks');
xlabel('Day');
ylabel('Unfulfilled Orders');
legend(arrayfun(@num2str, data1(:, 1), 'UniformOutput', 0));
hold off;

% Experiment 2 Results
figure();
for r = 1:dim2(1)
    plot(data2(r, 2:end));
    hold on;
end
title('Impact of Number of Trucks on Order Backlog', '20 orders/day, 30 days, 34.0 distance limit');
xlabel('Day');
ylabel('Unfulfilled Orders');
legend(arrayfun(@num2str, data2(:, 1), 'UniformOutput', 0));