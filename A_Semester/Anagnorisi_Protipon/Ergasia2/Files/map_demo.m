% --- initialize
disp('-----');
clc;
clear;
close all;

% ===========================================================
% TOY EXAMPLE WITH NUMERICAL DATA
% ===========================================================
% --- Example of lecture notes
% --- Lec03 Ανάκτηση εικόνων.pdf
% --- pp. 41

SortedID=[
    588
    576
    589
    342
    590
    717
    984
    772
    321
    498
    113
    628
    777
    592
    ];

RelevantID=[
    321
    588
    589
    590
    592
    772
    ];

% --- Calculate the Precision
[~,ib]=ismember(SortedID,RelevantID);
P1=find(ib)

% --- Calculate the Average Precision
AP1=sum((1:length(P1))'./P1)/length(RelevantID)


% ===========================================================
% TOY EXAMPLE WITH TEXT DATA
% ===========================================================
% --- Toy example where the sorted items as well as the relevant items
% --- are strings, e.g. filenames
% --- In the below toy example, we suppose a dataset with 10 images from person
% --- "s01" and 10 images from person "s02"
% --- Let suppose, the query is face image 's01 01.pgm'
% --- Thus, we want to retrieve all the images of "s01"
% --- A ranking algorithm produces the ranked results in SortedNames
% --- The correct results (ground truth) are given in RelevantNames
% --- At the end the Average Precision is calculated

SortedNames={
    's01 01.pgm'
    's01 06.pgm'
    's02 05.pgm'
    's01 04.pgm'
    's01 05.pgm'
    's02 04.pgm'
    's01 07.pgm'
    's02 10.pgm'
    's02 03.pgm'
    's02 06.pgm'
    's01 08.pgm'
    's01 09.pgm'
    's02 01.pgm'
    's01 03.pgm'
    's02 02.pgm'
    's01 02.pgm'
    's02 07.pgm'
    's01 10.pgm'
    's02 08.pgm'
    's02 09.pgm'
    };

RelevantNames={
    's01 01.pgm'
    's01 02.pgm'
    's01 03.pgm'
    's01 04.pgm'
    's01 05.pgm'
    's01 06.pgm'
    's01 07.pgm'
    's01 08.pgm'
    's01 09.pgm'
    's01 10.pgm'
    };




% --- Calculate the Precision
[~,ib]=ismember(SortedNames,RelevantNames);
P2=find(ib)

% --- Calculate the Average Precision
AP2=sum((1:length(P2))'./P2)/length(RelevantNames)

