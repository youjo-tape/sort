#include <stdio.h>

//フェルマー素数
#define N ((1<<16)+1)

int A[N];

void swap(int *i, int *j){
	int temp = *i;
	*i = *j;
	*j = temp;
}

/*
A[0], A[1], ..., A[n-1] をソートして昇順に書き換える関数
*/
void quick_sort(int A[], int n){
	if(n <= 1) return;
	int i, j, f, pivot = A[0];
    
    for(i = j = f = 1; i < n; i ++){
        if(A[i] <= pivot){
            
			// 等しい要素は左右に等分配する
			if(A[i] == pivot && !f){
				f = 1;
				continue;
			}
			
			swap(&A[i], &A[j]);
          	j ++;
			f = 0;
        }
    }
    swap(&A[j-1], &A[0]);
    
    quick_sort(A, j-1);
    quick_sort(A+j, n-j);
}

int main(){
  int i;
  A[0] = 0;
  A[1] = 0; //原始元
  for(i=2;i<N;i++){
    A[i] = (long long int) A[i-1] * A[1] % N;
  }

// すべての要素が同じ場合でも計算が早く終わるか確認する

  quick_sort(A, N);
  for(i=0;i<N;i++){
  //  if(A[i] != i) printf("ERROR %dth element is %d\n", i, A[i]);
  }
}
