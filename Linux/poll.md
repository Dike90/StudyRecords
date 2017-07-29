### poll系统调用

```c++
#include <poll.h>
int poll(struct pollfd fds[], nfds_t nfds, int timeout);
```

* fds参数列出了我们需要poll()来检查的文件描述符。该参数是pollfd结构数组。

  ```c++
  struct pollfd {
    int fd;		//File descriptor
    short events;	//Request events bit mask
    short revents;//Returned events bit mask
  };
  ```

* nfds指定了数组fds中元素的个数，数据类型nfds_t为无符号整形

* timeout决定了poll()的阻塞行为

  - 如果timeout等于-1，poll()会一直阻塞直到fds数组中列出的文件描述符有一个达到就绪态或者捕获到一个信号。

  - 如果timeout等于0，poll()不会阻塞，只是执行一次检查看看哪个文件描述符处于就绪态

  - 如果timeout大于0，poll()至多阻塞timeout毫秒，直到fds列出的文件描述符中有一个达到就绪态，或者捕获到一个信号为止。

* poll()的返回值

  * 返回-1，表示有错误发生。一种可能的错误是EINTR，表示调用被一个信号处理例程中断。
  * 返回0，表示该调用在任意一个文件描述符成为就绪态之前就超时了。
  * 返回正整数，表述有一个或者多个文件描述符处于就绪态了。返回值表述数组fds中拥有非零revents字段的pollfd结构体数量。

> 如果一个文件描述符在返回的描述符集合中出现了不止一次，系统调用select()会将同一个文件描述符计数多次。而系统调用poll()返回的是就绪态的文件描述符个数，且一个文件描述符只会统计一次，就算在相应的revents字段中设定了多个位掩码也是如此。

就TCP和UDP套接字而言，一下条件引起poll返回特定的revents。（有多种方法可能返回相同的条件）

* 所有正规TCP数据和所有UDP数据都被认为是普通数据
* TCP的带外数据被认为是优先级带数据
* 当TCP连接读半关闭时（例如收到了一个来自对端的FIN），也被认为是普通数据，随后的读操作将返回0.
* TCP连接存在错误既可以认为是普通数据，也可以认为是错误(POLLERR)。无论哪种情况，随后的读操作将返回-1，并把errno设置成合适的值。这可用于处理诸如接收到RST或发生的超时等条件。
* 在监听套接字上又新的连接可用既可认为是普通数据，也可认为是优先级数据。大多数实现视为普通数据。
* 非阻塞式connect的完成被认为是使相应的套接字可写。