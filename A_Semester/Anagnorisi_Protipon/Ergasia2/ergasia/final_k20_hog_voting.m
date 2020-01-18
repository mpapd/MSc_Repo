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
[Sorted,indexes]=sort(ScorePerImage(101,:).','descend');

%%Finding top 5
top5 = zeros(5,2);
top5(:,1) = Sorted([1 2 3 4 5]);
top5(:,2) = indexes([1 2 3 4 5]);


%%%Relevant
%%%Contains score per relevant image
%%%For example: our query is s10_01 so we will fill the array with all the
%%%scores from s10_01 to s10_10
Relevant=[ScorePerImage(101,101); ScorePerImage(101,102);ScorePerImage(101,103);ScorePerImage(101,104);ScorePerImage(101,105);ScorePerImage(101,106);ScorePerImage(101,107);ScorePerImage(101,108);ScorePerImage(101,109);ScorePerImage(101,110)];


% % --- Calculate the Precision
[~,ib]=ismember(Sorted,Relevant);
P=find(ib);

% % --- Calculate the Average Precision
AP=sum((1:length(P))'./P)/length(Relevant);


clc;



%%%Voting Mean Average Precision 
APArrayVoting = zeros(length(ScorePerImage),1);
RelevantVotingArray = zeros(400,10);
for i = 1:length(ScorePerImage)
    [Sorted,indexes]=sort(ScorePerImage(i,:).','descend');
    if i/10 < 1
        RelevantVotingArray(i,:)=[ScorePerImage(i,fix(i/10) + 1); ScorePerImage(i,fix(i/10) + 2);ScorePerImage(i,fix(i/10) + 3);ScorePerImage(i,fix(i/10) + 4);ScorePerImage(i,fix(i/10) + 5);ScorePerImage(i,fix(i/10) + 6);ScorePerImage(i,fix(i/10) + 7);ScorePerImage(i,fix(i/10) + 8);ScorePerImage(i,fix(i/10) + 9);ScorePerImage(i,fix(i/10) + 10)];
    elseif not(mod(i,10) == 0) 
        RelevantVotingArray(i,:)=[ScorePerImage(i,fix(i/10)*10 + 1); ScorePerImage(i,fix(i/10)*10 + 2);ScorePerImage(i,fix(i/10)*10 + 3);ScorePerImage(i,fix(i/10)*10 + 4);ScorePerImage(i,fix(i/10)*10 + 5);ScorePerImage(i,fix(i/10)*10 + 6);ScorePerImage(i,fix(i/10)*10 + 7);ScorePerImage(i,fix(i/10)*10 + 8);ScorePerImage(i,fix(i/10)*10 + 9);ScorePerImage(i,fix(i/10)*10 + 10)];
    else
        RelevantVotingArray(i,:)=[ScorePerImage(i,fix((i-1)/10)*10 + 1); ScorePerImage(i,fix((i-1)/10)*10 + 2);ScorePerImage(i,fix((i-1)/10)*10 + 3);ScorePerImage(i,fix((i-1)/10)*10 + 4);ScorePerImage(i,fix((i-1)/10)*10 + 5);ScorePerImage(i,fix((i-1)/10)*10 + 6);ScorePerImage(i,fix((i-1)/10)*10 + 7);ScorePerImage(i,fix((i-1)/10)*10 + 8);ScorePerImage(i,fix((i-1)/10)*10 + 9);ScorePerImage(i,fix((i-1)/10)*10 + 10)];
    end
    
    % % --- Calculate the Precision
    [~,ib]=ismember(Sorted,RelevantVotingArray(i,:));
    PVotingMean=find(ib);

    % % --- Calculate the Average Precision
    APArrayVoting(i)=sum((1:length(PVotingMean))'./PVotingMean)/length(RelevantVotingArray(i,:));

    
end

fprintf('\n------Experimental Results------\n');
fprintf('\nVoting Method Mean Average Precision(MAP) = %.4f\n\n', mean(APArrayVoting));




