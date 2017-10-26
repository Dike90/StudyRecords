### list

list是一个顺序容器，它可以在常数时间内从任意位置添加或删除元素，但是不支持随机访问。没有重载[]运算符。要遍历list只能通过迭代器从表头遍历至表尾，或者返过来。

list是以双向链表实现的。它的存储空间是不连续的。

```c++
#include <list>
template<class T, class Alloc=allocator<T>> class list;
```

* list的初始化

  ```c++
  list<int> li; //空的list
  list<string> li2(6,"hello");//6个string = hello
  list<string> li3(li2.begin(), lie.end());//以迭代器初始化，[b,e)
  list<string> li4(li3);//li3的副本
  ```

* list插入删除

  ```c++
  //list支持的常用操作
  li.push_front();
  li.push_back();
  li.pop_front();//删除第一元素，返回void
  li.pop_back();//删除最后一个元素，返回void

  li.insert(p,v);//从迭代器p所指位置插入元素。原迭代器p所指元素后移，p还是指向原来的元素。返回新插入的元素的第一元素的迭代器。
  li.insert(p,n,v);
  li.insert(p,b,e);
  //example
  list<int> mylist;
  list<int>::iterator it;
  for (int i = 1; i<= 5; i++)
    mylist.push_back(i);  // 1 2 3 4 5
  it = mylist.begin(); //to 1
  ++it; //to 2
  mylist.insert(it,10); //1 10 2 3 4 5  it仍然指向2
  mylist.insert(it,2,20); // 1 10 20 20 2 3 4 5

  //删除
  it = mylist.erase(it); //删除迭代器it所指的元素，返回被删元素的下一个元素，如果被删元素是最后一个元素，返回尾后迭代器
  mylist.remove(20); //删除列表中值为20的所有元素，返回void
  //此操作的复杂度与列表大小成正比
  ```

  ​

  ​



