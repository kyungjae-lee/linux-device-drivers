#!/bin/bash
##To run this script do
##1. chmod +x usbnet.sh 
##2. ./usbnet.sh 
iptables --table nat --append POSTROUTING --out-interface wlp61s0 -j MASQUERADE
iptables --append FORWARD --in-interface wlp61s0 -j ACCEPT
echo 1 > /proc/sys/net/ipv4/ip_forward
