### 系统调用stat()

利用系统调用stat()、lstat()和fstat() ，可获取与文件有关的信息，其中大部分提取自文件i节点。

```c++
#include <sys/stat.h>
int stat(const char* pathname,struct stat* statbuf);
int lstat(const char* pathname,struct stat* statbuf);
int fstat(int fd, struct stat* statbuf);

		All return 0 on success,or -1 on error;
```

* stat()会返回所命名文件的相关信息。
* lstat()和stat()类似，不过如果文件属于符号链接，则返回关于该链接的信息。
* fstat()会返回某个打开的文件描述符所指代的文件的信息。

上述所有系统调用都会在缓冲区返回一个由statbuf所指的stat结构。

```c++
struct stat {
	dev_t	st_dev; //IDs of device on which file resides
  	ino_t	st_ino; //I-node number of file
  	mode_t	st_mode;//File type and permissions
  	nlink_t	st_nlink;//Number of (hard) links to file
  	uid_t	st_uid;//User ID of file owner
  	gid_t	st_gid;//Group ID of file owner
  	dev_t	st_rdev;//IDs for device special files
  	off_t	st_size;//Total file size for I/O(bytes)
  	blksize_t	st_blksize;//Optimal block size for I/O(bytes)
  	blkcnt_t	st_blocks;//Number of (512B) blocks allocated
  	time_t	st_atime;//Time of last file access
  	time_t	st_mtime;//Time of last file modification
  	time_t	st_ctime;//Time of last status change
}
```

