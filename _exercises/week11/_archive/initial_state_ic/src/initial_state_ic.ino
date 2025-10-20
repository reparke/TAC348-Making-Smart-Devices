
/*

everything that goes to intial state NEEDS to be in json format
{"key":"temperature", "value":79}

[ {}, {} ]

*/

void setup() {
  Serial.begin(9600);
}

void loop() {
    // String data = "{\"key\":\"temperature\", \"value\":79}";
    int temperature = random(74, 83);
    String weather = "sunny";

    /*
    [
      {"key":"temperature":"value":TEMP_VAR},
      {"key":"weather", "value":"WEATHER_VAR"}
    ]
    */

    String data = "[{\"key\":\"temperature\", \"value\":" + String(temperature) + "},{\"key\":\"weather\",\"value\":\""+weather+"\"}]";

    // Trigger the integration
    Particle.publish("initial_state_20203", data, PRIVATE);
    // Wait 60 seconds
    delay(5000);
}