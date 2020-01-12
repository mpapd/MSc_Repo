% --- initialize
disp('-----');
clc;
clear;
close all;




AllClassesMatFilename='all_classes.mat';
load(AllClassesMatFilename);


%%%%%%%%Omoiothta
%kanto gia oles tis eikones tora einai mono gia ena (s01_xx ews s10_xx)
query = [transpose(AllClasses{1});transpose(AllClasses{1});transpose(AllClasses{1})];

images = [transpose(AllClasses{1}) ;transpose(AllClasses{2});transpose(AllClasses{3})];

Matches = images .* query;
%%Score me bash thn eikona s01_01, tha to kano gia oles
ScorePerImage=sum(Matches,2)



%%%%%%%Apotimisi gia eikona s01_01

%%%Sorted
%%%Tha exei to ScorePerImage gia to query s01_xx ews s10_xx
Sorted=[ScorePerImage; ScorePerImage*2; ScorePerImage*3;ScorePerImage*4] %temp for testing

%%%Relevant
%%%Tha exei ta score olwn ton eikonon s01_01 eos s01_10 epeidh relevant sto
%%%query mas
Relevant=[ScorePerImage; ScorePerImage]

% --- Calculate the Precision
[~,ib]=ismember(Sorted,Relevant);
P=find(ib)

% --- Calculate the Average Precision
AP=sum((1:length(P))'./P)/length(Relevant)
