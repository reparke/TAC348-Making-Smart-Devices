double temp;
double humidity;  // both doubles
int precipation;
String description;
String city;

void setup() {
  // Subscribe to the integration response event
  Particle.subscribe("hook-response/WeatherStack", myHandler, MY_DEVICES);
}

/* Webhook response template format
  http://api.weatherstack.com/current (shortens message to a single page)
  {{location.name}}|
  {{current.temperature}}|
  {{current.humidity}}|
  {{current.weather_descriptions.0}}|
  {{current.precip}}|
*/
void myHandler(const char *event, const char *data) {
  Serial.println("Event:\n" + String(event));
  Serial.println("Data:\n" + String(data));

  // if number of response variables are known
  char arrResponse[512];
  strcpy(arrResponse, data);
  char *ptr = arrResponse;

  city = strtok(arrResponse, "|");
  temp = atof(strtok(NULL, "|"));
  humidity = atof(strtok(NULL, "|"));
  description = strtok(NULL, "|");
  precipation = atoi(strtok(NULL, "|"));

  Serial.println(city + "\n  "+ description + "\n  temperature: " +
                 String(temp, 1) + " F\n  humidity: " + String(humidity,1) +
                 "%\n  rainfall: " + String(precipation) + " in");

  // // if number of response variables are unknown
  // char arrResponse[512];
  // strcpy(arrResponse, data);
  // char *ptr = arrResponse;

  // ptr = strtok(arrResponse, "**");
  // while (ptr != NULL) {
  //   Serial.println(ptr);
  //   ptr = strtok(NULL, "**");
  // }
}

void loop() {
  // Get some data
  String data = String(10);
  // Trigger the integration
  Particle.publish("WeatherStack", data, PRIVATE);
  // Wait 60 seconds
  delay(60000);
}
