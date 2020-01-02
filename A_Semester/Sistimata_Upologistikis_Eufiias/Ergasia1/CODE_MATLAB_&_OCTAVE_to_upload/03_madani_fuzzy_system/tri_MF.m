%------------------------------------------------------------------
%       function y=tri_MF(x,a,b,c)
%       This function provides the triangular membership function
%       Author: Dr.Paris Mastorocostas
%------------------------------------------------------------------

function y=tri_MF(x,a,b,c)
if a > b,
    error('Illegal parameter condition: a > b');
elseif b > c,
    error('Illegal parameter condition: b > c');
end


y=max( min(((x-a)/(b-a)),((c-x)/(c-b))),0 );
%-------------------------------------------
% Another implementation
%y = zeros(size(x)); %initialize y 
%% Left slope
%if (a ~= b)
%    index = find(a < x & x < b);
%    y(index) = (x(index)-a)/(b-a);
%end
%% right slope
%if (b ~= c)
%    index = find(b < x & x < c);
%    y(index) = (c-x(index))/(c-b);
%end
%% Center (y = 1)
%index = find(x == b);
%y(index) = ones(size(index));