mat = load('./positions.xyz');
mat = sortrows(mat,-1);
n_lines = size(mat,1);

count = 0;
for ix = 1:n_lines
	for jx = ix+1:n_lines
		if mat(ix,1)-mat(jx,1) > 0.05
			break;
		end
			if norm(mat(ix,:)-mat(jx,:))^2 < 0.05^2
			count = count+1;
		end
	end
end

fprintf("close points: %d\n", count);
