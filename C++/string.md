### string常用操作

* #### find 和rfind

  返回值是一个string::size_t类型，这是一个无符号整型。

  值是第一个匹配符的位置（从0开始算），如果找不多返回string::npos；由于它是一个size_t类型是一个无符号整型，所以表示最大的size_t值。

  find默认从前向后找，rfind默认从后往前找。

  ```c++
  string str="abcdef";
  int pos = str.find('b'); //pos=1;
  int pos = str.find("cde"); //pos =2;
  ```

* #### substr

  ```c++
  string substr(size_t pos=0 , size_t len=npos) const;
  ```

  * **pos**表示第一个被复制的位置，这个位置的字符会被复制。
  * **len**表示复制的长度

  ```c++
  string str = "abcdefg";
  string sub = str.substr(0,5);//sub="abcde" 
  ```

* #### replace

  将指定位置的字符，替换成一个指定的字符。原字符串其他位置的字符保持不变。

  ```c++
  string base = "this is a test string";
  string rep = "n example";
  base.replace(9,5,rep);
  //表示从下标9开始，替换5个字符。替换为rep，原string其他位置的字符不变
  ```

  ​