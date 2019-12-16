//
// Created by Dell on 2019/12/13.
//
#include <iostream>
#include <random>
#include <ctime>
const int MatchMax = 99999;

using namespace std;

class myClock {
public:
    void start() {
        cout << "开始计时" << endl;
        t1 = clock();
    }

    void end() {
        t2 = clock();
        cout << "经过时间 " << (double) (t2 - t1) / 1000 << "s" << endl;
        cout << endl;
    }

private:
    long t1;
    long t2;
};

//锦标赛排序用到
struct MatchNode{
    int data;
    int id;
    explicit MatchNode(int n = MatchMax, int id = -1):data(n),id(id){}
};


template<class T>
class LinearSort {
public:
    LinearSort();

    LinearSort(T a[], int n);

    ~LinearSort();

    void changeArray(T a[], int n);

    void printArray();

    void BubbleSort();

    void BubbleSortBothWay();

    void InsertSort();

    void BinaryInsertSort();

    void QuickSort();

    void ShellSort();

    void SelectSort();

    void MatchSort();//锦标赛排序


private:
    T *array;
    int currentSize;

    int QuickPass(int low, int high);

    void swap(int i, int j);

    void QuickSort(int low, int high);
};

template<class T>
LinearSort<T>::LinearSort() {
    array = nullptr;
    currentSize = 0;
}


template<class T>
LinearSort<T>::LinearSort(T *a, int n) {
    array = new T[n + 1]; //浪费一个空间有用
    for (int i = 0; i < n; i++)
        array[i] = a[i];
    currentSize = n;
}

template<class T>
LinearSort<T>::~LinearSort() {
    if (array != nullptr)
        delete array;
}


template<class T>
void LinearSort<T>::changeArray(T *a, int n) {
    if (array != nullptr)
        delete[] array;
    array = new T[n + 1];
    for (int i = 0; i < n; i++)
        array[i] = a[i];
    currentSize = n;
}

template<class T>
void LinearSort<T>::printArray() {
    for (int i = 0; i < currentSize; i++)
        cout << array[i] << " ";
    cout << endl;
}


//升序
template<class T>
void LinearSort<T>::BubbleSort() {
    if (!array)
        return;
    bool exchange;
    int i, j;
    int count = 0;//统计排序趟数
    for (i = 0; i < currentSize; i++) {
        exchange = false;
        for (j = 0; j < currentSize - 1; j++) {
            if (array[j] > array[j + 1]) {
                swap(j, j + 1);
                exchange = true;
            }
        }
        count++;
        if (!exchange)
            break;
    }
    cout << "经过 " << count << "次BubbleSort排序获得有序序列" << endl;
}

template<class T>
void LinearSort<T>::BubbleSortBothWay() {
    if (!array)
        return;
    bool exchange;
    int start[2] = {0, currentSize - 2};
    int end[2] = {currentSize - 1, -1};
    int move[2] = {1, -1};
    int count = 0; // 统计排序的趟数
    while (count < currentSize) {
        exchange = false;
        for (int i = start[count % 2]; i != end[count % 2]; i += move[count % 2]) {
            if (array[i] > array[i + 1]) {
                swap(i, i + 1);
                exchange = true;
            }
        }
        /*
         * cout << "count: " << count << "   ";
         * cout << "start: " << start[count % 2] << "  ";
         * cout << "end: " << end[count % 2] << endl;
         * cout << "array: ";
         * for (int i = 0; i < currentSize; i++)
         *      cout << array[i] << " ";
         *cout << endl << endl;
        */
        if (!exchange)
            break;
        count++;
    }
    cout << "经过 " << count << " 次双向BubbleSort排序获得有序序列" << endl;
}


template<class T>
void LinearSort<T>::InsertSort() {
    if (!array)
        return;
    int i, j;
    //多开了一个空间，放在了array[currentSize]
    for (int i = 1; i < currentSize; i++) {
        array[currentSize] = array[i];
        j = i - 1;
        while (array[currentSize] < array[j] && j >= 0) {
            //如果array[0]是多开的浪费空间的话可以把它考虑为哨兵,
            //这样就不用判断j >= 0
            array[j + 1] = array[j];
            j--;
        }
        array[j + 1] = array[currentSize];
    }
}

/*有哨兵的写法
 * template<class T>
 *void LinearSort222<T>::InsertSort() {
 * int i,j;
 * for(int i = 2; i < last; i++)
 * {
 *      data[0] = data[i];
 *      j = i - 1;
 *      while(data[0]<data[j])
 *          data[j + 1] = data[j--];
 *      data[j + 1] = 0
 * */


template<class T>
void LinearSort<T>::BinaryInsertSort() {
    if (!array)
        return;
    int mid;
    for (int i = 1; i < currentSize; i++) {
        int low = 0, high = i - 1;
        int temp = array[i];
        while (low <= high) {
            mid = (low + high) / 2;
            if (temp < array[mid])
                high = mid - 1;
            else
                low = mid + 1;
        }
        //由折半查找到的正确插入位置为high+1或者low
        for (int j = i - 1; j >= high + 1; j--)
            array[j + 1] = array[j];
        //在正确位置插入复制出来的待插入元素
        array[high + 1] = temp;
    }
}


template<class T>
void LinearSort<T>::QuickSort() {
    QuickSort(0, currentSize - 1);
}

template<class T>
void LinearSort<T>::QuickSort(int low, int high) {
    if (!array)
        return;
    int mid;
    if (low < high) {
        mid = QuickPass(low, high);
        QuickSort(low, mid - 1);
        QuickSort(mid + 1, high);
    }
}


template<class T>
void LinearSort<T>::swap(int i, int j) {
    T temp = array[i];
    array[i] = array[j];
    array[j] = temp;
}


template<class T>
void LinearSort<T>::ShellSort() {
    int i, j, gap;
    gap = currentSize/ 2;
    while (gap >= 1) {
        for (i = gap; i < currentSize; i++) {
            array[currentSize] = array[i]; //array[currentSize]为浪费的空间
            j = i - gap;
            while (array[currentSize] < array[j] && j >= 0) {
                array[j + gap] = array[j];
                j = j - gap;
            }
            array[j + gap] = array[currentSize];
        }
//        cout << "array: ";
//        printArray();
        gap = gap / 2;
    }
}

template<class T>
int LinearSort<T>::QuickPass(int low, int high) {
    int down = low;
    int up = high;
    array[currentSize] = array[down];
    //此时array[down]空出来了
    while (down < up) {
        while (down < up && array[up] > array[currentSize])
            up--;       //从右边找到第一个比基准值array[down]小的就停下来
        if (down < up)
            array[down++] = array[up];
        //此时array[up]空出来了
        while (down < up && array[down] <= array[currentSize])
            down++;
        if (down < up)
            array[up--] = array[down];
        //此时array[down]空出来了
    }
    //此时down与up相遇了
    array[down] = array[currentSize];
    return down;//此时return的是一次操作基准值放的位置
}

template<class T>
void LinearSort<T>::SelectSort() {
    int i, j, pos;
    for (i = 0; i < currentSize; i++) {
        pos = i;
        //前i个单元已经有序
        for (j = i + 1; j < currentSize; j++) {
            if (array[j] < array[pos])
                pos = j;
        }
        if (pos != j) {
            swap(i, pos);
        }
    }
}

template<class T>
void LinearSort<T>::MatchSort() {
//    int nodeNum = 1;
//    MatchNode *tree;
//    while(nodeNum < currentSize){
//        nodeNum *= 2;
//    }
//    tree = new MatchNode[nodeNum];
//    for(int i = 0, j = currentSize/2; i < currentSize; i++, j++){
//        tree[i].data = array[i];
//    }
//    for(int i = currentSize/2; i < currentSize; i = i + 2){
//        int j = i;
//        while(j > 0){
//            if(tree[j].data < tree[j + 1].data){
//                tree[(j - 1)/ 2].id = j;
//                tree[(j - 1)/ 2].data = tree[j].data;
//            }
//            else{
//                tree[(j - 1)/ 2].id = j + 1;
//                tree[(j - 1)/ 2].data = tree[j + 1].data;
//            }
//            j = (j - 1) / 2;
//        }
//    }
//    for(int i = 0; i < currentSize; i++)
//    {
//        array[i] = tree[0].data;
//        int j = (i % 2 == 0) ? i - 1 : i + 1;//右孩子编号为偶数
//        tree[(j - 1) / 2].data = tree[j].data;
//        tree[(j - 1) / 2].id = tree[j].id;
//        j = (j - 1) / 2;
//        while(j > 0){
//            int k = (j % 2 == 0) ? j - 1 : j + 1;
//            if(tree[j].data)
//        }
//    }
}


int main() {
    int test1[10] = {9, 8, 3, 7, 1, 6, 0, 5, 2, 4};
    int test2[10] = {9, 1, 2, 3, 4, 5, 6, 7, 8, 0};
    int test3[10];
    for (int i = 0; i < 10; i++)
        test3[i] = (int) (rand() % 1000);

    LinearSort<int> linear1;
    linear1.changeArray(test1, 10);
    linear1.BubbleSort();
    linear1.printArray();

//    cout << endl << "插入排序" << endl;
//    linear1.changeArray(test1, 10);
//    linear1.InsertSort();
//    linear1.printArray();

//    cout << endl << "折半插入排序" << endl;
//    linear1.changeArray(test1, 10);
//    linear1.BinaryInsertSort();
//    linear1.printArray();

//    cout << endl << "快速排序" << endl;
//    linear1.changeArray(test1 ,10);
//    linear1.QuickSort();
//    linear1.printArray();

//    cout << endl << "希尔排序" << endl;
////    linear1.changeArray(test1 ,10);
////    linear1.ShellSort();
////    linear1.printArray();

//    cout << endl << "选择排序" << endl;
//    linear1.changeArray(test1 ,10);
//    linear1.SelectSort();
//    linear1.printArray();


//    int temp[20000];
//    for(int i = 0; i < 20000; i++)
//        temp[i] = (int)(rand() % 100000);
//    myClock a;
////    LinearSort<int> linear1(temp, 2000);
//    linear1.changeArray(temp, 20000);
//    a.start();
//    linear1.ShellSort();
//    a.end();
//
//    linear1.changeArray(temp, 20000);
//    a.start();
//    linear1.QuickSort();
//    a.end();
//    linear1.printArray();
//
//    linear1.changeArray(test3, 2000);
//    a.start();
//    linear1.BubbleSortBothWay();
//    a.end();
//    linear1.printArray();

//    system("pause");
}