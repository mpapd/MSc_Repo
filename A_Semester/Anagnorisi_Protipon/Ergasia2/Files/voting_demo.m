% --- initialize
disp('-----');
clc;
clear;
close all;

% ===========================================================
% TOY EXAMPLE
% ===========================================================
% --- A simple FLAT (not hierarchical) utilization of the example 
% --- in the presentation of Nister and Stewenius pp. 33-36
% --- nister_stewenius_cvpr2006_slides.ppt

% --- Each row is an image, each column is a cluster (visual word)
% --- For example, the first row means: the first image (duck toy) has 5 
% --- features which belong to the follogin clusters
% --- 1 visual word (feature) of cluster 4
% --- 1 visual word (feature) of cluster 5
% --- 2 visual words (features) of cluster 8
% --- 1 visual word (feature) of cluster 9
% --- In a similar way are encoded the next 3 images 

VisWordsPerImage=[
    0 0 0 1 1 0 0 2 1 %toy
    1 0 1 0 1 0 0 0 0 %horta
    0 0 1 0 0 1 1 0 0 %gala
    1 1 0 0 0 0 1 0 0 %fatsa
    
    ];

% --- Similar encoding for the query image as shown in pp. 37
VisWordsPerQuery=[
    1 0 1 0 1 0 0 0 0
    1 0 1 0 1 0 0 0 0
    1 0 1 0 1 0 0 0 0
    ];

% --- Match the query against the dataset
Matches = VisWordsPerImage .* VisWordsPerQuery;

% --- Find the score per image by horizontal summation
ScorePerImage=sum(Matches,2)


