# Inspect 'Cannot allocate memory' error on Linux 2.6.32

## Applied settings

 * `sysctl -w vm.overcommit_memory=2`
 * `sysctl -w vm.overcommit_ratio=99`
 * `sysctl -w vm.swappiness=0`

## How inspect ?

Start `vagrant ssh` sessions, try these commands

 * `sar -r 1 100`
 * `watch -n0.2 grep Commit /proc/memcinfo`

Start another `vagrant ssh` session and run `/vagrant/out-of-memory`

```
$ vagarnt ssh
```

```
$ /vagrant/out-of-memory
[0] malloc success
[1] malloc success

...

[476] malloc success
[477] malloc success
malloc failed: errno = 12, error = Cannot allocate memory
pthread_create failed: errno = 11, error = Resource temporarily unavailable
```

## Inspect MySQL _ERROR 1135 (HY000): Can't create a new thread (errno 11)_

Start a `vagrant ssh` session

```
$ vagarnt ssh
```

Start mysqld

```
$ sudo /etc/init.d/mysqld start
```

Create many mysql connections

```
$ for i in {0..100}; do mysql -e "select sleep(180)" & done;
```

If Commmited_AS reaches Commitlimit, the following error message appear.

```
ERROR 1135 (HY000): Can't create a new thread (errno 11); if you are not out of available memory, you can consult the manual for a possible OS-dependent bug
```

