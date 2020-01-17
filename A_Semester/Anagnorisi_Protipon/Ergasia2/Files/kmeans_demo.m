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
    pkg load statistics;
    warning on;
end

% --- Define filenames of saved data
AllFeaturesMatFilename='all_features.mat';
ClusterCentersMatFilename='cluster_centers.mat';
AllClassesMatFilename='all_classes.mat';



% ===========================================================
% LOAD CLUSTERING RESULTS IF ALREADY AVAILABLE
% ===========================================================
% --- Read the classes of each feature from file (if available)
if exist(AllClassesMatFilename,'file')
    % --- COMMENT OUT THE NEXT 5 LINES TO FORCE CALCULATIONS FROM SCRATCH
    %load(ClusterCentersMatFilename);
    %fprintf('--- Cluster centers loaded ---\n');
    %load(AllClassesMatFilename);
    %fprintf('--- Classes per image loaded ---\n');
    %return;
end

% ===========================================================
% LOAD FEATURES
% ===========================================================
% --- Load the AllFeatures cell variable
% --- AllFeatures{1} contains the N1 features of the 1st image
% --- AllFeatures{2} contains the N2 features of the 2nd image
% --- etc
load(AllFeaturesMatFilename)

% --- Merge all the features in a single table
AllFeaturesArr=cell2mat(AllFeatures);



% ===========================================================
% APPLY K-MEANS
% ===========================================================

% --- Define K
K=100;

% --- Temporarily disable warnings for failing to converge in 1000 iterations
warning off;
% --- Apply K-Means clustering
% --- ClassID is the class where each keypoint belongs
% --- ClassCenters is the position of each class's center
fprintf('--- Apply K-Means ---\n')
[ClassID,ClassCenters]=kmeans(AllFeaturesArr,K,'MaxIter',1000,'Replicates',3,'display','final')



% --- Enable warnings
warning on;
% --- Save the clustering results to file
if exist('OCTAVE_VERSION', 'builtin')>0
    save('-mat7-binary',ClusterCentersMatFilename,'ClassCenters');
else
    save(ClusterCentersMatFilename,'ClassCenters');
end
fprintf('--- Cluster centers saved ---\n');

Nimages=length(AllFeatures);

% --- Get the number of features per image
FeaturesPerImage=cell2mat(cellfun(@(x) size(x,1),AllFeatures,'UniformOutput',false));
% --- Get the image to ehich each feature belongs
ImageOfPoint=cell2mat(cellfun(@(x,y) y*ones(x,1),num2cell(FeaturesPerImage),num2cell((1:length(FeaturesPerImage))'),'UniformOutput',false));

% --- For each image find the class of all its features
% --- AllClasses{1} contains the class label for all the features of the 1st image
% --- AllClasses{2} contains the class label for all the features of the 2nd image
% --- etc
AllClasses=cell(Nimages,1);
for i=1:Nimages
    AllClasses{i}=ClassID(ImageOfPoint==i);
end

% --- Save the classes per image to file
if exist('OCTAVE_VERSION', 'builtin')>0
    save('-mat7-binary',AllClassesMatFilename,'AllClasses');
else
    save(AllClassesMatFilename,'AllClasses');
end
fprintf('--- Classes per image saved ---\n');
