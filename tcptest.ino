// MAKE SURE you set the IP, PORT values!

#define SERVER_IP {0,0,0,0}
#define SERVER_PORT 0
#define TIMEOUT_INITIAL_RESPONSE 20000
#define TIMEOUT_RESPONSE_READ 5000
#define RECONNECT_DELAY 3000

void setup()
{
    // Give a person debugging via USB a moment to connect, if they want, before we start
    Serial.begin(9600);
    for(int i = 10;i > 0;i--)
    {
        Serial.println("Starting in " + String(i,DEC));
        delay(1000);
    }
}

void loop()
{
    Serial.println("");
    Serial.println("Connecting...");

    byte ip[] = SERVER_IP;
    TCPClient client;
    client.connect(ip, SERVER_PORT);
    if (client.connected())
    {
        Serial.println("Connected to server.");
        client.println("Hello, server!");

        unsigned int waitCount = 0;
        unsigned long lastTime = millis();

        // Wait until the server either disconnects, gives us a response, or the timeout is exceeded
        Serial.print("Waiting a for response.");
        while(client.connected() && !client.available() && millis() - lastTime < TIMEOUT_INITIAL_RESPONSE)
        {
            // Visual wait indicator for debugging
            if(waitCount++ % 100 == 0)
            {
                Serial.print(".");
            }
            
            // While we are waiting, which could be a while, allow cloud stuff to happen as needed
            SPARK_WLAN_Loop();
        }
        
        // Show a wait summary for debugging
        Serial.println("(wait loops: " + String(waitCount,DEC) + ")");

        // We stopped waiting because we actually got something
        if(client.connected() && client.available())
        {
            waitCount = 0;
            int charCount = 0;
            int lastReadTime = millis();
            
            // Keep going until the server either disconnects, or stops feeding us data in a timely manner
            Serial.print("Reading response.");
            while(client.connected() && millis() - lastReadTime < TIMEOUT_RESPONSE_READ)
            {
                // Visual wait indicator for debugging
                if(waitCount++ % 100 == 0)
                {
                    Serial.print(".");
                }
                
                // We get something!
                while(client.available())
                {
                    char c = client.read();
                    ++charCount;
                    
                    // Visual data received indicator for debugging
                    Serial.print("!");
                    
                    // Make note of when this happened
                    lastReadTime = millis();
                }
            }
            
            // Show a wait/read summary for debugging
            Serial.println("(wait loops: " + String(waitCount,DEC) + ", chars read: " + String(charCount,DEC) + ")");
        }
        else
        {
            Serial.println("No/empty response");
        }
        
        // Just to be nice, let's make sure we finish clean
        Serial.println("Explicit flush");
        client.flush();
        Serial.println("Explicit stop");
        client.stop();
    }
    else
    {
        Serial.println("Connection failed.");
    }

    delay(RECONNECT_DELAY);
}
