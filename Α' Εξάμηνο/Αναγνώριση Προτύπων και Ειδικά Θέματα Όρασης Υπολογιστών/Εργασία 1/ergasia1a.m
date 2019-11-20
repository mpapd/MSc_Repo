clc;
clear;
close all;

% ===========================================================
% INIT
% ===========================================================



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
% figure('color','w');

% Subplot 1
subplot(3,2,1);
hold on;
grid on;
box on;
plot(x,pxc);
axis([min(x) max(x) 0 ceil(max(pxc(:)*1.1)*10)/10]);
title('1. p(x|c_j)','fontsize',15);

% Subplot 2
subplot(3,2,3);
hold on;
grid on;
box on;
plot(x,y);
axis([0 max(x) 0 ceil(max(y(:)*1.1)*10)/10]);
title('2. p(x|c_j)P(c_j)','fontsize',15);

% Subplot 3
 subplot(3,2,5);
 hold on;
 grid on;
 box on;
 plot(x, px);
 
 title('3. p(x)','fontsize',15);
 
% %Subplot 4
subplot(3,2,2);
hold on;
grid on;
box on;
plot(x, pcx);
axis([min(x) max(x) 0 ceil(max(pcx(:)*1.1)*10)/10]);
title('4. p(c_i|x)','fontsize',15);

% %Subplot 5
subplot(3,2,4);
hold on;
grid on;
box on;
% %Bayesian risk
plot( x, (L(1,2) * pcx(:,2))); 
plot( x, (L(2,1) * pcx(:,1)));

title('5. R(a_j|x)','fontsize',15);

drawnow;
set(gcf,'units','normalized','position',[0.1 0.1 0.8 0.8]);

% ===========================================================
% FURTHER QUESTIONS
% ===========================================================

% Question 1
fprintf('----- Question 1 -----\n');
idx=find(pxc(:,1)>pxc(:,2));
x1=x(idx(1));
x2=x(idx(end));
fprintf('\n\tFrom %g to %g\n',x1,x2);

% Question 2
%Solution 1
fprintf('\n----- Question 2 -----\n');
%We have -3*x^2 + 56*x - 250.0224
equation = [-3 56 -250.0224];
solution = roots(equation);
Ndecimals = 2;
f = 10.^Ndecimals ;
range = [ceil(f*solution(2))/f 10];
fprintf('\n\tSolution 1: From %g to %g \n', range(1), range(2));

%Solution 2
% We will build the equation on final Bayes step
% p(x|?1) / p(x|?2) > [?(?1|?2) - ?(?2|?2)]?(?2) / ?(?2|?1) - ?(?1|?1)]?(?1)
% p(x|?1) = p(:,1)
% p(x|?2) = p(:,2)
% ?(?1|?2) = 3, ?(?2|?2) = 0
% ?(?2|?1) = 1,  ?(?1|?1) = 0
% ?(?2) = Pc(1,2)
% ?(?1) = Pc(1,1)


for element=1 : length(x)
    %calculating factor for each element
    pxc_element = pxc(element,1) / pxc(element,2);
    
    %Checking if the Bayes equation is confirmed and we are saving the
    %element
    
    if (pxc_element > (Pc(1,2) * L(1,2)) / (Pc(1,1) * L(2,1)))
        fprintf('\n\tSolution 2: position = %g with grade = %g\n', element, x(element))
        break;
    end
    
    
end


% Question 3
fprintf('\n----- Question 3 -----\n');
% ---- Algorithm for the equation ---- %
%Testing new ?
lgm = 1;
lmg = 2.5;
%Building right part of the equation
num_pc_test = 1*lgm*Pc(:,2);
den_pc_test = 2*lmg*Pc(:,1);
final_num_pc_test = num_pc_test / den_pc_test;
Ndecimals = 4;
f = 10.^Ndecimals ;
pc_test = ceil(f*log(final_num_pc_test))/f;
%Building left part of the equation
clean_num = -240-8*pc_test;
equation = [-3 56 clean_num];
solution = roots(equation);
%Since we rounded by the second decimal on A2 question, we will find ? values to be as
%close as possible to 6.4 based on second decimal
Ndecimals = 1;
f = 10.^Ndecimals ;
range = [ceil(f*solution(2))/f 10];
fprintf('\n\tFrom %g to %g \n', range(1), range(2));


% Question 4
fprintf('\n----- Question 4 -----\n');
%Based on Bayesian risk we are building the two risks
%R(good | x) = ?mg * p(moderate|x)
risk_good = L(1,2) * pcx(:,2); 
%R(moderate | x) = ?gm * p(good | x)
risk_moderate = L(2,1) * pcx(:,1); 
%Finding the which grade has the minimum risk to be considered good
for element=2 : length(x) - 1
    %Checking if the current element is less than the previous and the next risk
    if(risk_good(element) < risk_good(element-1) && risk_good(element) < risk_good(element+1))
        fprintf('\n\tgrade = %g with risk = %g \n ', x(element), risk_good(element))
    end
end

% Question 5
fprintf('\n----- Question 5 -----\n');
new_Pc=[0.5 0.5];
%Building right part of the equation
num_pc_test = 1*lgm*new_Pc(:,2);
den_pc_test = 2*lmg*new_Pc(:,1);
final_num_pc_test = num_pc_test / den_pc_test;
Ndecimals = 4;
f = 10.^Ndecimals ;
pc_test = ceil(f*log(final_num_pc_test))/f;
%Building left part of the equation
clean_num = -240-8*pc_test;
equation = [-3 56 clean_num];
solution = roots(equation);
%Since we rounded by the second decimal on A2 question, we will find ? values to be as
%close as possible to 6.4 based on second decimal
Ndecimals = 1;
f = 10.^Ndecimals ;
range = [ceil(f*solution(2))/f 10];
fprintf('\n\tFrom %g to %g \n', range(1), range(2));






