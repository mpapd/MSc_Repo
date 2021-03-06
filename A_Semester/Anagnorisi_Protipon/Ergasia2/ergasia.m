% --- initialize
disp('-----');
clc;
clear;
close all;
fprintf('\nCalculating please wait . . . . . .\n');
AllClassesMatFilename='all_classes.mat';
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
%%Erotima 1, o pinakas ScorePerImage exei to apotelesma tou erotimatos
%%Kathe grammh einai to kathe score ths eikonas san query
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

%%%%%%%Apotimisi gia eikona s10_01

%%%Sorted
%%%Sorting results of the first image s10_01 and keeping track of the
%%%indexes
[Sorted,indexes]=sort(ScorePerImage(101,:).','descend');


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




%%%Peiramatika apotelesmata

%%cosine
%%Opos blepeis sthn diafaneia 32, exei 2 queries 
%%Pairneis ta score ton duo kai ta anatheteis sta x kai y kai bgazeis to
%%cosine similarity
cosineResults = zeros(400,maxDimensions);
for i = 1:length(images)
    x=[images(i,:)];
    for j = 1:length(images)
        y=[images(j,:)];
        xy   = dot(x,y);
        nx   = norm(x);
        ny   = norm(y);
        nxny = nx*ny;
        Cs   = xy/nxny;
        cosineResults(i,j) = Cs;

    end
end

[SortedCos,indexesCos]=sort(cosineResults(101,:).','descend');

RelevantCos=[cosineResults(101,101); cosineResults(101,102);cosineResults(101,103);cosineResults(101,104);cosineResults(101,105);cosineResults(101,106);cosineResults(101,107);cosineResults(101,108);cosineResults(101,109);cosineResults(101,110)];


% % --- Calculate the Precision for Cosine
[~,ib]=ismember(SortedCos,RelevantCos);
PCos=find(ib);

% % --- Calculate the Average Precision for Cosine
APCos=sum((1:length(PCos))'./PCos)/length(RelevantCos);


clc;
fprintf('\n------Questions------\n');
fprintf('\n------Question 1------\n');
fprintf('\nResults for all queries are too many to show. \nPlease open ScorePerImage array to view them! \n\n');
fprintf('\n------Question 2------\n');

fprintf('\nFor query s10_01:\n\nAverage Precision = %.4f\n\n', AP);


fprintf('\n------Experimental Results------\n');
fprintf('\n------Question i------\n');

fprintf('\nCosine Method for query s10_01:\n\nAverage Precision = %.4f\n\n', APCos);
fprintf('\nVoting Method for query s10_01:\n\nAverage Precision = %.4f\n\n', AP);


%%Calculating Mean Average Precision

%%%Cosine Mean Average Precision 
APArrayCosine = zeros(length(cosineResults),1);
RelevantCosArray = zeros(400,10);
for i = 1:length(cosineResults)
    [SortedCos,indexesCos]=sort(cosineResults(i,:).','descend');
    
    if i/10 < 1
        RelevantCosArray(i,:)=[cosineResults(i,fix(i/10) + 1); cosineResults(i,fix(i/10) + 2);cosineResults(i,fix(i/10) + 3);cosineResults(i,fix(i/10) + 4);cosineResults(i,fix(i/10) + 5);cosineResults(i,fix(i/10) + 6);cosineResults(i,fix(i/10) + 7);cosineResults(i,fix(i/10) + 8);cosineResults(i,fix(i/10) + 9);cosineResults(i,fix(i/10) + 10)];
    elseif not(mod(i,10) == 0) 
        RelevantCosArray(i,:)=[cosineResults(i,fix(i/10)*10 + 1); cosineResults(i,fix(i/10)*10 + 2);cosineResults(i,fix(i/10)*10 + 3);cosineResults(i,fix(i/10)*10 + 4);cosineResults(i,fix(i/10)*10 + 5);cosineResults(i,fix(i/10)*10 + 6);cosineResults(i,fix(i/10)*10 + 7);cosineResults(i,fix(i/10)*10 + 8);cosineResults(i,fix(i/10)*10 + 9);cosineResults(i,fix(i/10)*10 + 10)];
    else
        RelevantCosArray(i,:)=[cosineResults(i,fix((i-1)/10)*10 + 1); cosineResults(i,fix((i-1)/10)*10 + 2);cosineResults(i,fix((i-1)/10)*10 + 3);cosineResults(i,fix((i-1)/10)*10 + 4);cosineResults(i,fix((i-1)/10)*10 + 5);cosineResults(i,fix((i-1)/10)*10 + 6);cosineResults(i,fix((i-1)/10)*10 + 7);cosineResults(i,fix((i-1)/10)*10 + 8);cosineResults(i,fix((i-1)/10)*10 + 9);cosineResults(i,fix((i-1)/10)*10 + 10)];
    end

    % % --- Calculate the Precision for Cosine
    [~,ib]=ismember(SortedCos,RelevantCosArray(i,:));
    PCos=find(ib);

    % % --- Calculate the Average Precision for Cosine
    APArrayCosine(i)=sum((1:length(PCos))'./PCos)/length(RelevantCosArray(i,:));
end

fprintf('\n------Question ii------\n');
fprintf('\nCosine Method Mean Average Precision(MAP) = %.4f\n\n', mean(APArrayCosine));


%%%Voting Mean Average Precision 
APArrayVoting = zeros(length(ScorePerImage),1);
RelevantVotingArray = zeros(400,10);
for i = 1:length(cosineResults)
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


fprintf('\nVoting Method Mean Average Precision(MAP) = %.4f\n\n', mean(APArrayVoting));




