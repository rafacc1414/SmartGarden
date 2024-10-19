void InitMDNS()
{
    if (!MDNS.begin(hostname))
    {
        Serial.println("Error starting mDNS");
    }
    Serial.println("mDNS started");
}