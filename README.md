# Goffi-SLang
Goffi-SLang is a [stack oriented language](https://en.wikipedia.org/wiki/Stack-oriented_programming) inspired in [Porth](https://gitlab.com/tsoding/porth) writed in C++
that can be compiled or simulated.

## Summary
* [Simple math](#Aritmetric-Operators)
* [Built-in Procedures](#Build-in-Procedures)
* [Flow Control](#Flow-Control)
* [Macros](#Macro-definition)
* [standart lib](#stdlib)
* [argc and argv](#argc-argv)
## <div id="Aritmetric-Operators">Aritmetric-Operators</div>	
    result of any operation will be pushed automatically ot the top of the stack
	In comparasions `<` or `>` will push 1 if true and 0 if false.

`=`	EQUALS operand, Usage: `1 1 =` is equivalent to (1 == 1)

`+`	PLUS operand. Usage:  `2 1 +` is equivalent to (2+1) 

`-`	MINUS operand, Usage: `2 1 -` is equivalent to (2-1) 

`<`	LESS THAN operand, Usage:  `2 1 <` is equivalent to (2<1) 

`>`	GREATER THAN operand, Usage:  `2 1 >` is equivalent to (2>1) 

`*`	MULTIPLY operand, example: `2 1 *` is equivalent to (2*1)




# <div id="Build-in-Procedures">Build-in Procedures </div>

`dump` print the last (int) digit in the stack


# <div id="Flow-Control">Flow Control</div>



`if` if->expression->do-block will goto next do-block or jump the whole do-block.
    if 1 do 
	69 dump 
    end

`do` Always close end blocks this will perfome instructions jumps in some scenarios.
    do 1 dump end

`while` while->expr->do-block if expr is false will jump the do-block, otherwise will evaluate the do-block.
    0 while dup 10 < do
	dup dump
	1 +
    end


# <div id="Macro-definition">Macros</div>

--`define`  is used to created a macro, that will be expanded when used 

    example:
      define N as 69 end
      N dump 
    will dump 69

More examples in examples folder, kinda obvious.


# <div id="stdlib"> standart library </div>
## Some procedures in std
    All proc are currently maros

-- `print`  dup dump

-- `puts`   stdout fputs

-- `eputs`  stderr fputs

-- `fputs`  write drop

-- `write`  SYS_write syscall3 

-- `exit`   SYS_exit syscall1 end

## Std constants

--`SYS_read` = 0

--`SYS_write` = 1

--`SYS_open` = 2

--`SYS_close` = 3

--`SYS_stat` = 4

--`SYS_fstat` = 5

--`SYS_lstat` = 6

--`SYS_poll` = 7

--`SYS_lseek` = 8

--`SYS_mmap` = 9

--`SYS_mprotect` = 10

--`SYS_munmap` = 11

--`SYS_brk` = 12

--`SYS_rt_sigaction` = 13

--`SYS_rt_sigprocmask` = 14

--`SYS_rt_sigreturn` = 15

--`SYS_ioctl` = 16

--`SYS_pread_six_four` = 17

--`SYS_pwrite_six_four` = 18

--`SYS_readv` = 19

--`SYS_writev` = 20

--`SYS_access` = 21

--`SYS_pipe` = 22

--`SYS_select` = 23

--`SYS_sched_yield` = 24

--`SYS_mremap` = 25

--`SYS_msync` = 26

--`SYS_mincore` = 27

--`SYS_madvise` = 28

--`SYS_shmget` = 29

--`SYS_shmat` = 30

--`SYS_shmctl` = 31

--`SYS_dup` = 32

--`SYS_dup_two` = 33

--`SYS_pause` = 34

--`SYS_nanosleep` = 35

--`SYS_getitimer` = 36

--`SYS_alarm` = 37

--`SYS_setitimer` = 38

--`SYS_getpid` = 39

--`SYS_sendfile` = 40

--`SYS_socket` = 41

--`SYS_connect` = 42

--`SYS_accept` = 43

--`SYS_sendto` = 44

--`SYS_recvfrom` = 45

--`SYS_sendmsg` = 46

--`SYS_recvmsg` = 47

--`SYS_shutdown` = 48

--`SYS_bind` = 49

--`SYS_listen` = 50

--`SYS_getsockname` = 51

--`SYS_getpeername` = 52

--`SYS_socketpair` = 53

--`SYS_setsockopt` = 54

--`SYS_getsockopt` = 55

--`SYS_clone` = 56

--`SYS_fork` = 57

--`SYS_vfork` = 58

--`SYS_execve` = 59

--`SYS_exit` = 60

--`SYS_wait_four` = 61

--`SYS_kill` = 62

--`SYS_uname` = 63

--`SYS_semget` = 64

--`SYS_semop` = 65

--`SYS_semctl` = 66

--`SYS_shmdt` = 67

--`SYS_msgget` = 68

--`SYS_msgsnd` = 69

--`SYS_msgrcv` = 70

--`SYS_msgctl` = 71

--`SYS_fcntl` = 72

--`SYS_flock` = 73

--`SYS_fsync` = 74

--`SYS_fdatasync` = 75

--`SYS_truncate` = 76

--`SYS_ftruncate` = 77

--`SYS_getdents` = 78

--`SYS_getcwd` = 79

--`SYS_chdir` = 80

--`SYS_fchdir` = 81

--`SYS_rename` = 82

--`SYS_mkdir` = 83

--`SYS_rmdir` = 84

--`SYS_creat` = 85

--`SYS_link` = 86

--`SYS_unlink` = 87

--`SYS_symlink` = 88

--`SYS_readlink` = 89

--`SYS_chmod` = 90

--`SYS_fchmod` = 91

--`SYS_chown` = 92

--`SYS_fchown` = 93

--`SYS_lchown` = 94

--`SYS_umask` = 95

--`SYS_gettimeofday` = 96

--`SYS_getrlimit` = 97

--`SYS_getrusage` = 98

--`SYS_sysinfo` = 99

--`SYS_times` = 100

--`SYS_ptrace` = 101

--`SYS_getuid` = 102

--`SYS_syslog` = 103

--`SYS_getgid` = 104

--`SYS_setuid` = 105

--`SYS_setgid` = 106

--`SYS_geteuid` = 107

--`SYS_getegid` = 108

--`SYS_setpgid` = 109

--`SYS_getppid` = 110

--`SYS_getpgrp` = 111

--`SYS_setsid` = 112

--`SYS_setreuid` = 113

--`SYS_setregid` = 114

--`SYS_getgroups` = 115

--`SYS_setgroups` = 116

--`SYS_setresuid` = 117

--`SYS_getresuid` = 118

--`SYS_setresgid` = 119

--`SYS_getresgid` = 120

--`SYS_getpgid` = 121

--`SYS_setfsuid` = 122

--`SYS_setfsgid` = 123

--`SYS_getsid` = 124

--`SYS_capget` = 125

--`SYS_capset` = 126

--`SYS_rt_sigpending` = 127

--`SYS_rt_sigtimedwait` = 128

--`SYS_rt_sigqueueinfo` = 129

--`SYS_rt_sigsuspend` = 130

--`SYS_sigaltstack` = 131

--`SYS_utime` = 132

--`SYS_mknod` = 133

--`SYS_uselib` = 134

--`SYS_personality` = 135

--`SYS_ustat` = 136

--`SYS_statfs` = 137

--`SYS_fstatfs` = 138

--`SYS_sysfs` = 139

--`SYS_getpriority` = 140

--`SYS_setpriority` = 141

--`SYS_sched_setparam` = 142

--`SYS_sched_getparam` = 143

--`SYS_sched_setscheduler` = 144

--`SYS_sched_getscheduler` = 145

--`SYS_sched_get_priority_max` = 146

--`SYS_sched_get_priority_min` = 147

--`SYS_sched_rr_get_interval` = 148

--`SYS_mlock` = 149

--`SYS_munlock` = 150

--`SYS_mlockall` = 151

--`SYS_munlockall` = 152

--`SYS_vhangup` = 153

--`SYS_modify_ldt` = 154

--`SYS_pivot_root` = 155

--`SYS__sysctl` = 156

--`SYS_prctl` = 157

--`SYS_arch_prctl` = 158

--`SYS_adjtimex` = 159

--`SYS_setrlimit` = 160

--`SYS_chroot` = 161

--`SYS_sync` = 162

--`SYS_acct` = 163

--`SYS_settimeofday` = 164

--`SYS_mount` = 165

--`SYS_umount_two` = 166

--`SYS_swapon` = 167

--`SYS_swapoff` = 168

--`SYS_reboot` = 169

--`SYS_sethostname` = 170

--`SYS_setdomainname` = 171

--`SYS_iopl` = 172

--`SYS_ioperm` = 173

--`SYS_create_module` = 174

--`SYS_init_module` = 175

--`SYS_delete_module` = 176

--`SYS_get_kernel_syms` = 177

--`SYS_query_module` = 178

--`SYS_quotactl` = 179

--`SYS_nfsservctl` = 180

--`SYS_getpmsg` = 181

--`SYS_putpmsg` = 182

--`SYS_afs_syscall` = 183

--`SYS_tuxcall` = 184

--`SYS_security` = 185

--`SYS_gettid` = 186

--`SYS_readahead` = 187

--`SYS_setxattr` = 188

--`SYS_lsetxattr` = 189

--`SYS_fsetxattr` = 190

--`SYS_getxattr` = 191

--`SYS_lgetxattr` = 192

--`SYS_fgetxattr` = 193

--`SYS_listxattr` = 194

--`SYS_llistxattr` = 195

--`SYS_flistxattr` = 196

--`SYS_removexattr` = 197

--`SYS_lremovexattr` = 198

--`SYS_fremovexattr` = 199

--`SYS_tkill` = 200

--`SYS_time` = 201

--`SYS_futex` = 202

--`SYS_sched_setaffinity` = 203

--`SYS_sched_getaffinity` = 204

--`SYS_set_thread_area` = 205

--`SYS_io_setup` = 206

--`SYS_io_destroy` = 207

--`SYS_io_getevents` = 208

--`SYS_io_submit` = 209

--`SYS_io_cancel` = 210

--`SYS_get_thread_area` = 211

--`SYS_lookup_dcookie` = 212

--`SYS_epoll_create` = 213

--`SYS_epoll_ctl_old` = 214

--`SYS_epoll_wait_old` = 215

--`SYS_remap_file_pages` = 216

--`SYS_getdents_six_four` = 217

--`SYS_set_tid_address` = 218

--`SYS_restart_syscall` = 219

--`SYS_semtimedop` = 220

--`SYS_fadvise_six_four` = 221

--`SYS_timer_create` = 222

--`SYS_timer_settime` = 223

--`SYS_timer_gettime` = 224

--`SYS_timer_getoverrun` = 225

--`SYS_timer_delete` = 226

--`SYS_clock_settime` = 227

--`SYS_clock_gettime` = 228

--`SYS_clock_getres` = 229

--`SYS_clock_nanosleep` = 230

--`SYS_exit_group` = 231

--`SYS_epoll_wait` = 232

--`SYS_epoll_ctl` = 233

--`SYS_tgkill` = 234

--`SYS_utimes` = 235

--`SYS_vserver` = 236

--`SYS_mbind` = 237

--`SYS_set_mempolicy` = 238

--`SYS_get_mempolicy` = 239

--`SYS_mq_open` = 240

--`SYS_mq_unlink` = 241

--`SYS_mq_timedsend` = 242

--`SYS_mq_timedreceive` = 243

--`SYS_mq_notify` = 244

--`SYS_mq_getsetattr` = 245

--`SYS_kexec_load` = 246

--`SYS_waitid` = 247

--`SYS_add_key` = 248

--`SYS_request_key` = 249

--`SYS_keyctl` = 250

--`SYS_ioprio_set` = 251

--`SYS_ioprio_get` = 252

--`SYS_inotify_init` = 253

--`SYS_inotify_add_watch` = 254

--`SYS_inotify_rm_watch` = 255

--`SYS_migrate_pages` = 256

--`SYS_openat` = 257

--`SYS_mkdirat` = 258

--`SYS_mknodat` = 259

--`SYS_fchownat` = 260

--`SYS_futimesat` = 261

--`SYS_newfstatat` = 262

--`SYS_unlinkat` = 263

--`SYS_renameat` = 264

--`SYS_linkat` = 265

--`SYS_symlinkat` = 266

--`SYS_readlinkat` = 267

--`SYS_fchmodat` = 268

--`SYS_faccessat` = 269

--`SYS_pselect_six` = 270

--`SYS_ppoll` = 271

--`SYS_unshare` = 272

--`SYS_set_robust_list` = 273

--`SYS_get_robust_list` = 274

--`SYS_splice` = 275

--`SYS_tee` = 276

--`SYS_sync_file_range` = 277

--`SYS_vmsplice` = 278

--`SYS_move_pages` = 279

--`SYS_utimensat` = 280

--`SYS_epoll_pwait` = 281

--`SYS_signalfd` = 282

--`SYS_timerfd_create` = 283

--`SYS_eventfd` = 284

--`SYS_fallocate` = 285

--`SYS_timerfd_settime` = 286

--`SYS_timerfd_gettime` = 287

--`SYS_accept_four` = 288

--`SYS_signalfd_four` = 289

--`SYS_eventfd_two` = 290

--`SYS_epoll_create_one` = 291

--`SYS_dup_tree` = 292

--`SYS_pipe_two` = 293

--`SYS_inotify_init_one` = 294

--`SYS_preadv` = 295

--`SYS_pwritev` = 296

--`SYS_rt_tgsigqueueinfo` = 297

--`SYS_perf_event_open` = 298

--`SYS_recvmmsg` = 299

--`SYS_fanotify_init` = 300

--`SYS_fanotify_mark` = 301

--`SYS_prlimit_six_four` = 302

--`SYS_name_to_handle_at` = 303

--`SYS_open_by_handle_at` = 304

--`SYS_clock_adjtime` = 305

--`SYS_syncfs` = 306

--`SYS_sendmmsg` = 307

--`SYS_setns` = 308

--`SYS_getcpu` = 309

--`SYS_process_vm_readv` = 310

--`SYS_process_vm_writev` = 311

--`SYS_kcmp` = 312

--`SYS_finit_module` = 313


#<div id=argc-argv>Argument count and argument value</div>

To access command argc/argv you can use the built-in keyword __argc and __argv

__argc and __argv
NOTE: __argc is a pointer so to access you have to dereference the ptr. Example: __argc -> dump
OBS: -> is inside std.gfsl but is equivalent to load64

