clear;
close all;
clc;
im1 = double(imread("T1.jpg"));
im2 = double(imread("T2.jpg"));
%[numRows, numCols] = size(im2);
corrCoefArr = [];
quadraticMIArr = [];
arr = [-10,-9,-8,-7,-6,-5,-4,-3,-2,-1,0,1,2,3,4,5,6,7,8,9,10];
for shift = -10:10
    shiftedIm = circshift(im2, [0, shift]);  
    %shiftedIm = shiftedIm(:, 1:numCols);
    if shift > 0
        shiftedIm(:,1:shift) = 0;
    end
    if shift < 0
        numCols = size(shiftedIm,2);
        shiftedIm(:,numCols+shift+1:numCols) = 0;
    end
    correlationMatrix = corrcoef(im1, shiftedIm);
    if shift == 0
        disp(correlationMatrix);
    end
    correlationCoefficient = correlationMatrix(1, 2);
    corrCoefArr(end+1) = correlationCoefficient;
    flatIm1 = im1(:);
    flatShifted = shiftedIm(:);
    binWidth = 10;
    numBins = ceil(256 / binWidth);
    binnedArray1 = floor(flatIm1 / binWidth) + 1;
    binnedArray2 = floor(flatShifted / binWidth) + 1;
    histArray1 = histcounts(binnedArray1, numBins);
    histArray2 = histcounts(binnedArray2, numBins);
    jointHist = myJointHistogram(im1, shiftedIm, numBins);
    %[jointHist, edgesX, edgesY] = histcounts2(im1,shiftedIm,'NumBins',[numBins,numBins]);
    %quadraticMI = sum(sum(jointHist .* jointHist)) - sum(histArray1 .* histArray1) - sum(histArray2 .* histArray2);
    jointProb = jointHist / sum(jointHist(:));
    marginalProb1 = sum(jointProb, 2);
    marginalProb2 = sum(jointProb, 1);
    QMI = sum(sum((jointProb - (marginalProb1 * marginalProb2)).^2));
    quadraticMIArr(end+1) = QMI;    
end
figure;
plot(arr,corrCoefArr,'r');
xlabel('x');
ylabel('y');
title('correlation Coefficient vs shift');
grid on;

figure;
plot(arr,quadraticMIArr,'b');
xlabel('x');
ylabel('y');
title('QMI vs shift');
clear;
clc;

% Load and process the image
im1 = double(imread("T1.jpg"));
im2 = 255 - im1;
[numRows, numCols] = size(im2);

% Initialize arrays with preallocation
corrCoefArr = zeros(1, 21);
quadraticMIArr = zeros(1, 21);

% Define shifts
shifts = -10:10;

for shift = shifts
    shiftedIm = circshift(im2, [0, shift]);
    
    % Handle boundary cases by zeroing out columns
    if shift > 0
        shiftedIm(:, 1:shift) = 0;
    elseif shift < 0
        shiftedIm(:, end+shift+1:end) = 0;
    end
    
    % Calculate correlation coefficient
    correlationCoefficient = corr2(im1, shiftedIm);
    corrCoefArr(shift + 11) = correlationCoefficient;
    
    % Calculate quadratic mutual information
    jointHist = myJointHistogram(im1, shiftedIm, 26); % Adjust the number of bins as needed
    jointProb = jointHist / sum(jointHist(:));
    marginalProb1 = sum(jointProb, 2);
    marginalProb2 = sum(jointProb, 1);
    QMI = sum(sum((jointProb - (marginalProb1 * marginalProb2)).^2));
    quadraticMIArr(shift + 11) = QMI;
end

% Plot correlation coefficient
figure;
plot(shifts, corrCoefArr, 'r');
xlabel('Shift');
ylabel('Correlation Coefficient');
title('Correlation Coefficient vs Shift for Inverted Image');
grid on;

% Plot quadratic mutual information
figure;
plot(shifts, quadraticMIArr, 'b');
xlabel('Shift');
ylabel('QMI');
title('QMI vs Shift for Inverted Image');
grid on;

% Custom function for joint histogram calculation
function jointHist = myJointHistogram(array1, array2, numBins)
    % Initialize the joint histogram
    jointHist = zeros(numBins, numBins);

    % Calculate the bin width
    binWidth = 256 / numBins;

    % Flatten the arrays
    flatArray1 = array1(:);
    flatArray2 = array2(:);

    % Calculate indices for the bins
    indices1 = floor(flatArray1 / binWidth) + 1;
    indices2 = floor(flatArray2 / binWidth) + 1;

    % Populate the joint histogram
    for i = 1:length(indices1)
        jointHist(indices1(i), indices2(i)) = jointHist(indices1(i), indices2(i)) + 1;
    end
end