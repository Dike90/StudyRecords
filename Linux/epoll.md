### 水平触发和边缘触发

* **水平触发**：如果文件描述符上可以非阻塞的执行I/O系统调用，此时认为它已经就绪。
* **边缘触发**：如果文件描述符自上次状态检查以来有了新的I/O活动，此时需要触发通知。

### epoll

epoll API的核心数据结构称作epoll实例，它和一个打开的文件描述符相关联。这个文件描述符不是来做I/O的，相反，它是内核数据结构的句柄，这些内核数据结构实现了两个目的。

* 记录了在进程中声明过的感兴趣的文件描述符列表--interest list
* 维护了处于I/O就绪态的文件描述符列表--ready list

epoll API由以下3个系统调用组成。

* **epoll_create()**系统调用创建一个epoll实例，返回代表该实例的文件描述符。
* **epoll_ctl()**系统调用操作同epoll实例相关联的兴趣列表。通过epoll_ctl()，我们可以从兴趣列表中增加或删除文件描述符，以及修改文件描述符上的感兴趣事件。
* **epoll_wait()**返回与epoll实例相关联的就绪列表中的成员。

#### epoll_create()

```c++
#include <sys/epoll.h>
int epoll_create(int size);

	return file descriptor on sucess,or -1 on error;
```

* **size**参数已经被忽略了。

作为函数返回值，epoll_create()返回了代表新创建的epoll实例的文件描述符。这个文件描述符在剩余两个epoll调用中代表这个epoll实例。当这个描述符不在需要时，应当使用close()来关闭它。

#### epoll_ctl()

```c++
#include <sys/epoll.h>
int epoll_ctl(int epfd, int op, int fd, struct epoll_event *ev);

	return 0 on success,or -1 on error;
```

* **epfd**参数指明了要操作的epoll实例。

* **fd**参数指明了要修改的文件描述。

* **op**参数用来指定需要执行的操作。它可以是如下值：

  * EPOLL_CTL_ADD

    将描述符fd添加到epfd指向的epoll实例的兴趣列表中。同时我们还可以在ev中指定感兴趣的事件。当添加一个已存在描述符时将返回EEXIST错误。

  * EPOLL_CTL_MOD

    修改描述符fd上的设定事件，需要用到ev所指结构体中的信息。当修改不在兴趣列表中的描述符的时候将返回ENOENT错误。

  * EPOLL_CTL_DEL

    将文件描述符fd从epfd指向的epoll实例的兴趣列表中删除。该操作忽略ev参数。当移除一个不在兴趣列表中的fd时，发生ENOENT错误。

* **ev**参数是指向epoll_event结构体的指针，结构体定义如下。

  * 结构体events字段是一个位掩码，它指定了我们感兴趣的事件集合。
  * data字段是一个联合体，当描述符fd稍后成为就绪态时，联合体的成员可用来指定传回调用进程的信息。

```c++
struct epoll_event {
	uint32_t		events;//epoll events(bit mask)
  	epoll_data_t	data;//User data	
};

typedef union epoll_data {
 	void		*ptr;//Pointer to user-defined data
  	int 		fd;//File descriptor
  	uint32_t	u32;//32-bit integer;
  	uint64_t	u64;//64-bit integer;
}	epoll_data_t;
```

使用例子	

```c++
int epfd;
struct epoll_event ev;
epfd = epoll_create(5);
if (epfd == -1)
  //error handle
ev.data.fd = fd;//当指定的事件发生时，这个值会返回给用户。
ev.events = EPOLLIN;
if (epoll_ctl(epfd, EPOLL_CTL_ADD, fd , ev) == -1)
  //error handle
```

#### epoll_wait()

系统调用epoll_wait()返回epoll实例中处于就绪的文件描述符信息。

```c++
#include <sys/epoll.h>
int epoll_wait(int epfd, struct epoll_events *evlist, int maxevents, int timeout);

	return number of ready file descriptors,0 on timeout,or -1 on error
```

* **epfd**指定要等待的epoll实例。

* **evlist**参数所指的结构体数组中返回的是有关就绪文件描述符的信息。数组evlist空间由调用者负责申请，所包含的元素个数在参数**maxevents**中指定。

  ​	在数组evlist中，每个元素返回的都是单个就绪文件描述符的信息。events字段返回了在该描述符上已经发生的事件掩码。data字段返回的是我们在注册感兴趣事件在ev.data中所指定的值。data字段是唯一可获知同这个事件关联的文件描述符的途径。因此，当我们注册感兴趣事件时，应当将ev.data.fd设为文件描述符，或者ev.data.ptr指向包含文件描述符的结构体。

* **timeout**参数用来确定epoll_wait()的阻塞行为。

  * timeout = -1,调用将一直阻塞，直到兴趣列表中的文件描述符有事件发生或者捕获到了一个信号。

  * timeout = 0,执行一次非阻塞的检查。立即返回。

  * timeout > 0,调用将阻塞至多timeout毫秒。

epoll_wait()调用成功后，返回数组evlist中元素的个数。如果timeout时间超时的时间内没有任何文件描述符就绪，返回0，出错时返回-1，并在errno中设置错误码。

​	在多线程编程时，可以在一个线程中使用epoll_ctl()将文件描述符添加到另一个线程所监视的epoll实例的兴趣列表中去。这些对兴趣列表的修改将立刻得到处理，epoll_wait调用将返回新的就绪信息。

#### epoll事件

|     位掩码      | 作为epoll_ctl()的输入 | 由epoll_wait()返回 |      描述       |
| :----------: | :--------------: | :-------------: | :-----------: |
|   EPOLLIN    |        *         |        *        |  可读非高优先级的数据   |
|   EPOLLPRI   |        *         |        *        |   可读高优先级数据    |
|  EPOLLRDHUP  |        *         |        *        |    套接字对端关闭    |
|   EPOLLOUT   |        *         |        *        |    普通数据可写     |
|   EPOLLET    |        *         |                 |  采用边缘触发事件通知   |
| EPOLLONESHOT |        *         |                 | 在完成事件通知之后禁用检查 |
|   EPOLLERR   |                  |        *        |     有错误发生     |
|   EPOLLHUP   |                  |        *        |     出现挂断      |

​	**EPOLLONESHOT**标志

​	默认情况下，一旦通过epoll_ctl()的EPOLL_CTL_ADD操作将文件描述符添加到epoll实例的兴趣列表后，它会保持激活状态，直到我们将它从兴趣列表中移除。如果我们希望在某个特定的文件描述符上只得到一次通知，那么可以在传给epoll_ctl()的ev.events中指定EPOLLONESHOT标志。当这个文件描述就绪一次后，就处于非激活状态了，就不会再收到它的就绪状态了。需要重新使用epoll_ctl()的EPOLL_CTL_MOD操作重新激活。