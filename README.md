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

[vagrant@vagrant-centos65 ~]$ /vagrant/out-of-memory 
[0] malloc success
[1] malloc success

...

[476] malloc success
[477] malloc success
malloc failed: errno = 12, error = Cannot allocate memory
pthread_create failed: errno = 11, error = Resource temporarily unavailable
```

