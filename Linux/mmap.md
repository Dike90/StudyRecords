### mmap

mmap()系统调用在调用进程的虚拟地址空间创建一个新映射。

```c++
#include <sys/mman.h>
void *mmap(void *addr, size_t length, int prot , int flags, int fd , off_t offset);

return starting address of mapping on success,or MAP_FAILED on error;
```

* **addr**参数指定了映射被放置的虚拟地址。如果将addr指定为NULL，那么内核会为映射选择一个合适的地址。

* **length**参数指定了映射的字节数。实际上length会被提升为分页大小的下一个倍数。

* **prot**参数是一个位掩码，它指定了施加于映射之上的保护信息。可取以下值：

  |     值      |   描述    |
  | :--------: | :-----: |
  | PROT_NONE  | 区域无法访问  |
  | PROT_READ  | 区域内容可读取 |
  | PROT_WRITE | 区域内容可修改 |
  | PROT_EXEC  | 区域内容可执行 |

* **flags**参数是一个控制映射操作各个方面的选项的位掩码。这个掩码必须为MAP_PRIVATE或MAP_SHARED之一。

* **fd**参数表示一个打开文件的文件描述符。

* **offset**参数指定了从文件区域中哪个字节开始映射，它必须是系统分页大小的倍数。