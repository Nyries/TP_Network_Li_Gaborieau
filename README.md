# Lab Work Synthesis – TFTP Client

Objectives: Develop a TFTP client using RFC specifications and Wireshark captures.

## Q1 : Use command-line arguments for the gettftp and puttftp programs to obtain request information (server and file).

The gettftp and puttftp programs accept command-line arguments to specify the TFTP server, port and file concerned.


## Q2 : Call getaddrinfo to obtain the server’s address.

The program uses the getaddrinfo function to resolve the server name and obtain the address information needed to establish the connection.

## Q3 : Reserve a connection socket to the server.

A socket is reserved using the address information obtained, enabling a connection to be established with the TFTP server.

## Q4 : For gettftp:
- a) Build a properly formed Read Request (RRQ) and send it to the server.
  
The program constructs a correct RRQ request and sends it to the TFTP server to request the download of a file.

- b) Receive a file consisting of a single Data (DAT) packet and its acknowledgment
(ACK).

The program is able to receive a file consisting of a single data packet and send the corresponding acknowledgement to the server.

- c) Receive a file consisting of multiple Data (DAT) packets and their respective acknowledgments (ACK).

The program supports the reception of files made up of several data packets and sends the corresponding acknowledgements.

## Q5 : For puttftp : 
- a) Build a properly formed Write Request (WRQ) and send it to the server.
- b) Send a file consisting of a single Data (DAT) packet and receive its acknowledg-
ment (ACK)
- c) Send a file consisting of multiple Data (DAT) packets and receive the irrespective
acknowledgments (ACK).









