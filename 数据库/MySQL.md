### 1.检索数据

* SELECT语句

  ```mysql
  SELECT column1,column2,... FROM table;
  ```

  * 检索不同的行

    ```mysql
    SELECT DISTINCT column1,column2,... FROM table;
    #DISTINCT语句不能部分使用
    #会修饰所有的列
    ```

  * 限制结果

    ```mysql
    SELECT column1,column2,... FROM table LIMIT line_count;
    SELECT column FROM table LIMIT line_no , line_count;
    ```

    ​

    SELECT 列名 FROM 表名 LIMIT 行号，行数；（从第0行开始算）

### 2.排序检索数据

* 排序数据

  `SELECT 列名 FROM 表名 ORDER BY 列名`

  ```sql
  SELECT 列名1 ,列名2,... FROM 表名 ORDER BY 列名1，列名2；
  //首先按照列名1排序，列名1相同再按列名2排序
  ```

* 指定排序方向

  ```mysql
  SELECT column FROM table ORDER BY column DESC;
  SELECT column1, column2 ,... FROM table ORDER BY column1 DESC, column2 DESC;
  #DESC只修饰单独的列，想让所有列都按降序排，都得加DESC；
  #mysql默认是按照升序排序的，不加DESC修饰就按升序排
  ```

  ​

### 3.过滤数据

* WHERE子句

  ​