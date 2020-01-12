% --- initialize
disp('-----');
clc;
clear;
close all;

% ===========================================================
% INIT
% ===========================================================

if exist('OCTAVE_VERSION', 'builtin')>0
    % If in OCTAVE load the statistics package
    warning off;
    pkg load image;
    warning on;
end

% --- Define filenames of saved data
AllFilenamesMatFilename='all_filenames.mat';
AllPointsMatFilename='all_points.mat';
AllClassesMatFilename='all_classes.mat';
ClusterCentersMatFilename='cluster_centers.mat';

% ===========================================================
% LOAD FILENAMES AND SIFT POINTS
% ===========================================================
load(AllFilenamesMatFilename);
load(AllPointsMatFilename);
load(AllClassesMatFilename);
load(ClusterCentersMatFilename);


% ===========================================================
% SHOW AN IMAGE, THE KEYPOINTS AND THEIR CLASSES
% ===========================================================
% --- Define the selected image ID
ImID=1;

% --- open and show the image
I=imread(AllFilenames{ImID});

figure;
image(I);
axis image off;
colormap(gray(256));
hold on;

% --- Get and show the keypoints
Points=AllPoints{ImID};
plot(Points(:,1),Points(:,2),'.r','markersize',10);

% --- Get and show the class of each keypoint
Classes=AllClasses{ImID};
text(Points(:,1),Points(:,2),char(num2str(Classes)),'color','c',...
    'verticalalignment','bottom','horizontalalignment','center');

set(gcf,'units','normalized','position',[0.1 0.1 0.8 0.8]);

% ===========================================================
% SHOW THE NUMBER OF KEYPOINTS PER CLUSTER
% ===========================================================

% --- Get the number of classes
K=size(ClassCenters,1);

% --- Calculate the histogram
HistValue=hist(Classes,1:K);

% --- Show the histogram
figure;
bar(HistValue,'edgecolor','none');
title('Visual word occurrences');
xlabel('Visual word index');
ylabel('Frequency of occurrence');

