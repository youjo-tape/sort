#include <stdio.h>

// フェルマー素数
#define N ((1<<16)+1)

int A[N];

void swap(int *i, int *j){
    int temp = *i;
    *i = *j;
    *j = temp;
}

void quick_sort(int A[], int n){
	if(n <= 1) return;
	int i, j, pivot = A[0];
    
    for(i = j = 1; i < n; i ++){
        if(A[i] <= pivot) swap(&A[i], &A[j ++]);
    }
    swap(&A[j-1], &A[0]);
    
    quick_sort(A, j-1);
    quick_sort(A+j, n-j);
}

/*
A[0], A[1], ..., A[n-1] の中でk+1番目に小さい値を返す関数
ただし、Aの中身は書き換えてしまう。
*/
int quick_select(int A[], int n, int k){
    
	// 実際に計算する
	if(n <= 5){
		quick_sort(A, n);
		return A[k];
	}
	
	// A を 5 個区切りにしたものの中央値を並べた配列 M をつくる
    int i, j, M[N];
	for(i = 0; i < n/5; i ++){
		M[i] = quick_select(A+5*i, 5, 2);
	}
	if(n % 5) M[i] = quick_select(A+5*i, n % 5, (n % 5)/2);
	
	// M の中央値を求めてピボットにする
	int pivot = quick_select(M, (n+4)/5, (n+4)/5/2);
	
	// ピボット(と値が等しい要素)を先頭にもってくる
	for(i = 0; i < n; i ++){
		if(A[i] == pivot){
			swap(&A[0], &A[i]);
			break;
		}
	}
	
	// あとは前と同じ
    for(i = j = 1; i < n; i++){
        if(A[i] <= pivot) swap(&A[i], &A[j ++]);
    }
    
    if(j == k+1) return pivot;
    else if(j < k+1) return quick_select(A+j, n-j, k-j);
    else return quick_select(A+1, j-1, k);
}

int main(){
  int i;
  A[0] = 0;
  A[1] = 3; //原始元
  for(i=2;i<N;i++){
    A[i] = (long long int) A[i-1] * A[1] % N;
  }
  for(i=0;i<N;i++){
	if(quick_select(A, N, i) != i) printf("ERROR %d %d\n", i, quick_select(A, N, i));
	printf("%d th element is %d\n", i, quick_select(A, N, i));
  }
}
