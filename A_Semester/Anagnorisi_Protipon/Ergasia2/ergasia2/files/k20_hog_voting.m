% --- initialize
disp('-----');
clc;
clear;
close all;
fprintf('\nCalculating please wait . . . . . .\n');
AllClassesMatFilename='hog_k20_all_classes.mat';
load(AllClassesMatFilename);

%%%%Data normalization
%%%We need to normalize the data mostly on sift cases because we are
%%%getting different dimensions on each member of AllClasses
%%%on hog the dimensions are 99 (fixed)

%%%We will find the max dimensions of the inner arrays of AllClasses
maxDimensArray = zeros(400,1);
for i = 1:length(AllClasses)
    maxDimensArray(i) = length(AllClasses{i});
end

%%%Getting the the maximum dimensions
maxDimensions = max(maxDimensArray);

%%%%%%%%Omoiothta

images = zeros(length(AllClasses),maxDimensions);
for i = 1:length(AllClasses)
    for j = 1:length(AllClasses{i})
        images(i,j) = transpose(AllClasses{i}(j));
    end
end

%%We will calculate all the scores for each image (query)
ScorePerImage = zeros(length(AllClasses),length(AllClasses));
for i = 1:length(AllClasses)
    
    query = zeros(length(AllClasses),maxDimensions);
    for j = 1:length(AllClasses) %%fill query 400 times
        for k = 1:length(AllClasses{i})
            query(j,k) = transpose(AllClasses{i}(k));
        end
        
    end
       
    Matches = images .* query;
    
    ScorePerImage(i,:)=sum(Matches,2);
    
end

%%%Experimental Results
%%%%%%%Voting

%%%Sorted
%%%Sorting results of the first image s10_01 and keeping track of the
%%%indexes
[Sorted,indexes]=sort(ScorePerImage(91,:).','descend');

%%Finding top 5
top5 = zeros(5,2);
top5(:,1) = Sorted([1 2 3 4 5]);
top5(:,2) = indexes([1 2 3 4 5]);


%%%Relevant
%%%Contains score per relevant image
%%%For example: our query is s10_01 so we will fill the array with all the
%%%scores from s10_01 to s10_10
Relevant=[ScorePerImage(91,91); ScorePerImage(91,92);ScorePerImage(91,93);ScorePerImage(91,94);ScorePerImage(91,95);ScorePerImage(91,96);ScorePerImage(91,97);ScorePerImage(91,98);ScorePerImage(91,99);ScorePerImage(91,100)];


% % --- Calculate the Precision
[~,ib]=ismember(Sorted,Relevant);
P=find(ib);

% % --- Calculate the Average Precision
AP=sum((1:length(P))'./P)/length(Relevant);


clc;

fprintf('\n------Experimental Results------\n');


fprintf('\nVoting Method for query s10_01:\n\nAverage Precision = %.4f\n\n', AP);


