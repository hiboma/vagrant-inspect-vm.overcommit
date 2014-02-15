# -*- mode: ruby -*-
# vi: set ft=ruby :

# Vagrantfile API/syntax version. Don't touch unless you know what you're doing!
VAGRANTFILE_API_VERSION = "2"

$script = <<SCRIPT

cat << RC_LOCAL >/etc/rc.local
#!/bin/sh

touch /var/lock/subsys/local

sysctl -w vm.overcommit_memory=2
sysctl -w vm.overcommit_ratio=99
sysctl -w vm.swappiness=0
RC_LOCAL

cat << MYSQL >/etc/my.cnf
[mysqld]
datadir=/var/lib/mysql
socket=/var/lib/mysql/mysql.sock
user=mysql
# Disabling symbolic-links is recommended to prevent assorted security risks
symbolic-links=0
innodb_buffer_pool_size = 280M
MYSQL

yum install -y sysstat strace mysql mysql-server

sysctl -w vm.overcommit_memory=2
sysctl -w vm.overcommit_ratio=99
sysctl -w vm.swappiness=0

gcc -lpthread -std=gnu99 -W /vagrant/out-of-memory.c -o /vagrant/out-of-memory

# swapon /mnt/swapfile
dd if=/dev/zero of=/mnt/swapfile bs=1M count=500
mkswap -f /mnt/swapfile
SCRIPT

Vagrant.configure(VAGRANTFILE_API_VERSION) do |config|
  config.vm.box     = "CentOS 6.5 x86_64"
  config.vm.box_url = "https://github.com/2creatives/vagrant-centos/releases/download/v6.5.1/centos65-x86_64-20131205.box"
  config.vm.provision "shell", inline: $script
end
