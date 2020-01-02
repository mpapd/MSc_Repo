%-----------------------------------------------------------------------
% Αναγνώριση συστήματος με ασαφές σύστημα τύπου Mamdani 5 κανόνων.
% Εφαρμογή: συνάρτηση συνημιτόνου
%-----------------------------------------------------------------------
clc;
close all;
clear all;
%-----------------------------------------------------------------------
% Βασικές Παράμετροι (όχι όλες)
ruleNumber = 5;
inputSets = ruleNumber;
outputSets = 3;
overlappingCoefficient = 0.5;
%-----------------------------------------------------------------------
x=0:1:360;
y=linspace(-5,5,361);
z=5*cos(2*pi*x/360);
%-----------------------------------------------------------------------
% Ομοιόμορφη κατανομή του χώρου εισόδου
figure(2);
axis([min(x) max(x) 0 1.05]);   title('Partition of x');   hold on
[Alpha,Beta,Gamma]=tri_MF_partition(min(x),max(x),inputSets,overlappingCoefficient);
for (k=1:inputSets)
    mf_x(k,:)=tri_MF(x,Alpha(k),Beta(k),Gamma(k));
    plot(x,mf_x(k,:))
end
%-----------------------------------------------------------------------
% Ομοιόμορφη κατανομή του χώρου εξόδου
figure(3);
axis([min(y) max(y) 0 1.05]);   title('Partition of y');   hold on
[Alpha,Beta,Gamma]=tri_MF_partition(min(y),max(y),outputSets,0.5);
for (k=1:outputSets)
    mf_y(k,:)=tri_MF(y,Alpha(k),Beta(k),Gamma(k));
    plot(y,mf_y(k,:))
end
%-----------------------------------------------------------------------
% Βάση κανόνων, αντιστοίχηση των ασαφών συνόλων στα σύνολα των κανόνων
In(1,:)=mf_x(1,:);    In(2,:)=mf_x(2,:);    In(3,:)=mf_x(3,:);    In(4,:)=mf_x(5,:);    In(5,:)=mf_x(4,:);    
Out(1,:)=mf_y(3,:);   Out(2,:)=mf_y(2,:);   Out(3,:)=mf_y(1,:);   Out(4,:)=mf_y(3,:);   Out(5,:)=mf_y(2,:); 
%-----------------------------------------------------------------------
for j=1:length(x)
    for i=1:ruleNumber
        Bbar(i,:)=min(In(i,j),Out(i,:));
    end    
    total=Bbar(1,:);
    for i=2:ruleNumber
        total=max(total,Bbar(i,:));
    end
    output(j)=sum(y.*total)/sum(total);
end

figure(4);
plot(x,z,'b',x,output,'r--');
title('Blue solid line: Cos, Red dotted line: fuzzy system''s output');
clc

