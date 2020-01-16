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
    pkg load image;
    warning on;
end

% --- Define filenames of saved data
AllFilenamesMatFilename='all_filenames.mat';
AllPointsMatFilename='all_points.mat';
AllFeaturesMatFilename='all_features.mat';

% ===========================================================
% LOAD DATA IF ALREADY AVAILABLE
% ===========================================================
% --- Read filenames, points and features from files (if available)
if exist(AllFilenamesMatFilename,'file')
    % --- COMMENT OUT THE NEXT 5 LINES TO FORCE CALCULATIONS FROM SCRATCH    
%     load(AllFilenamesMatFilename);
%     load(AllPointsMatFilename);
%     load(AllFeaturesMatFilename);
%     fprintf('--- Filenames, Points and Features loaded ---\n');
%     return;
end

% ===========================================================
% GET IMAGES DATA AND INFO
% ===========================================================

fprintf('--- Get Filenames ---\n');
% --- Get the images filenames
ImagesFolder='.\Faces_dataset_ATT';
ImagesFilter='*.pgm';
s=dir(fullfile(ImagesFolder,ImagesFilter));
AllFilenames=strcat(cellstr(ImagesFolder),filesep,{s.name}');
% COMMENT OUT THE NEXT LINE IN ORDER TO CALCULATE ALL THE IMAGES 
% AllFilenames=AllFilenames(1:5);

% --- Get the number of images
Nimages=length(AllFilenames);

% ===========================================================
% CALCULATE POINTS AND FEATURES
% ===========================================================
% --- Initialize the features and the patches arrays
AllFeatures=cell(Nimages,1);
AllPoints=cell(Nimages,1);
% --- For each image
fprintf('--- Extract Points and Features ---\n');
for i=1:Nimages
    % --- Read the image
    disp(AllFilenames{i});
    I=imread(AllFilenames{i});
    % --- Get the features vector of the image
    [Features,Points]=sift_lowe_func(I);
    % fix [y x scale orientation] to [x y scale orientation]
    Points=Points(:,[2 1 3 4]);
    
    % --- Keep the points of this image
    AllPoints{i}=Points;
    % --- Keep the features of this image
    AllFeatures{i}=Features;
end
% --- Save the features and points to files
if exist('OCTAVE_VERSION', 'builtin')>0
    % --- If in Octave then save to mat files compatible with Matlab
    save('-mat7-binary',AllFilenamesMatFilename,'AllFilenames');
    save('-mat7-binary',AllPointsMatFilename,'AllPoints');
    save('-mat7-binary',AllFeaturesMatFilename,'AllFeatures');
else
    save(AllFilenamesMatFilename,'AllFilenames');
    save(AllPointsMatFilename,'AllPoints');
    save(AllFeaturesMatFilename,'AllFeatures');
end
fprintf('--- Filenames, Points and Features saved ---\n');
