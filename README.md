'preadv2' function may return 0 if the file is not cached in memory

##### Device
Rasbperry Pi 4B 4Gb ram

##### OS
Raspbian GNU/Linux 10 (buster)

###### The bug is reproducible with linux kernels:
1. Linux raspberrypi 5.10.0-v7l+ #1382 SMP Tue Dec 15 18:23:34 GMT 2020 armv7l GNU/Linux
2. Linux raspberrypi 5.10.17-v7l+ #1414 SMP Fri Apr 30 13:20:47 BST 2021 armv7l GNU/Linux
3. Linux raspberrypi 5.10.36-v7l+ #1418 SMP Thu May 13 18:17:17 BST 2021 armv7l GNU/Linux

###### And NOT reproducible with:
1. Linux raspberrypi 5.4.81-v7l+ #1378 SMP Mon Dec 7 18:43:09 GMT 2020 armv7l GNU/Linux

##### How to reproduce
```bash
$ dd if=/dev/urandom of=file_450000 bs=1500 count=300
$ echo 1 | sudo tee /proc/sys/vm/drop_caches
$ ./target/release/preadv2_bug_tokio_1.6 file_450000
File size = 4096
$ ./target/release/preadv2_bug_tokio_0.2 file_450000
File size = 450000
$ ./target/release/preadv2_bug_tokio_1.6 file_450000
File size = 450000
```

