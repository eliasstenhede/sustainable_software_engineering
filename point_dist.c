#include <stdlib.h>
#include <stdio.h>

// counts the number of lines in the input file
int countRows(FILE *fp) {
    int count = 0;
    char c;
    for (c = getc(fp); c != EOF; c = getc(fp)) {
        if (c == '\n')
           count++;
    }
    rewind(fp);
    return count;
}

// helper function for mergeSort
static inline void merge_by_x(float arr[], int l, int m, int r){
    int ix, jx, kx;
    int n1 = m - l + 1;
    int n2 = r - m;
    float left[n1*3], right[n2*3];
    for (ix = 0; ix < 3*n1; ix+=3) {
	left[ix+0] = arr[3*l+ix+0];
	left[ix+1] = arr[3*l+ix+1];
	left[ix+2] = arr[3*l+ix+2];
    }
    for (jx = 0; jx < 3*n2; jx+=3) {
	right[jx+0] = arr[3*(m+1)+jx+0];
	right[jx+1] = arr[3*(m+1)+jx+1];
	right[jx+2] = arr[3*(m+1)+jx+2];
    }
    ix = 0;
    jx = 0;
    kx = l*3;
    while (ix < n1*3 && jx < n2*3) {
	if (left[ix] <= right[jx]) {
	    arr[kx+0] = left[ix+0];
	    arr[kx+1] = left[ix+1];
	    arr[kx+2] = left[ix+2];
	    ix+=3;
	}
	else {
	    arr[kx+0] = right[jx+0];
	    arr[kx+1] = right[jx+1];
	    arr[kx+2] = right[jx+2];
	    jx+=3;
	}
	kx+=3;
    }
    while (ix < 3*n1) {
	arr[kx+0] = left[ix+0];
	arr[kx+1] = left[ix+1];
	arr[kx+2] = left[ix+2];
	ix+=3;
	kx+=3;
    }
    while (jx < 3*n2) {
	arr[kx+0] = right[jx+0];
	arr[kx+1] = right[jx+1];
	arr[kx+2] = right[jx+2];
	jx+=3;
	kx+=3;
    }
}

// Sorts array of 3D-coordinates in order [x1 y1 z1 x2 y2 z2 x3 ...] by x-values, ascending
static inline void mergeSort(float arr[], int l, int r) {
    if (l < r) {
	int m = l + (r - l) / 2;
	mergeSort(arr, l, m);
	mergeSort(arr, m + 1, r);
	merge_by_x(arr, l, m, r);
    }
}

// Reads input file given for this problem,
// assuming all coordinates are in the interval (-9.99999, 9.999999) and specified with constant number of digits.
void parseFile(FILE* fp, float* points) {
    size_t ix = 0;
    char s[31];
    char *e;
    int startp;
    float coord;
    for (fgets(s, 31, fp); (e = fgets(s, 31, fp)) != NULL; ix+=3) {
        startp=0;
	for (int jx=0; jx < 3; jx++) {
	    if (e[startp] == '-') {
	        coord = -1.f      *(e[startp+1]-'0')
		        -0.1f     *(e[startp+3]-'0')
			-0.01f    *(e[startp+4]-'0')
		        -0.001f   *(e[startp+5]-'0')
			-0.0001f  *(e[startp+6]-'0')
			-0.00001f *(e[startp+7]-'0')
			-0.000001f*(e[startp+8]-'0');
	        startp+=10;
	    } else {
	        coord = +1.f      *(e[startp+0]-'0')
		        +0.1f     *(e[startp+2]-'0')
			+0.01f    *(e[startp+3]-'0')
		        +0.001f   *(e[startp+4]-'0')
			+0.0001f  *(e[startp+5]-'0')
			+0.00001f *(e[startp+6]-'0')
			+0.000001f*(e[startp+7]-'0');
	        startp+=9;
            }
            points[ix+jx] = (float) coord;
        }
    }
    fclose(fp);
}



int main(int argc, char *argv[]) {
    //Read file and sort by x-coordinate
    FILE *fp  = fopen("./positions.xyz", "r");
    const int rows_in_file = countRows(fp);
    float* points = (float*) malloc(rows_in_file*3*sizeof(float));
    parseFile(fp, points);
    mergeSort(points, 0, rows_in_file-1);
    
    //Set number of threads
    
    //Count the points with distance < .05 
    float dx1,dy1,dz1,dx2,dy2,dz2,dx3,dy3,dz3,dx4,dy4,dz4;
    size_t count_close = 0;
    size_t jx;
    
    /* #pragma omp parallel for schedule(dynamic) reduction(+:count_close) */
    for (size_t ix=0; ix<rows_in_file*3; ix+=3) {
	jx = ix+3;
	while(points[jx] - points[ix] < 0.05f && jx < rows_in_file*3)
	{
	    //Partially unrolling loop to get multiple of 4 of the operations, which allowed for vectorization on my CPU.
	    dx1=points[ix+0]-points[jx+0 ];
	    dy1=points[ix+1]-points[jx+1 ];
	    dz1=points[ix+2]-points[jx+2 ];
	    
	    dx2=points[ix+0]-points[jx+3 ];
	    dy2=points[ix+1]-points[jx+4 ];
	    dz2=points[ix+2]-points[jx+5 ];
	    
	    dx3=points[ix+0]-points[jx+6 ];
	    dy3=points[ix+1]-points[jx+7 ];
	    dz3=points[ix+2]-points[jx+8 ];
	    
	    dx4=points[ix+0]-points[jx+9 ];
	    dy4=points[ix+1]-points[jx+10];
	    dz4=points[ix+2]-points[jx+11];

	    dx1=dx1*dx1;
	    dy1=dy1*dy1;
	    dz1=dz1*dz1;
	    dx1 = dx1+dy1+dz1; 
	    if (dx1 < 0.0025f){
		count_close++;
	    }
	    dx2=dx2*dx2;
	    dy2=dy2*dy2;
	    dz2=dz2*dz2;
	    dx2 = dx2+dy2+dz2; 
	    if (dx2 < 0.0025f){
		count_close++;
	    }
	    dx3=dx3*dx3;
	    dy3=dy3*dy3;
	    dz3=dz3*dz3;
	    dx3 = dx3+dy3+dz3; 
	    if (dx3 < 0.0025f){
		count_close++;
	    }
	    dx4=dx4*dx4;
	    dy4=dy4*dy4;
	    dz4=dz4*dz4;
	    dx4 = dx4+dy4+dz4; 
	    if (dx4 < 0.0025f){
		count_close++;
	    }
	    jx+=12;
	}
    }
    printf("Close points: %d\n", count_close);
    free(points);
}

