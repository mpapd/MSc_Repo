%-------------------------------------------------------------------------- 
%-------------------------------------------------------------------------- 
% Moντελοποίηση της συμπεριφοράς του μοντέλου του φούρνου γκαζιού Box-Jenkins.
% 2 είσοδοι: y(k), y(k-1)
%--------------------------------------------------------------------------
close all;      clear all;      clc;        format long;
%__________________________________________________________________________
%__________________________________________________________________________
% ΠΑΡΑΜΕΤΡΟΙ ΜΟΝΤΕΛΟΥ - ΕΚΠΑΙΔΕΥΣΗΣ
fuzzySets = 10;                      % ασαφή σύνολα ανά είσοδο
epoch_number = 50;                 % αριθμός επαναλήψεων εκπαίδευσης
initial_learning_rate = 0.1;        % αρχικός ρυθμός εκμάθησης
mfType = 'gauss2mf';                % είδος συνάρτησης συμμετοχής ('trimf', 'trapmf', 'gbellmf', 'gaussmf', 'gauss2mf', 'pimf' 'dsigmf', 'psigmf')
outType = 'linear';                 % είδος εξόδου του κανόνα: σταθερή ('constant;) ή γραμμική ('linear')
%__________________________________________________________________________
%__________________________________________________________________________
% Απεικόνιση της χρονοσειράς
samples = 290;                      % αριθμός δεδομένων εκπαίδευσης 
load BJ_data.dat
time = BJ_data(:,1);
x = BJ_data(:, 4);
figure(1)
plot(time,x)
title('Box-Jenkins time-series')
xlabel('Time')
%-------------------------------------------------------------------------- 
% Παραγωγή των δεδομένων
for t = 1:samples 
    Data(t,:) = [BJ_data(t,2), BJ_data(t,3), BJ_data(t,4)]; 
end
trnData = Data(1:samples,:);
save('trnData.dat','trnData','-ASCII');

fismat = genfis1(trnData,[fuzzySets fuzzySets],char(mfType,mfType),char(outType));
%-------------------------------------------------------------------------- 
% Οι αρχικές συναρτήσεις συμμετοχής καλύπτουν ομοιόμορφα τον χώρο εισόδου
figure(2)
for (i = 1:2)
    subplot(2,1,i)
    plotmf(fismat,'input',i)
end
%-------------------------------------------------------------------------- 
% Εκπαίδευση
[fismat2,training_error,learning_rate] = anfis(trnData,fismat,[epoch_number,0,initial_learning_rate,0.9,1.1],[0 0 0 0]);
training_error
%-------------------------------------------------------------------------- 
%Απεικόνιση των τελικών συναρτήσεων συμμετοχής
figure(3)
for (i = 1:2)
    subplot(2,1,i)
    plotmf(fismat2,'input',i)
end
%Απεικόνιση της εξέλιξης του σφάλματος εκμάθησης
figure(4)
plot([training_error])
hold on
legend('training error')
xlabel('Epochs')
ylabel('RMSE (Root Mean Squared Error)')
title('Error Curves')
%Απεικόνιση της εξέλιξης του ρυθμού εκμάθησης
figure(5)
plot(learning_rate)
xlabel('Epochs')
ylabel('Learning rate')
title('Evolution of the learning rate')
%-------------------------------------------------------------------------- 
%Σύγκριση της εξόδου του συστήματος με την πραγματική
anfis_output = evalfis(trnData(:,1:2), fismat2);
index = 1:samples;

figure(6)
plot(time(index),[x(index) anfis_output])
plot(time(index),x(index),'b',time(index),anfis_output,'r')
xlabel('Time (sec)')
title('Box-Jenkins Time Series and ANFIS Prediction')

%Σφάλμα για κάθε δείγμα του συνόλου εκμάθησης
figure(7)
plot(time(index),x(index) - anfis_output)
xlabel('Time (sec)')
title('Prediction Error');