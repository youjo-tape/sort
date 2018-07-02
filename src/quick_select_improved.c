#include <stdio.h>

// フェルマー素数
#define N ((1<<16)+1)

int A[N];

void swap(int *i, int *j){
    int temp = *i;
    *i = *j;
    *j = temp;
}

/*
A[0], A[1], ..., A[n-1] の中でk+1番目に小さい値を返す関数
ただし、Aの中身は書き換えてしまう。
*/
int quick_select(int A[], int n, int k){
	swap(&A[0], &A[n/2]);
    int i, j, f, pivot = A[0];

    for(i = j = f = 1; i < n; i++){
        if(A[i] <= pivot){
            
			// 等しい要素は左右に等分配する
			if(A[i] == pivot && !f){
				f = 1;
				continue;
			}
			
			swap(&A[i], &A[j ++]);
			f = 0;
        }
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

// すべての要素が同じ場合でも計算が早く終わるか確認する

  for(i=0;i<N;i++){
    if(quick_select(A, N, i) != i) printf("ERROR %d %d\n", i, quick_select(A, N, i));
//	printf("%d th element is %d\n", i, quick_select(A, N, i));
  }
}
