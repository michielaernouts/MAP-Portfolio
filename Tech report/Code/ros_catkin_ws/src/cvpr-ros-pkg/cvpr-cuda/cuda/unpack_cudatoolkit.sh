#!/usr/bin/expect -f
set cudatoolkit_dst [lindex $argv 0]
spawn tmp/cudatoolkit_4.1.28_linux_64_ubuntu11.04.run -- --prefix=$cudatoolkit_dst
expect "Would you like to uninstall?"
send "yes\r"
interact
