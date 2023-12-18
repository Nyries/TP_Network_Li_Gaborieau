# Lab Work Synthesis – TFTP Client

Objectives: Develop a TFTP client using RFC specifications and Wireshark captures.

## Q1 : Use command-line arguments for the gettftp and puttftp programs to obtain request information (server and file).

The gettftp and puttftp programs accept command-line arguments to specify the TFTP server, port and file concerned.


## Q2 : Call getaddrinfo to obtain the server’s address.

The program uses the getaddrinfo function to resolve the server name and obtain the address information needed to establish the connection.

## Q3 : Reserve a connection socket to the server.

A socket is reserved using the address information obtained, enabling a connection to be established with the TFTP server.

## Q4 : For gettftp:

The questions are similar to Q4, but care must be taken to change the OPcode to 02 as indicated in 


We use the informations on https://datatracker.ietf.org/doc/html/rfc1350 : 
<img width="726" alt="image" src="https://github.com/Nyries/TP_Network_Li_Gaborieau/assets/152593516/8e688a13-1a0a-48b2-b617-4e0cf9a0cd72">

<img width="726" alt="image" src="https://github.com/Nyries/TP_Network_Li_Gaborieau/assets/152593516/774bcaf1-32a5-4007-a178-df10222243fd">

<img width="523" alt="image" src="https://github.com/Nyries/TP_Network_Li_Gaborieau/assets/152593516/78b71a01-b732-4c74-9f02-34f88083189e">



- a) Build a properly formed Read Request (RRQ) and send it to the server.
  
The program constructs a correct RRQ request and sends it to the TFTP server to request the download of a file.

- b) Receive a file consisting of a single Data (DAT) packet and its acknowledgment
(ACK).

The program is able to receive a file consisting of a single data packet and send the corresponding acknowledgement to the server.

- c) Receive a file consisting of multiple Data (DAT) packets and their respective acknowledgments (ACK).

The program supports the reception of files made up of several data packets and sends the corresponding acknowledgements.

## Q5 : For puttftp : 

the questions are similar to Q4, but we have to change the opcode to 02 as indicated in the sources above. 

- a) Build a properly formed Write Request (WRQ) and send it to the server.
- b) Send a file consisting of a single Data (DAT) packet and receive its acknowledg-
ment (ACK)
- c) Send a file consisting of multiple Data (DAT) packets and receive the irrespective
acknowledgments (ACK).


## Q6 : Use the blocksize option : 










