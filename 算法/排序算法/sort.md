| 排序方法 |            |   时间复杂度   |           |  空间复杂度   | 稳定性  |
| :--: | :--------: | :-------: | :-------: | :------: | :--: |
|      |    平均情况    |   最好情况    |   最坏情况    |   辅助存储   |      |
| 插入排序 |   O(n^2)   |   O(n)    |  O(n^2)   |   O(1)   |  稳定  |
| 希尔排序 | O(n^(1.3)) |   O(n)    |  O(n^2)   |   O(1)   | 不稳定  |
| 选择排序 |   O(n^2)   |  O(n^2)   |  O(n^2)   |   O(1)   | 不稳定  |
| 堆排序  |  O(nlogn)  | O(nlogn)  | O(nlogn)  |   O(1)   | 不稳定  |
| 冒泡排序 |   O(n^2)   |   O(n)    |  O(n^2)   |   O(1)   |  稳定  |
| 快速排序 |  O(nlogn)  | O(nlogn)  |  O(n^2)   | O(nlogn) | 不稳定  |
| 归并排序 |  O(nlogn)  | O(nlogn)  | O(nlogn)  |   O(n)   |  稳定  |
| 基数排序 | O(d(n+r))  | O(d(n+r)) | O(d(n+r)) |  O(n+r)  |  稳定  |

注：r代表基数，d代表长度，n代表数的个数

### 冒泡排序

从前往后，依次比较前面的数和后面的数依次比较，如果前面的数大于后面的数，就交换它们的位置。这样循环一遍后，最大的数就在数组最后了。将循环的范围缩小，直至为1，数组就有序了。

* 时间复杂度O(n^2)

  ```c++
  void bubule_sort(int * a; int n){
  	for (int i = n -1; i > 0 ; i--)
       	for (int j = 0 ; j < i ; j++)
            if (a[j] > a[j+1])
              swap(a,j,j+1);
  }
  ```

  ​

### 选择排序

每次都选择未排序数中的最小的数，与当前未排序数中的第一个数交换位置

* 时间复杂度O(n^2)

  ```c++
  void selectionSort(int* A, int n) {
    // write code here
    for (int i = 0; i< n ; i++){
      int min = i;//记录当前最小值的位置
      //从剩余未排序的数里面找到最小值的位置
      for (int j = i+1 ; j < n ; j++){
        if (A[j] < A[min])
          min = j;
      }
      //将最小值与当前第一个未排序的值交换位置
      if (min == i)
        continue;
      int temp = A[i];
      A[i] = A[min];
      A[min] = temp;
    }
  }
  ```

  ​

### 插入排序

将一个数插入到前面有序的数中合适的位置

* 时间复杂度O(n^2)

  ```c++
  void insertionSort(int* A, int n) {
    // write code here
    //注意数组范围，别越界，因为j=i+1;因此i<n-1;
    for (int i = 0 ; i< n-1 ;i++){
      int j = i+1;
      while( j > 0 && A[j] < A[j-1]){
        int temp = A[j];
        A[j] = A[j-1];
        A[j-1] = temp;
        j--;
      }
    }
  }
  ```

  ​

### 归并排序

采用分治的思想，需要一个辅助数组。

* 时间复杂度为O(nlogn)

* 是稳定的

  ```c++
  void merge(int *a, int lo , int mid , int hi){
    int len = hi - lo + 1;
    int *aux = new int[len];
    int index = 0;
    int i = lo;
    int j = mid + 1;
    while(i <=mid && j <= hi)
      aux[index++] = a[i] < a[j] ? a[i++] : a[j++];
    while(i<=mid)
      aux[index++] = a[i++];
    while(j<=hi)
      aux[index++] = a[j++];
    for (int k =0; k < len ; k++)
      a[lo+k] = aux[k];
    delete [] aux;
  }
  void mergeSortRecur(int *a, int lo , int hi){
    if (lo >= hi)
      return;
    int mid = (lo + hi)/2;
    mergeRecur(a,lo,mid);
    mergeRecur(a,mid+1,hi);
    merge(a,lo,mid,hi);
  }
  ```

  ​

### 快速排序

* 是不稳定的排序

* 最好情况O(nlogn)

* 最坏情况O(n^2)

* 平均情况O(nlogn)

  版本一

  ```c++

      void quickSort(int *A,int lo , int hi){
          if ( lo >= hi)
              return;
          int i = lo , j = hi + 1;
          int pivot = A[lo]; //选择切分元素，切分值可以任意选择
          while(true){//退出条件为，i>=hi或j<=lo或i>=j，都表明已经遍历了数组的所有元素
              while(A[++i] <= pivot) //从左侧搜索大于切分值的位置
                  if ( i >= hi) break;
              while(A[--j] >= pivot)//从右侧所搜小于切分值的位置
                  if ( j <= lo) break;
              if ( i >= j) break;
              swap(A, i, j); //将这两个位置的数交换，让小于切分值的数在左边，大于切分值的数在右边。
            
          }
          swap(A, lo , j);//将切分值交换到正确的位置，切分值左侧全部小于它，右侧全部大于它
          quickSort(A,lo,j-1);//切分左侧的部分
          quickSort(A,j+1,hi);//切分右侧的部分
      }
  ```

  版本二

  ```c++
      void quick_sort(int *A,int lo , int hi){
          if ( lo >= hi)
              return;
          int i = lo , j = hi;
          int pivot = A[lo];
          while( i < j){
              while( i < j && A[j] > pivot) j--;//从右边找第一个小于pivot的数
              if (i<j)
              	A[i++] = A[j];//填i的坑，默认i为0,
              while( i < j && A[i] < pivot) i++;//从左边找第一个大于pivot的数
              if (i <j)
              	A[j--] = A[i];//填上次j的坑
              
          }
          A[i] = pivot;
          quick_sort(A,lo,i-1);
          quick_sort(A,i+1,hi);
      }
  ```

  ​

### 堆排序

堆是一个完全二叉树，并且父节点大于等于子节点的大小，称为大根堆；

二叉堆的性质有，以数组存储二叉堆，假如父节点的索引为k,那么它的左子节点的索引为2k+1,右子节点的索引为2k+2

* 是不稳定的

* 时间复杂度O(nlogn)

  ```c++
  //下沉操作，将父节点下沉到应有的位置 
  //len表示堆的大小
  void sink(int *A, int p , int len){
      	int c = 2 * p +1;//c初始为父节点的左子节点
          while ( c < len){//子节点的索引在二叉堆的范围内就一直循环
            	//找到子节点中大的那个
              if ( c + 1 < len && A[c] < A[c+1])
                  c++;
            	//如果父节点大于等于子节点的大小就结束循环
              if ( A[p] >= A[c])
                  break;
            	//执行到这里说明，父节点的大小小于子节点的大小，将父子节点交换
              swap(A, p , c);
              p = c;//更新父节点
              c = 2 * p + 1;//更新子节点
          }
      }
      
      int* heapSort(int* A, int n) {
          // write code here
        	//先从堆的倒数第二层的最后开始进行下沉操作，一直到堆顶
        	//循环结束后，堆就是堆有序的了
          for ( int i = n/2 - 1; i >= 0 ; i-- ){
              sink(A, i , n);
          }
        	//将最大值（堆顶）交换到数组最后
        	//进行一次下沉操作，恢复堆的有序状态
        	//一直到堆的大小为1，此时，数组就是有序的了
          for (int k = n-1 ; k > 0 ; k--){
              swap(A,0,k);
            	sink(A,0,k);
          }
          return A;
      }
  ```

  ​

### 希尔排序

是步长可变的插入排序。步长从一个比较大的数一直变到1.

* 希尔排序是不稳定的

* 时间复杂度为

  ```c++
  int* shellSort(int* A, int n) {
    // write code here
    int step = n / 2; //步长
    while(step > 0){
      //按照插入排序的思想进行排序
      for (int i = step ; i < n ; i++){
        int index = i;
        while( index >= step && A[index] < A[index - step]){
          //执行到这里说明A[index] < A[index - step]
          //后面的小于前面的，将它们交换
          swap(A , index , index - step);
          index -= step;
        }
      }
      step /= 2;
    }
    return A;
  }
  ```

  ​

### 计数排序

是基于桶排序的思想，建立一个与所排数组中数值范围大小的桶，将对应的值放入对应的桶中来排序。

* 时间复杂度为O(n)

* 空间复杂度为O(m)，与桶的数量有关

  ```c++
      int* countingSort(int* A, int n) {
          // write code here
          int min=A[0];
          int max=A[0];
        	//求出数组中数值的最大值和最小值
          for (int i = 0; i < n ; i++){
              if (A[i] > max)
                  max = A[i];
             else if (A[i] < min)
                  min = A[i];
          }
        	//len是桶的数量
          int len = max - min + 1;
          int *bucket = new int[len]();
        	//将数组中对应的值放入对应的桶中
          for (int i = 0 ; i< n ; i++){
              bucket[A[i]-min]++;
          }
          int index = 0;
        	//根据桶中的数据重构数组
          for (int i = 0 ; i< len ; i++){
              while (bucket[i]-- > 0)
                  A[index++] = i + min;
          }
          delete [] bucket;
          return A;
          
      }
  ```

  ​

### 基数排序

```c++
    int* radixSort(int* A, int n) {
        // write code here
        queue<int> q1[10];
        int base = 1;
        while (base <= 1000){
        	for (int i = 0 ; i< n ; i++){
            	q1[(A[i]/base)%10].push(A[i]);
        	}    
            int index = 0;
            for (int i =0 ; i< 10 ; i++){
                while (!q1[i].empty()){
                    A[index++] = q1[i].front();
                    q1[i].pop();
                }
            }
            base *= 10;
            
        }
        return A;
    }
```

