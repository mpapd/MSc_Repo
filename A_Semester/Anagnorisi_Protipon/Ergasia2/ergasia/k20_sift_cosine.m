% --- initialize
disp('-----');
clc;
clear;
close all;

fprintf('\nCalculating please wait . . . . . .\n');
AllClassesMatFilename='sift_k20_all_classes.mat';
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

%%Cosine
cosineResults = zeros(length(AllClasses),length(AllClasses));
for i = 1:length(images)
    x=[images(i,:)];
%     for j = 1:length(images)
%         y=[images(j,:)];
%         xy   = dot(x,y);
%         nx   = norm(x);
%         ny   = norm(y);
%         nxny = nx*ny;
%         Cs   = xy/nxny;
%         cosineResults(i,:) = Cs;
%         
%     end
    cosineResults(i,:) = 1 - pdist2(x,images,'cosine')';
end


[SortedCos,indexesCos]=sort(cosineResults(91,:).','descend');

%%Finding top 5
top5 = zeros(5,2);
top5(:,1) = SortedCos([1 2 3 4 5]);
top5(:,2) = indexesCos([1 2 3 4 5]);

RelevantCos=[cosineResults(91,91); cosineResults(91,92);cosineResults(91,93);cosineResults(91,94);cosineResults(91,95);cosineResults(91,96);cosineResults(91,97);cosineResults(91,98);cosineResults(91,99);cosineResults(91,100)];


% % --- Calculate the Precision for Cosine
[~,ib]=ismember(SortedCos,RelevantCos);
PCos=find(ib);

% % --- Calculate the Average Precision for Cosine
APCos=sum((1:length(PCos))'./PCos)/length(RelevantCos);


clc;

fprintf('\n------Experimental Results------\n');


fprintf('\nCosine Method for query s10_01:\n\nAverage Precision = %.4f\n\n', APCos);


