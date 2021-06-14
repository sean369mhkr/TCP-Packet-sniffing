#include <iostream>
#include <tins/tins.h>

using namespace Tins;
using namespace std;
int countto=0;

int main(int argc, char *argv[]) {
    string device="";
    string pcap_path="";
  for (int i = 0; i < argc; ++i) {
    if(string(argv[i]) == "-i"){
      device=argv[i+1];
      cout << "Interface: " << device <<endl;
    }
    else if(string(argv[i]) =="-f"){
      pcap_path=argv[i+1];
      cout << "Filepath: " << pcap_path <<endl;
    }
  }
  if(device == ""){
    cout << "No Interface"<<endl;
    return false;
  }
  if(pcap_path == ""){
    cout << "No Filepath"<<endl;
    return false;
  }
  
    // We'll write packets to /tmp/test.pcap. The lowest layer will be
    // EthernetII, so we use the appropriate identifier.
    PacketWriter writer(pcap_path, DataLinkType<EthernetII>());


    Sniffer("enp0s3").sniff_loop([&](PDU &pdu) {
        countto=countto+1;
        // Find the IP layer
        const IP &ip = pdu.rfind_pdu<IP>();
        // Find the TCP layer
        const TCP &tcp = pdu.rfind_pdu<TCP>();
        cout << ip.src_addr() << ':' << tcp.sport() << " -> "
             << ip.dst_addr() << ':' << tcp.dport() << endl;
        writer.write(pdu);
        cout << countto << endl;
        if(countto>=500)
            return false;
        else
            return true;
    });

}
