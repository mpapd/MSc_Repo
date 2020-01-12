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
AllPatchesMatFilename='all_patches.mat';
AllFeaturesMatFilename='all_features.mat';

% ===========================================================
% LOAD DATA IF ALREADY AVAILABLE
% ===========================================================
% --- Read filenames, points and features from files (if available)
if exist(AllFilenamesMatFilename,'file')
    % --- COMMENT OUT THE NEXT 5 LINES TO FORCE CALCULATIONS FROM SCRATCH 
    %load(AllFilenamesMatFilename);
    %load(AllPatchesMatFilename);
    %load(AllFeaturesMatFilename);
    %fprintf('--- Filenames, Points and Features loaded ---\n');
    %return;
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
AllFilenames=AllFilenames(1:3); 

% --- Get the number of images
Nimages=length(AllFilenames);

% --- Define patch dimensions
PatCols=10; % Patch width (columns)
PatRows=10; % patch height (rows)

% --- Get the image dimensions
% --- NOTICE: All images are assumed to have the SAME size
I=imread(AllFilenames{1});
[Rows,Cols]=size(I);

% --- Get the number of patcher per image
Npatches=floor(Rows/PatRows)*floor(Cols/PatCols);

% ===========================================================
% CALCULATE PATCHES AND FEATURES
% ===========================================================
% --- Initialize the features and the patches arrays
AllPatches=cell(Nimages,1);
AllFeatures=cell(Nimages,1);
% --- For each image
fprintf('--- Extract Patches and Features ---\n');
for i=1:Nimages
    % --- Read the image
    disp(AllFilenames{i});
    I=imread(AllFilenames{i});
    k=1;
    % --- Get its patches
    Patches=cell(Npatches,1);
    for r=1:PatRows:Rows-PatRows
        for c=1:PatCols:Cols-PatCols
            Patches{k}=I(r:r+PatRows-1,c:c+PatCols-1);
            k=k+1;
        end
    end
    
    % --- For each patch get its features vector
    ImageFeatures=[];
    for j=1:Npatches
        % --- Get the features vector of the patch
        Features=hog(Patches{j});
        % --- Add the vector to the ImageFeatures array
        ImageFeatures=[ImageFeatures;Features(:)'];
    end
    
    % --- Keep the patches of this image
    AllPatches{i}=Patches;
    % --- Keep the features of this image
    AllFeatures{i}=ImageFeatures;
end
% --- Save the features and patches to files
if exist('OCTAVE_VERSION', 'builtin')>0
    % --- If in Octave then save to mat files compatible with Matlab
    save('-mat7-binary',AllFilenamesMatFilename,'AllFilenames');
    save('-mat7-binary',AllPatchesMatFilename,'AllPatches');
    save('-mat7-binary',AllFeaturesMatFilename,'AllFeatures');
else
    save(AllFilenamesMatFilename,'AllFilenames');
    save(AllPatchesMatFilename,'AllPatches');
    save(AllFeaturesMatFilename,'AllFeatures');
end
fprintf('--- Filenames, Points and Features saved ---\n');
