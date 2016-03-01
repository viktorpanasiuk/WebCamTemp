H = 480; % Height of image
W = 640; % Width of image
minT = 20; % Min temperature
maxT = 25; % Max temperature
sigmaInt = 80; % Sigma interference
sigmaOp = 80; % Sigma opacity
gain = 1.0; % Gain value
T = 0.3; % Threshold value
nAvr = 8; % number of means
% ------------------------------------------------------
[M,N] = meshgrid(-W:W, -H:H); % Meshgrid function

R = sqrt(M.^2 + N.^2); % Distance from the center

Int = normpdf(R, 0, sigmaInt); % 2D gaussian for interference
Op = normpdf(R, 0, sigmaOp); % 2D gaussian for opacity

Int = Int/max(max(Int)); % Normalization of interference gaussian
Op = Op/max(max(Op)); % Normalization of opacity gaussian

clear M N R sigmaInt sigmaOp % Delete unused variables from memory

load('MyColormaps','mycmap'); % Load colormap