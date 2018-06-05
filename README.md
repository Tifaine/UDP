# UDP
An exemple of C++ UDP client and server

# compile
server : g++ udp_server.cpp essai_server.cpp udp_manager.cpp -std=c++11 -lpthread -o server

client : g++ udp_client.cpp essaiClient.cpp -std=c++11 -lpthread -o client
