% --- initialize
disp('-----');
clc;
clear;
close all;
fprintf('\nCalculating please wait . . . . . .\n');
AllClassesMatFilename='CLASS_all_classes.mat';
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
%%Opos blepeis sthn diafaneia 32, exei 2 queries 
%%Pairneis ta score ton duo kai ta anatheteis sta x kai y kai bgazeis to
%%cosine similarity
cosineResults = zeros(length(AllClasses),length(AllClasses));
for i = 1:length(images(:,1))
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
    cosineResults(i,:) = 1 - pdist2(x,images,'cosine');
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


%%Calculating Mean Average Precision

%%%Cosine Mean Average Precision 
APArrayCosine = zeros(length(cosineResults),1);
RelevantCosArray = zeros(length(cosineResults),11);
for i = 1:length(cosineResults)
    [SortedCos,indexesCos]=sort(cosineResults(i,:).','descend');
    
    if i >= 1 && i <10
        RelevantCosArray(i,:)=[cosineResults(i,1);cosineResults(i,2);cosineResults(i,3);cosineResults(i,4);cosineResults(i,5);cosineResults(i,6);cosineResults(i,7);cosineResults(i,8);cosineResults(i,9);0;0];
    elseif i>=10 && i<18
        RelevantCosArray(i,:)=[cosineResults(i,10);cosineResults(i,11);cosineResults(i,12);cosineResults(i,13);cosineResults(i,14);cosineResults(i,15);cosineResults(i,16);cosineResults(i,17);0;0;0];
    elseif i>=18 && i<24
        RelevantCosArray(i,:)=[cosineResults(i,18);cosineResults(i,19);cosineResults(i,20);cosineResults(i,21);cosineResults(i,22);cosineResults(i,23);0;0;0;0;0];
    elseif i>=24 && i<33
        RelevantCosArray(i,:)=[cosineResults(i,24);cosineResults(i,25);cosineResults(i,26);cosineResults(i,27);cosineResults(i,28);cosineResults(i,29);cosineResults(i,30);cosineResults(i,31);cosineResults(i,32);0;0];
    elseif i>=33 && i<44
        RelevantCosArray(i,:)=[cosineResults(i,33);cosineResults(i,34);cosineResults(i,35);cosineResults(i,36);cosineResults(i,37);cosineResults(i,38);cosineResults(i,39);cosineResults(5,40);cosineResults(i,41);cosineResults(i,42);cosineResults(i,43)];
    elseif i>=44 && i<50
         RelevantCosArray(i,:)=[cosineResults(i,44);cosineResults(i,45);cosineResults(i,46);cosineResults(i,47);cosineResults(i,48);cosineResults(i,49);0;0;0;0;0];    
    elseif i>=50 && i<57
         RelevantCosArray(i,:)=[cosineResults(i,50);cosineResults(i,51);cosineResults(i,52);cosineResults(i,53);cosineResults(i,54);0;0;0;0;0;0];    
    elseif i>=57 && i<62
        RelevantCosArray(i,:)=[cosineResults(i,57);cosineResults(i,58);cosineResults(i,59);cosineResults(i,60);cosineResults(i,61);0;0;0;0;0;0];  
    elseif i>=62 && i<67
        RelevantCosArray(i,:)=[cosineResults(i,62);cosineResults(i,63);cosineResults(i,64);cosineResults(i,65);cosineResults(i,66);0;0;0;0;0;0];  
    elseif i>=67 && i<76
        RelevantCosArray(i,:)=[cosineResults(i,67);cosineResults(i,68);cosineResults(i,69);cosineResults(i,70);cosineResults(i,71);cosineResults(10,72);cosineResults(i,73);cosineResults(i,74);cosineResults(i,75);0;0];  
    elseif i>=76 && i<81
        RelevantCosArray(i,:)=[cosineResults(i,76);cosineResults(i,77);cosineResults(i,78);cosineResults(i,79);cosineResults(i,80);0;0;0;0;0;0];          
    elseif i>=81 && i<89
        RelevantCosArray(i,:)=[cosineResults(i,81);cosineResults(i,82);cosineResults(i,83);cosineResults(i,84);cosineResults(i,85);cosineResults(i,86);cosineResults(i,87);0;0;0;0];  
    elseif i>=89 && i<97
        RelevantCosArray(i,:)=[cosineResults(i,89);cosineResults(i,90);cosineResults(i,91);cosineResults(i,92);cosineResults(i,93);cosineResults(i,94);cosineResults(i,95);cosineResults(i,96);0;0;0];  
    elseif i>=97 && i<103
         RelevantCosArray(i,:)=[cosineResults(i,97);cosineResults(i,98);cosineResults(i,99);cosineResults(i,100);cosineResults(i,101);cosineResults(i,102);0;0;0;0;0];  
    elseif i>=103 && i<109
         RelevantCosArray(i,:)=[cosineResults(i,103);cosineResults(i,104);cosineResults(i,105);cosineResults(i,106);cosineResults(15,107);cosineResults(15,108);0;0;0;0;0];
    elseif i>=109 && i<112
        RelevantCosArray(i,:)=[cosineResults(i,109);cosineResults(i,110);cosineResults(i,111);0;0;0;0;0;0;0;0];
    elseif i>=112 && i<114
        RelevantCosArray(i,:)=[cosineResults(i,112);cosineResults(i,113);0;0;0;0;0;0;0;0;0];
    elseif i>=114 && i<116
        RelevantCosArray(i,:)=[cosineResults(i,114);cosineResults(i,115);0;0;0;0;0;0;0;0;0];
    elseif i>=116 && i<118
        RelevantCosArray(i,:)=[cosineResults(i,116);cosineResults(i,117);0;0;0;0;0;0;0;0;0];
    elseif i>=118 && i<120
        RelevantCosArray(i,:)=[cosineResults(i,118);cosineResults(i,119);0;0;0;0;0;0;0;0;0];
    elseif i>=120 && i<122
        RelevantCosArray(i,:)=[cosineResults(i,120);cosineResults(i,121);0;0;0;0;0;0;0;0;0];
    elseif i>=122 && i<124
        RelevantCosArray(i,:)=[cosineResults(i,122);cosineResults(i,123);0;0;0;0;0;0;0;0;0];
    elseif i>=124 && i<127
        RelevantCosArray(i,:)=[cosineResults(i,124);cosineResults(i,125);cosineResults(i,126);0;0;0;0;0;0;0;0];
    elseif i>=127 && i<129
        RelevantCosArray(i,:)=[cosineResults(i,127);cosineResults(i,128);0;0;0;0;0;0;0;0;0];
    elseif i==129
        RelevantCosArray(i,:)=[cosineResults(i,129);0;0;0;0;0;0;0;0;0;0];
    end

    % % --- Calculate the Precision for Cosine
    [~,ib]=ismember(SortedCos,RelevantCosArray(i,:));
    PCos=find(ib);

    % % --- Calculate the Average Precision for Cosine
    APArrayCosine(i)=sum((1:length(PCos))'./PCos)/length(RelevantCosArray(i,:));
end

fprintf('\n------Experimental Results------\n');
fprintf('\nCosine Method Mean Average Precision(MAP) = %.4f\n\n', mean(APArrayCosine));





