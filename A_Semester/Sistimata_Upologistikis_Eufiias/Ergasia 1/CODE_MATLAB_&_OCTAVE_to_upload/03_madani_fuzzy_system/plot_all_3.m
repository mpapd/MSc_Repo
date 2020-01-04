%-----------------------------------------------------------------
%       function plot_all_3(x,A,Abar,y,B,Bbar,z,C,Cbar);
%       This function plots A, A', B, B' and C, C' of a two-input
%       fuzzy rule
%       Author: Dr.Paris Mastorocostas
%-----------------------------------------------------------------

function plot_all_3(x,A,Abar,y,B,Bbar,z,C,Cbar);
subplot(3,1,1);
plot(x,A,'k');   hold on;
plot(x,Abar,'r')
title('black line: A,  red line: A''')
subplot(3,1,2);
plot(y,B,'k');   hold on;
plot(y,Bbar,'r')
title('black line: B,  red line: B''')
subplot(3,1,3);
plot(z,C,'k');   hold on;
plot(z,Cbar,'r')
title('black line: C,  red line: C''')
