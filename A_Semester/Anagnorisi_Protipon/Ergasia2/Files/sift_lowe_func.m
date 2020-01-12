function [descriptors, locs] = sift_lowe_func(I)

% TK_SIFT_LOWE Find SIFT keypoints using Lowe's implementation.

[rows, cols, bands] = size(I); 
if bands>1
   I = rgb2gray(I);
end


% Convert into PGM imagefile, readable by "keypoints" executable
f = fopen('tmp.pgm', 'w');
if f == -1
    error('Could not create file tmp.pgm.');
end
fprintf(f, 'P5\n%d\n%d\n255\n', cols, rows);
fwrite(f, I', 'uint8');
fclose(f);

% Call keypoints executable
if exist('OCTAVE_VERSION', 'builtin')>0
    % If in OCTAVE
    command = 'siftwin32.exe <tmp.pgm> tmp.key';
else
    % If in MATLAB
    command = 'siftwin32.exe <tmp.pgm> tmp.key';
end
system(command);

% Open tmp.key and check its header
g = fopen('tmp.key', 'r');
if g == -1
    error('Could not open file tmp.key.');
end
[header, count] = fscanf(g, '%d %d', [1 2]);
if count ~= 2
    error('Invalid keypoint file beginning.');
end
num = header(1);
len = header(2);
if len ~= 128
    error('Keypoint descriptor length invalid (should be 128).');
end

% Creates the two output matrices (use known size for efficiency)
locs = double(zeros(num, 4));
descriptors = double(zeros(num, 128));

% Parse tmp.key
for i = 1:num
    [vector, count] = fscanf(g, '%f %f %f %f', [1 4]); %row col scale ori
    if count ~= 4
        error('Invalid keypoint file format');
    end
    locs(i, :) = vector(1, :);
    
    [descrip, count] = fscanf(g, '%d', [1 len]);
    if (count ~= 128)
        error('Invalid keypoint file value.');
    end
    % Normalize each input vector to unit length
    descrip = descrip / sqrt(sum(descrip.^2));
    descriptors(i, :) = descrip(1, :);
end
fclose(g);
 
if exist('tmp.key','file')
    delete('tmp.key');
end
if exist('tmp.pgm','file')
    delete('tmp.pgm');
end
