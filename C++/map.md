### map

标准库map类型是一种以键-值(key-value)存储的数据类型,它是有序的。由于是有序的，所以一般来说它要比unordered_map要慢。

在一个map中，是依照key的值来排序的，并且依靠key来区分不同元素，value是与key相关联的内容。

map的元素类型是value_type.

`typedef pair<cosnt key, T> value_type;`

value_type是一个pair类型

* #### pair类型

  pair类型定义在utility头文件中，一个pair保存两个数据成员。

  ```c++
  #include<utility>
  template <class T1,class T2>
  struct pair;
  ```

  它有两个公有的成员变量，first和second。

  * 初始化

    ```c++
    pair<string,int> p;
    pair<int, double> p(23,4.5);
    pair<int, int> p2;
    p2 = make_pair(23.2,'A'); //p2.first=23, p2.second = 65;
    //make_pair根据传入的类型，推断pair类型(pair<int,char>)，之所以能赋值时因为在赋值时发生了隐式转换
    ```

* #### map类型

  ```c++
  #include<map>
  template <class Key,	//map::key_value
  	class T,			//map::mapped_value
  	class Compare = less<Key>,//map::key_compare
  	class Alloc = allocator<pair<const Key,T>> //map::allocator_type
        > class map;
  ```

  * 定义和初始化

    ```c++
    map<string,int> m; //一个空map
    map<string,string> m2(m.begin() , m.end());//依据迭代器来初始化m2
    map<string,int> m3(m2);//m3是m2的副本
    ```

  * 元素的插入

    ```c++
    m.insert(v);//v是一个value_type对象
    m.insert(b,e);//b，e是迭代器
    m.insert(p,v);//p是一个迭代器，指明从哪里开始搜索v应该存储的位置。
    m[k]=v;//如果k不在map中，则添加k-v元素；如果k在map中，返回k所关联的值
    ```

  * 访问元素

    ```c++
    m.find(k);//返回一个迭代器，指向k的元素，若k不在map中，返回一个尾后迭代器。
    m.count(k);//返回k的数量。map中永远为1或0；
    ```

  * 删除元素

    ```c++
    m.erase(k);//删除关键字为k的元素
    m.erase(p);//从m中删除迭代器p所指的元素；返回一个指向p之后的迭代器，若p指向m中的尾元素，返回m.end();
    m.erase(b,e);//删除迭代器b,e所表示的范围中的元素，返回e
    ```

  * 迭代器

    ```c++
    map<string,int> m4;
    m4["abc"]=123;
    map<string,int>::iterator it;
    it = m4.begin();
    it->first = "hello"; //error,key_value是const的
    it->second++;//正确。m4["abc"]=124;
    ```

    ​