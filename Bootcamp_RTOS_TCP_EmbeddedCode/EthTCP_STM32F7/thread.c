#include "main.h"
char dbuf[400]; // Buffer for data communication
uint8_t ip[5]; // IP address array
int i;



//-------- <<< Use Configuration Wizard in Context Menu >>> -----------------
//   <o>Socket Address Family <0=>IPv4 <1=>IPv6
//   <i> Define either IPv4 or IPv6 connections are accepted
//   <i> Default: 1
#define SOCK_AF        0

//   <o>Socket Local Port <1-65535>
//   <i> Do not set number of port too small,
//   <i> maybe it is already used.
//   <i> Default: 1001
#define SOCK_PORT      4001


static __NO_RETURN void Server (void *arg) {
    SOCKADDR_IN addr;
    int sock, sd, res;
    int type = (int)arg;

    while (1) {
        sock = socket (AF_INET, type, 0);  // Create a socket based on the specified address family (IPv4 or IPv6) and type
        // Timeout 5 sec
        int timeout = 50000;
        setsockopt (sock, SOL_SOCKET, IP_TOS  , (char *)&timeout, sizeof (timeout)); //SOCKET TIME OUT
			
			// Configure the server address
        addr.sin_port        = htons(SOCK_PORT);
        addr.sin_family      = PF_INET;
        addr.sin_addr.s_addr = INADDR_ANY;
      
			// Bind the socket to the specified address and port
        bind (sock, (SOCKADDR *)&addr, sizeof(addr));

      // For TCP sockets, listen for incoming connections and accept the first one
        if (type == SOCK_STREAM)
				{
            listen (sock, 1);
            sd = accept (sock, NULL, NULL);
            closesocket (sock);
            sock = sd;
        }
				
        while (1) 
				{
				 // Receive data from the client
					res = recv (sock, dbuf, sizeof (dbuf), 0 );
								

					//LED1 ON
					if(dbuf[0] == 'L' && dbuf[1] == 'E' && dbuf[2] == 'D' && dbuf[3] == '1' && dbuf[4] == 'O' && dbuf[5] == 'N') 
					{																				
						LED1_ON;
						res = send (sock, " LED1_ON ", 9, 0);
					}
					//LED1 ON
					else if(dbuf[0] == 'L' && dbuf[1] == 'E' && dbuf[2] == 'D' && dbuf[3] == '1' && dbuf[4] == 'O' && dbuf[5] == 'F' && dbuf[6] == 'F') 
					{																						
						LED1_OFF;
						res = send (sock, " LED1_OFF ", 10, 0);
					}
					//LED2 ON
					else if(dbuf[0] == 'L' && dbuf[1] == 'E' && dbuf[2] == 'D' && dbuf[3] == '2' && dbuf[4] == 'O' && dbuf[5] == 'N') 
					{																				
						LED2_ON;
						res = send (sock, " LED2_ON ", 9, 0);
					}
					//LED2 OFF
					else if(dbuf[0] == 'L' && dbuf[1] == 'E' && dbuf[2] == 'D' && dbuf[3] == '2' && dbuf[4] == 'O' && dbuf[5] == 'F' && dbuf[6] == 'F') 
					{																						
						LED2_OFF;
						res = send (sock, " LED2_OFF ", 10, 0);
					}
					//LED3 ON
					else if(dbuf[0] == 'L' && dbuf[1] == 'E' && dbuf[2] == 'D' && dbuf[3] == '3' && dbuf[4] == 'O' && dbuf[5] == 'N') 
					{																				
						LED3_ON;
						res = send (sock, " LED3_ON ", 9, 0);
					}
					//LED3 OFF
					else if(dbuf[0] == 'L' && dbuf[1] == 'E' && dbuf[2] == 'D' && dbuf[3] == '3' && dbuf[4] == 'O' && dbuf[5] == 'F' && dbuf[6] == 'F') 
					{																						
						LED3_OFF;
						res = send (sock, " LED3_OFF ", 10, 0);
					}
					//LED4 ON
					else if(dbuf[0] == 'L' && dbuf[1] == 'E' && dbuf[2] == 'D' && dbuf[3] == '4' && dbuf[4] == 'O' && dbuf[5] == 'N') 
					{																				
						LED4_ON;
						res = send (sock, " LED4_ON ", 9, 0);
					}
					//LED4 OFF
					else if(dbuf[0] == 'L' && dbuf[1] == 'E' && dbuf[2] == 'D' && dbuf[3] == '4' && dbuf[4] == 'O' && dbuf[5] == 'F' && dbuf[6] == 'F') 
					{																						
						LED4_OFF;
						res = send (sock, " LED4_OFF ", 10, 0);
					}
					else if(dbuf[0] == 'R' && dbuf[1] == 'L' && dbuf[2] == 'O' && dbuf[3] == 'N' ) 
					{																						
						//ROLEYI AC
						RELAY_ON; 
						res = send (sock, " RLON ", 6, 0);
					}
					else if(dbuf[0] == 'R' && dbuf[1] == 'L' && dbuf[2] == 'O' && dbuf[3] == 'F' && dbuf[4] == 'F') 
					{																						
						//ROLEYI KAPA
					  RELAY_OFF;
						res = send (sock, " RLOFF ", 7, 0);
					}
					else if(dbuf[0] == 'G' && dbuf[1] == 'E' && dbuf[2] == 'T' && dbuf[3] == 'R' && dbuf[4] == 'L') 
					{																						
						//ROLE DURUMUNU SORGULA
						if(RELAY_STATE==1)
						{
							res = send (sock, " RELAY STATE:ON ", 16, 0);
						}
						else if(RELAY_STATE==0)
						{
						res = send (sock, " RELAY STATE:OFF ", 17, 0);
						}
					}
					
					
          // Clear buffer
					int i = 0;
					for(i=0; i<400; i++){ dbuf[i]= 0x00; }
					if (res <= 0){ break; }
                
        }
				// Check for disconnection or errors
        res = send (sock, "Disconnected...", 15, 0);
        closesocket (sock);
    }
}




// Main application function
void app_main(void *argument)
{
	  // Add a delay before starting the server
	  HAL_Delay(1000);
    netInitialize (); // Initialize the network

    /* Create BSD socket processor threads */
	  /* Create threads for TCP and UDP socket processing */
    osThreadNew (Server, (void *)SOCK_STREAM, NULL);
    //osThreadNew (Server, (void *)SOCK_DGRAM,  NULL);


    while(1)
    {
			
      osThreadFlagsWait (0x01, osFlagsWaitAny, osWaitForever); // Wait for a thread signal or event
		
	
    }
}
