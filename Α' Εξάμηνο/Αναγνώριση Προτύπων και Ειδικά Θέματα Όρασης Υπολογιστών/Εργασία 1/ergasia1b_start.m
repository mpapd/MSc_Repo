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
    warning on;
else
    % If in MATLAB prevent legend from auto updating (in recent Matlab versions)
    set(groot,'defaultLegendAutoUpdate','off'); 
end

% ===========================================================
% DATA
% ===========================================================

fid = fopen('naive_data.txt');
FormatStyle='%s %s %s %s';
% Read the header line
H = textscan(fid,'%s %s %s %s',1,'delimiter',',');
% Read the data
Data = textscan(fid,'%s %s %f %s','delimiter',',');
fclose(fid);
% Class names
C={'No','Yes'};
% Test sample
T={'Yes','Divorced',100};

% ===========================================================
% MAIN
% ===========================================================

% Get the data per feature
Owner=Data{1};
Status=Data{2};
Income=Data{3};
Class=Data{4};

% Count of all entries
N=length(Class);
fprintf('Overall entries N = %d\n',N);
fprintf('\n');
fprintf('Classes: %s\n',strjoin(C,', '));
fprintf('\n');

% Count of Class No entries
NC(1)=sum(strcmpi(Class,C{1}));
% Count of Class Yes entries
NC(2)=sum(strcmpi(Class,C{2}));

% Prior of class No 
P(1)=NC(1)/N;
% Prior of class Yes 
P(2)=NC(2)/N;

% Show priors
fprintf('P(%s) = %d/%d = %0.4f\n',C{1},NC(1),N,P(1));
fprintf('P(%s) = %d/%d = %0.4f\n',C{2},NC(2),N,P(2));
fprintf('\n');

% Conditional probabilities p(Owner=No|Class=No)
Nxc(1,1)=sum(strcmpi(Owner,T{1}) & strcmpi(Class,C{1}));
pxc(1,1)=Nxc(1,1)/NC(1);
fprintf('p(%s|%s) = %d/%d = %0.4f\n',T{1},C{1},Nxc(1,1),NC(1),pxc(1,1));
% Conditional probabilities p(Status=Divorced|Class=No)
Nxc(2,1)=sum(strcmpi(Status,T{2}) & strcmpi(Class,C{1}));
pxc(2,1)=Nxc(2,1)/NC(1);
fprintf('p(%s|%s) = %d/%d = %0.4f\n',T{2},C{1},Nxc(2,1),NC(1),pxc(2,1));
% Conditional probabilities p(Income=100|Class=No)
idx=find(strcmpi(Class,C{1}));
mu=mean(Income(idx));
sdev=std(Income(idx));
pxc(3,1)=normpdf(T{3},mu,sdev);
fprintf('p(%d|%s) = %0.4f\n',T{3},C{1},pxc(3,1));
fprintf('\n');

% Conditional probabilities p(Owner=No|Class=Yes)
Nxc(1,2)=sum(strcmpi(Owner,T{1}) & strcmpi(Class,C{2}));
pxc(1,2)=Nxc(1,2)/NC(2);
fprintf('p(%s|%s) = %d/%d = %0.4f\n',T{1},C{2},Nxc(1,2),NC(2),pxc(1,2));
% Conditional probabilities p(Status=Divorced|Class=Yes)
Nxc(2,2)=sum(strcmpi(Status,T{2}) & strcmpi(Class,C{2}));
pxc(2,2)=Nxc(2,2)/NC(2);
fprintf('p(%s|%s) = %d/%d = %0.4f\n',T{2},C{2},Nxc(2,2),NC(2),pxc(2,2));
% Conditional probabilities p(Income=100|Class=Yes)
idx=find(strcmpi(Class,C{2}));
mu=mean(Income(idx));
sdev=std(Income(idx));
pxc(3,2)=normpdf(T{3},mu,sdev);
fprintf('p(%d|%s) = %0.4f\n',T{3},C{2},pxc(3,2));
fprintf('\n');

% Posterior probability p(No|No,Divorced,100)
pcx(1)=prod(pxc(:,1))*P(1);
fprintf('The posterior probability for class %s is %0.4f\n',C{1},pcx(1));
% Posterior probability p(Yes|No,Divorced,100)
pcx(2)=prod(pxc(:,2))*P(2);
fprintf('The posterior probability for class %s is %0.4f\n',C{2},pcx(2));
