%-----------------------------
%       Ασαφή Σύνολα
%-----------------------------

%-------------------------------------------------
% Εντολές που μπαίνουν στην αρχή κάθε προγράμματος
close all;
clear all;
clc;
format long;

%-------------------------------------------------
% Πεδίο ορισμού
x=0:0.01:100;

%-------------------------------------------------
% Κάλυψη του χώρου εισόδου με
% 3 Γκαουσιανές συναρτήσεις συμμετοχής
mf(1,:)=exp(-0.5*x.^2/(15^2));
mf(2,:)=exp(-0.5*((x-50).^2)/(20^2));
mf(3,:)=exp(-0.5*((x-100).^2)/(18^2));
plot(x,mf(1,:),'b',x,mf(2,:),'r',x,mf(3,:),'g');
title('blue line: Low, red line: Medium, green line: High');

%-------------------------------------------------
% Τομή και ένωση ασαφών συνόλων
figure(2);
In_A_B=min(mf(1,:),mf(2,:));
plot(x,In_A_B,'b');
hold on
In_A_B_alg=mf(1,:).*mf(2,:);
plot(x,In_A_B_alg,'r');
title('Intersection of A and B (blue line: min   red line: algebraic product');
axis([min(x) max(x) 0 max(In_A_B)]); % Καθορισμός ορίων αξόνων. Η τεταγμένη να ανέρχεται στη μέγιστη τιμή της τομής.

figure(3);
Un_A_B=max(mf(1,:),mf(2,:));
plot(x,Un_A_B);
title('Union of A and B');
axis([min(x) max(x) 0 max(Un_A_B)]); % Καθορισμός ορίων αξόνων. Η τεταγμένη να ανέρχεται στη μέγιστη τιμή της ένωσης.

%-------------------------------------------------
% Συμπλήρωμα ασαφούς συνόλου
figure(4);
mf_A_bar=1-mf(1,:);
plot(x,mf_A_bar);
title('Complement of Low');
axis([min(x) max(x) 0 max(mf_A_bar)]);

%-------------------------------------------------
% Mέγεθος ασαφούς συνόλου
for (i=1:3)
  cardinal=sum(mf(i,:));
  % Η sprintf χρησιμοποιείται για να γραφεί ένα string στην οθόνη
  st=sprintf('The cardinality of the %d-th fuzzy set is %g\n',i,cardinal);
  disp(st);
end
