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
AllPatchesMatFilename='all_patches.mat';
AllClassesMatFilename='all_classes.mat';
ClusterCentersMatFilename='cluster_centers.mat';

% ===========================================================
% LOAD FILENAMES, PATCHES, CLUSTERING RESULTS AND PATCH CLASSES
% ===========================================================
load(AllFilenamesMatFilename);
load(AllPatchesMatFilename);
load(ClusterCentersMatFilename);
load(AllClassesMatFilename);


% ===========================================================
% SHOW AN IMAGE, THE PATCHES AND THEIR CLASSES
% ===========================================================
% --- Define the selected image ID
ImID=2;

% --- Open the image and get its dimensions
I=imread(AllFilenames{ImID});
[ImRows,ImCols]=size(I);

% --- Get the class of each patch
Classes=AllClasses{ImID};

% --- Show the first 3 rows of patches
% --- Get the patch dimensions
[PatRows,PatCols]=size(AllPatches{1}{1});
% --- Calculate the number of patches in each row
PatchesInEachRow=floor(ImCols/PatCols);

% --- Show the top 3 rows of patches
figure;
%set(gcf,'units','normalized','position',[0.1 0.1 0.8 0.8]);
for i=1:3*PatchesInEachRow
    Ip=AllPatches{ImID}{i};
    
    subplot(3,PatchesInEachRow,i);   
    image(Ip);    
    text(0.5,0.5,char(num2str(Classes(i))),'color','c',...
    'verticalalignment','middle','horizontalalignment','center','units','normalized');

    axis image off;
    colormap(gray(256));
    drawnow;    
end

set(gcf,'units','normalized','position',[0.1 0.1 0.8 0.8]);

% ===========================================================
% SHOW THE HISTOGRAM OF PATCHES PER CLUSTER
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

