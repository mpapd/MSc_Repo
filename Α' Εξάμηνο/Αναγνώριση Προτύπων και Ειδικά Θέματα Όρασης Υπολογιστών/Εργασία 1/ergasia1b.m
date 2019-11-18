clc;
clear;
close all;

% ===========================================================
% INIT
% ===========================================================


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


% ----- Question 1 -----
% Prior of class No 
P(1)=NC(1)/N;
% Prior of class Yes 
P(2)=NC(2)/N;

% Show priors
fprintf('\n----- Question 1 -----\n');
fprintf('P(%s) = %d/%d = %0.4f\n',C{1},NC(1),N,P(1));
fprintf('P(%s) = %d/%d = %0.4f\n',C{2},NC(2),N,P(2));
fprintf('\n');

% Conditional probabilities p(Owner=Yes|Class=No)
Nxc(1,1)=sum(strcmpi(Owner,T{1}) & strcmpi(Class,C{1}));
pxc(1,1)=Nxc(1,1)/NC(1);
fprintf('p(Owner=Yes|Class=No) => p(%s|%s) = %d/%d = %0.4f\n',T{1},C{1},Nxc(1,1),NC(1),pxc(1,1));
% Conditional probabilities p(Status=Divorced|Class=No)
Nxc(2,1)=sum(strcmpi(Status,T{2}) & strcmpi(Class,C{1}));
pxc(2,1)=Nxc(2,1)/NC(1);
fprintf('p(Status=Divorced|Class=No)=> p(%s|%s) = %d/%d = %0.4f\n',T{2},C{1},Nxc(2,1),NC(1),pxc(2,1));
% Conditional probabilities p(Income=100|Class=No)
idx=find(strcmpi(Class,C{1}));
mu=mean(Income(idx));
sdev=std(Income(idx));
pxc(3,1)=normpdf(T{3},mu,sdev);
fprintf('p(Income=100|Class=No)=> p(%d|%s) = %0.4f\n',T{3},C{1},pxc(3,1));
fprintf('\n');

% Conditional probabilities p(Owner=Yes|Class=Yes)
Nxc(1,2)=sum(strcmpi(Owner,T{1}) & strcmpi(Class,C{2}));
pxc(1,2)=Nxc(1,2)/NC(2);
fprintf('p(Owner=Yes|Class=Yes)=> p(%s|%s) = %d/%d = %0.4f\n',T{1},C{2},Nxc(1,2),NC(2),pxc(1,2));
% Conditional probabilities p(Status=Divorced|Class=Yes)
Nxc(2,2)=sum(strcmpi(Status,T{2}) & strcmpi(Class,C{2}));
pxc(2,2)=Nxc(2,2)/NC(2);
fprintf('p(Status=Divorced|Class=Yes)=> p(%s|%s) = %d/%d = %0.4f\n',T{2},C{2},Nxc(2,2),NC(2),pxc(2,2));
% Conditional probabilities p(Income=100|Class=Yes)
idx=find(strcmpi(Class,C{2}));
mu=mean(Income(idx));
sdev=std(Income(idx));
pxc(3,2)=normpdf(T{3},mu,sdev);
fprintf('p(Income=100|Class=Yes)=> p(%d|%s) = %0.4f\n',T{3},C{2},pxc(3,2));
fprintf('\n');

% Posterior probability p(No|No,Divorced,100)
pcx(1)=prod(pxc(:,1))*P(1);
fprintf('The posterior probability for class %s is %.4f\n',C{1},pcx(1));
% Posterior probability p(Yes|No,Divorced,100)
pcx(2)=prod(pxc(:,2))*P(2);
fprintf('The posterior probability for class %s is %.4f\n',C{2},pcx(2));


% ----- Question 2 -----
fprintf('\n----- Question 2 -----\n');

% %Our goal is to build :
% %p(Class = No|X) = p(X|Class=No) * p(Class = No) / p(X) 
% %p(Class = Yes |X) = p(X|Class=Yes) * p(Class = Yes) / p(X) 
% %p(Owner=Yes|Class=No) = pxc(1,1)
% %p(Status=Divorced||Class=No) = pxc(1,1)
% %p(Income=100|Class=No) = pxc(3,1)
% %p(X) = p(Owner=Yes) * p(Status=Divorced) * p(Income=100)

% %Calculating p(X)
% %p(Owner=Yes) = sum(strcmpi(Owner,T{1})
p_owner_yes = sum(strcmpi(Owner,T{1})) / NC(1) ;


% %p(Status=Divorced)
p_status_divorced = sum(strcmpi(Status,T{2})) / NC(1);



% %p(Income=100)
p_income_100 = numel(find(Income==T{3})) / NC(1);

% %p(X) for normalization
px = p_owner_yes * p_status_divorced * p_income_100;


% %Calculating p(X|Class=No)
% %Our goal is to build :
% %p(X|Class=No) = p(Owner = Yes|Class=No) * p(Status=Divorced|Class=No) * p(Income=100|Class=No) 
% %p(X|Class=No) = pxc(1,1) * pxc(2,1) * pxc(3,1)
px_no = pxc(1,1) * pxc(2,1) * pxc(3,1);
px_yes = pxc(1,2) * pxc(2,2) * pxc(3,2);


% %p(Class = No) = P(2)
p_no_x = px_no * P(1);
% %p(Class = Yes) = P(2)
p_yes_x = px_yes * P(2);
fprintf('\n\t p(Class=No|X) = %.4f\n',p_no_x);
fprintf('\n\t p(Class=Yes|X) = %.4f\n',p_yes_x);

if(p_no_x > p_yes_x)
  fprintf('\n\t Sample x = {Yes,Divorced,100}, belongs to p(Class=No) \n');
else
  fprintf('\n\t Sample x = {Yes,Divorced,100}, belongs to p(Class=Yes) \n');
end


% ----- Question 4 -----
fprintf('\n----- Question 4 -----\n');


% %Calculating new pxc
% %Laplacian smoothing
m = 1;

% Conditional probabilities p(Owner=Yes|Class=No) with Laplacian smoothing
Nxc(1,1)=sum(strcmpi(Owner,T{1}) & strcmpi(Class,C{1}));
Nxc(1,1) = Nxc(1,1) + m;
NC_No_laplacian = NC(1) + 2*m;
pxc(1,1)=Nxc(1,1)/NC_No_laplacian;
% Conditional probabilities p(Status=Divorced|Class=No) with Laplacian smoothing
Nxc(2,1)=sum(strcmpi(Status,T{2}) & strcmpi(Class,C{1}));
Nxc(2,1) = Nxc(2,1) + m;
NC_No_laplacian = NC(1) + 3*m;
pxc(2,1)=Nxc(2,1)/NC_No_laplacian;


% Conditional probabilities p(Owner=Yes|Class=Yes) with Laplacian smoothing
Nxc(1,2)=sum(strcmpi(Owner,T{1}) & strcmpi(Class,C{2}));
Nxc(1,2) = Nxc(1,2) + m;
NC_Yes_laplacian = NC(2) + 2*m;
pxc(1,2)=Nxc(1,2)/NC_Yes_laplacian;
% Conditional probabilities p(Status=Divorced|Class=Yes) with Laplacian smoothing
Nxc(2,2)=sum(strcmpi(Status,T{2}) & strcmpi(Class,C{2}));
Nxc(2,2) = Nxc(2,2) + m;
NC_Yes_laplacian = NC(2) + 3*m;
pxc(2,2)=Nxc(2,2)/NC_Yes_laplacian;


fprintf('\n\t For Laplacian smoothing = %g\n',m);
% %Calculating p(Class=No|X) with Laplacian smoothing
px_no_laplace = pxc(1,1) * pxc(2,1) * pxc(3,1);
p_no_x_laplace = px_no_laplace * P(1);

% %Calculating p(Class=Yes|X) with Laplacian smoothing
px_yes_laplace = pxc(1,2) * pxc(2,2) * pxc(3,2);
p_yes_x_laplace = px_yes_laplace * P(2);

fprintf('\n\t p(Class=No|X) = %0.4f\n',p_no_x_laplace);
fprintf('\n\t p(Class=Yes|X) = %0.4f\n',p_yes_x_laplace);

if(p_no_x_laplace > p_yes_x_laplace)
  fprintf('\n\t Laplacian smoothing: \n\t\tSample x = {Yes,Divorced,100}, belongs to p(Class=No) \n');
else
  fprintf('\n\t Laplacian smoothing: \n\t\tSample x = {Yes,Divorced,100}, belongs to p(Class=Yes) \n');
end








% ----- Question 5 -----
fprintf('\n----- Question 5 -----\n');


% %Calculating new pxc
% %Laplacian smoothing
m = 10000;

% Conditional probabilities p(Owner=Yes|Class=No) with Laplacian smoothing
Nxc(1,1)=sum(strcmpi(Owner,T{1}) & strcmpi(Class,C{1}));
Nxc(1,1) = Nxc(1,1) + m;
NC_No_laplacian = NC(1) + 2*m;
pxc(1,1)=Nxc(1,1)/NC_No_laplacian;
% Conditional probabilities p(Status=Divorced|Class=No) with Laplacian smoothing
Nxc(2,1)=sum(strcmpi(Status,T{2}) & strcmpi(Class,C{1}));
Nxc(2,1) = Nxc(2,1) + m;
NC_No_laplacian = NC(1) + 3*m;
pxc(2,1)=Nxc(2,1)/NC_No_laplacian;


% Conditional probabilities p(Owner=Yes|Class=Yes) with Laplacian smoothing
Nxc(1,2)=sum(strcmpi(Owner,T{1}) & strcmpi(Class,C{2}));
Nxc(1,2) = Nxc(1,2) + m;
NC_Yes_laplacian = NC(2) + 2*m;
pxc(1,2)=Nxc(1,2)/NC_Yes_laplacian;
% Conditional probabilities p(Status=Divorced|Class=Yes) with Laplacian smoothing
Nxc(2,2)=sum(strcmpi(Status,T{2}) & strcmpi(Class,C{2}));
Nxc(2,2) = Nxc(2,2) + m;
NC_Yes_laplacian = NC(2) + 3*m;
pxc(2,2)=Nxc(2,2)/NC_Yes_laplacian;


fprintf('\n\t For Laplacian smoothing = %g\n',m);
% %Calculating p(Class=No|X) with Laplacian smoothing
px_no_laplace = pxc(1,1) * pxc(2,1) * pxc(3,1);
p_no_x_laplace = px_no_laplace * P(1);

% %Calculating p(Class=Yes|X) with Laplacian smoothing
px_yes_laplace = pxc(1,2) * pxc(2,2) * pxc(3,2);
p_yes_x_laplace = px_yes_laplace * P(2);

fprintf('\n\t p(Class=No|X) = %0.4f\n',p_no_x_laplace);
fprintf('\n\t p(Class=Yes|X) = %0.4f\n',p_yes_x_laplace);

if(p_no_x_laplace > p_yes_x_laplace)
  fprintf('\n\t Laplacian smoothing: \n\t\tSample x = {Yes,Divorced,100}, belongs to p(Class=No) \n');
else
  fprintf('\n\t Laplacian smoothing: \n\t\tSample x = {Yes,Divorced,100}, belongs to p(Class=Yes) \n');
end














