# TCP-Packet-sniffing

環境建置  
使用資料庫 libtins  
https://github.com/mfontanini/libtins  
  
$ mkdir build  
$ cd build  
$ cmake ../  
如果出現以下問題  
Could NOT find PCAP  
https://www.programmersought.com/article/61643405465/  
Could NOT find Boost  
$ sudo apt-get install libboost-all-dev  
Could NOT find OpenSSL  
$ sudo apt-get install libssl-dev  
  
$ make  
$ sudo make install  
$ ldconfig  
  
編譯檔案  
$ g++ tcp_sniffer.cpp -o tcp_sniffer -ltins  
  
執行  
$ sudo ./tcp_sniffer -i eth0 -f /var/log/tcp_sniffing_log.pcap  
