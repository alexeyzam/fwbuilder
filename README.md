[![Build Status](https://travis-ci.org/fwbuilder/fwbuilder.svg?branch=master)](https://travis-ci.org/fwbuilder/fwbuilder)

fwbuilder
=========

Firewall Builder is a GUI firewall management application for iptables, PF, Cisco ASA/PIX/FWSM, Cisco router ACL and more. Firewall configuration data is stored in a central file that can scale to hundreds of firewalls managed from a single UI.


Installation instructions
=========================


Ubuntu
---------
```
 sudo apt install git cmake libxml2-dev libxslt-dev libsnmp-dev qt5-default qttools5-dev-tools
 git clone https://github.com/fwbuilder/fwbuilder.git
 mkdir build
 cd build
 cmake ../fwbuilder
 make
 sudo make install
```
Note: default destination is /usr/local. This is configurable:
```
 cmake ../fwbuilder -DCMAKE_INSTALL_PREFIX=/usr
```

Create deb package
---------
```
debuild -us -uc --lintian-opts --profile debian
```
Centos
---------
yum install git cmake3 libxml2-devel libxslt-devel  net-snmp-libs qt5-qtbase-devel gcc-c++ -y
git clone https://github.com/alexeyzam/fwbuilder.git
 mkdir build
 cd build
 cmake3 ../fwbuilder
 make
 sudo make install
 
