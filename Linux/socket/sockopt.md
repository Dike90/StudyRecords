### getsockopt和setsockopt

```c++
#include <sys/socket.h>
int getsockopt(int sockfd, int levl , int optname, void *optval , socklen_t *optlen);
int setsockopt(int sockfd, int levl , int optname, const void *optval, socklen_t optlen);

							return 0 on success,or -1 on error;
```

* **sockfd**必须指向一个打开的套接字描述符。
* **level**指定系统中解释选项的代码。可以为下列代码：
  * SOL_SOCKET:基本套接字接口。
  * IPPROTO_IP:IPv4套接口。
  * IPPROTO_IPv6：IPv6套接口。
  * IPPROTO_TCP：TCP套接字接口。
* **optval**是一个指向某个变量的指针，setsockopt从\*optval中取得选项待设置的新值，getsockopt则把已获取的选项当前值存放到\*optval中。
* **optlen**指定optval参数的大小。