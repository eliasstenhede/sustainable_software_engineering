import numpy as np

if __name__=="__main__":
    mat = np.loadtxt("./data/positions.xyz")
    mat = mat[mat[:, 0].argsort()[::-1]]
    n_lines = mat.size//3

    count = 0
    for ix in range(n_lines):
        for jx in range(ix+1, n_lines):
            if mat[ix,0]-mat[jx,0] > 0.05:
                break
            if np.linalg.norm(mat[ix]-mat[jx]) < 0.05:
                count+=1
    print("close points:", count)
