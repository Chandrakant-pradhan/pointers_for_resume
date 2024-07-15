
clear;
close all;
clc;
values = [1, 2, 3, 4, 5];
probabilities = [0.05, 0.4, 0.15, 0.3, 0.1];
numSamples = [5, 10, 20, 50, 100, 200, 500, 1000, 5000, 10000];
numRows = 5;
numCols = 2;
MAD = [];
figure(1);
figure(2);

for i = 1:length(numSamples)
    averageArr = [];
    for j = 1:10000
        samples = numSamples(i);
        generatedSamples = randsample(values, samples, true, probabilities);
        average = mean(generatedSamples);
        averageArr(end + 1) = average;
    end
    figure(1);
    subplot(numRows, numCols, i);
    histogram(averageArr, 50);  
    xlabel(['N is ' num2str(numSamples(i))]);
    
    [empirical, dataVals] = ecdf(averageArr);
    %empiricalArr = [empiricalArr; empirical'];  % Transpose empirical before concatenation
    %dataValArr = [dataValArr; dataVals'];        % Transpose dataVals before concatenation
    
    averageIs = mean(averageArr);
    DevIs = std(averageArr);
    gaussian = normcdf(dataVals, averageIs, DevIs);
    maxDiff = 0;
    for j=1:length(dataVals)
        diff = abs(gaussian(j) - empirical(j));
        if diff > maxDiff
            maxDiff = diff;
        end
    end
    MAD(end+1) = maxDiff;
    figure(2);
    subplot(numRows,numCols,i);
    plot(dataVals,empirical,'r','DisplayName','cdf');
    xlabel(['n is' num2str(numSamples(i))]);
    grid on;
    hold on;
    plot(dataVals,gaussian,'b','DisplayName','gaussian');
    legend('location','best');
    hold off;
    %gaussianArr = [gaussianArr; gaussian'];      % Transpose gaussian before concatenation
end
figure;
plot(numSamples,MAD,'b');
grid on;
legend('location','best');