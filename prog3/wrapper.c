#include <asm/unistd.h>
#include <sys/syscall.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdint.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <unistd.h>

#ifndef COMMON_ARC_STRACE_H_
#define COMMON_ARC_STRACE_H_
#endif

extern "C" {
	ARC_EXPORT int __wrap_unlink(const char* pathname);
	ARC_EXPORT int __wrap_ftruncate(int fd, off_t length);
	ARC_EXPORT int __wrap_truncate(const char* path, off_t length);
}

/* create pointers for real functions */
int *__real_truncate (const char, off_t);
int *__real_ftruncate(int, off_t);
int *__real_unlink(const char*);

/* my Truncate implementation */
static int TruncateImpl(const char* pathname, off_t length) {
	ARC_STRACE_ENTER("truncate", "\"%s\", %lld",
        SAFE_CSTR(pathname), static_cast<int64_t>(length));
		
	int result = VirtualFileSystem::GetVirtualFileSystem()->truncate(pathname, length);
	
	if (result == -1) {
		DANGERF("path=%s length=%lld: %s",
			SAFE_CSTR(pathname), static_cast<int64_t>(length),
            safe_strerror(errno).c_str());
	}
	
	ARC_STRACE_RETURN(result);
}

int *__wrap_truncate (const char *pathname, off_t length) {
	return TruncateImpl(pathname, length);
	#ifndef NOCALL
		syscall(truncate id,file,length);
	#endif
}

/* my Ftruncate implementation */
static int FtruncateImpl(int fd, off_t length) {
	ARC_STRACE_ENTER_FD("ftruncate", "%d, %lld",
		fd, static_cast<int64_t>(length));
		
	int result = VirtualFileSystem::GetVirtualFileSystem()->ftruncate(fd, length);
	
	if (result == -1) {
		DANGERF("fd=%d length=%lld: %s", fd, static_cast<int64_t>(length),
            safe_strerror(errno).c_str());
	}
	
	ARC_STRACE_RETURN(result);
}

int __wrap_ftruncate(int fd, off_t length) {
	return FtruncateImpl(fd, length);
	#ifndef NOCALL
		syscall(ftruncate id,fd,length);
	#endif
}

/* my Unlink implementation */
int __wrap_unlink(const char* pathname) {
	ARC_STRACE_ENTER("unlink", "\"%s\"", SAFE_CSTR(pathname));
  
	int result = VirtualFileSystem::GetVirtualFileSystem()->unlink(pathname);
  
	if (result == -1 && errno != ENOENT) {
		DANGERF("path=%s: %s", SAFE_CSTR(pathname), safe_strerror(errno).c_str());
	}
	
	#ifndef NOCALL
		syscall(unlink id,file);
	#endif
	
	ARC_STRACE_RETURN(result);
}

int rename(const char *oldpath, const char *newpath) {
	printf("Renaming <%s> to <%s>\n",oldpath,newpath);
	return(syscall(__NR_rename,oldpath,newpath));
}