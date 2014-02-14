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

yum install -y sysstat strace 

sysctl -w vm.overcommit_memory=2
sysctl -w vm.overcommit_ratio=99
sysctl -w vm.swappiness=0

gcc -lpthread -std=gnu99 -W /vagrant/out-of-memory.c -o /vagrant/out-of-memory
SCRIPT

Vagrant.configure(VAGRANTFILE_API_VERSION) do |config|
  config.vm.box     = "CentOS 6.5 x86_64"
  config.vm.box_url = "https://github.com/2creatives/vagrant-centos/releases/download/v6.5.1/centos65-x86_64-20131205.box"
  config.vm.provision "shell", inline: $script
end
