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

% Priors
Pc=[0.3 0.7];

% Class conditionals (mean,std^2)
mu=[8 4];
sdev=[1 2];

% Loss function
L=[
    0       3
    1       0
    ];

% ===========================================================
% MAIN
% ===========================================================

% x values
x=0:0.1:10;

% Number of classes
Nc=length(Pc);

% Number of x samples
Nx=length(x);

% Number of actions
Na=size(L,1);

% Calculate class likelihoods
for j=1:Nc
    pxc(:,j)=normpdf(x,mu(j),sdev(j));
    y(:,j)=pxc(:,j)*Pc(j);
end

% Calculate probability density
px=sum(y,2);

% Calculate posteriors
for j=1:Nc
    pcx(:,j)=y(:,j)./px;
end

% ...
% ...
% ...


% ===========================================================
% VISUALIZATION
% ===========================================================

% Open new figure
figure('color','w');

% Subplot 1
subplot(3,2,1);
hold on;
grid on;
box on;
plot(x,pxc);
axis([min(x) max(x) 0 ceil(max(pxc(:)*1.1)*10)/10]);
title('1. p(x|c_j)','fontsize',15);

% Subplot 3
subplot(3,2,3);
hold on;
grid on;
box on;
plot(x,y);
axis([0 max(x) 0 ceil(max(y(:)*1.1)*10)/10]);
title('2. p(x|c_j)P(c_j)','fontsize',15);

% ...
% ...
% ...

drawnow;
set(gcf,'units','normalized','position',[0.1 0.1 0.8 0.8]);

% ===========================================================
% FURTHER QUESTIONS
% ===========================================================

% Question 1
disp('----- Question 1 -----');
idx=find(pxc(:,1)>pxc(:,2));
x1=x(idx(1));
x2=x(idx(end));
fprintf('From %g to %g\n',x1,x2);

% Question 2
% ...
% ...
% ...

