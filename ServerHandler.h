/*
  ServerHandler.h - Library for receive Http Requests and send Http responses.
  Created by Joan Ortega, jomaora@gmail.com Feb. 29, 2016.
  Released into the public domain.
*/

#ifndef ServerHandler_h
#define ServerHandler_h

#include "Arduino.h"
#include <Ethernet.h>

class ServerHandler
{
    public:
        ServerHandler(EthernetServer *server, byte mac[], int ipRanges[]) {
            _server = server;
            for (int i = 0; i < 6; i++) {
                _mac[i] = mac[i];
            }
            _ip = IPAddress(ipRanges[0], ipRanges[1], ipRanges[2], ipRanges[3]);
            _requestReceived = false;
        }

        void    init();
        bool    listenRequest();

        void    enableLogs() { _activeLogs = true; }
        void    disableLogs() { _activeLogs = false; }

    private:
        void    readRequest();
        void    resetRequest();

        EthernetServer *_server;
        EthernetClient _client;
        byte _mac[6];
        IPAddress _ip;

        bool _requestReceived = false;
        int  _readingStatus = 0;

        /*Variables to store request from Client*/
        String _requestLine = "";
        String _requestBody = "";
        String _requestHeaders = "";

        /*Counter on \n and \r characters sent by the API in the response, to identify which element have been read*/
        int  _returnCharCount = 0;
        bool _activeLogs = false;
};
 #endif