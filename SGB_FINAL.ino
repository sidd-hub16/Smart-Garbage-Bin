#include <WiFi.h>
#include <WebServer.h>

#define TRIG_PIN 18
#define ECHO_PIN 19
#define BUZZER 21

const char* ssid = "SIDDHU";
const char* password = "12345678";

WebServer server(80);

long duration;
float distance;

// Function to measure distance
float getDistance()
{
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH, 30000); // timeout added

  if (duration == 0) return -1; // error case

  return duration * 0.034 / 2;
}

// Webpage handler
void handleRoot()
{
  distance = getDistance();

  String status;
  String color;
  String icon;
  bool isFull = false;

  if (distance < 7)
  {
    status = "Bin is FULL";
    color = "#ff4d4d";
    icon = "⚠️";
    isFull = true;
  }
  else
  {
    status = "Bin is OK";
    color = "#4CAF50";
    icon = "✔️";
  }

  String html = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<meta http-equiv="refresh" content="2">
<title>Smart Garbage Bin</title>

<style>
body {
  margin: 0;
  font-family: 'Segoe UI', sans-serif;
  background: radial-gradient(circle at top, #0f172a, #020617);
  color: white;
  text-align: center;
}

.container {
  width: 90%;
  max-width: 500px;
  margin: auto;
}

.card {
  background: #111827;
  padding: 20px;
  margin: 20px 0;
  border-radius: 15px;
  box-shadow: 0 0 15px rgba(0,0,0,0.5);
}

.status {
  font-size: 22px;
  font-weight: bold;
}
</style>

</head>

<body>

<h1>Smart Garbage Bin Dashboard</h1>

<div class="container">

  <!-- Adyar (REAL DATA) -->
  <div class="card">
    <h2>Adyar Garbage Bin</h2>
    <p class="status" style="color: )rawliteral" + color + R"rawliteral(;">
      )rawliteral" + icon + " " + status + R"rawliteral(
    </p>
    <p>Distance: )rawliteral" + String(distance) + R"rawliteral( cm</p>
  </div>

  <!-- T Nagar (STATIC) -->
  <div class="card">
    <h2>T. Nagar Garbage Bin</h2>
    <p class="status" style="color:#4CAF50;">
      ✔️ Bin is OK
    </p>
  </div>

  <!-- Triplicane (STATIC) -->
  <div class="card">
    <h2>Triplicane Garbage Bin</h2>
    <p class="status" style="color:#4CAF50;">
      ✔️ Bin is OK
    </p>
  </div>

</div>

<script>
)rawliteral";

  if (isFull)
  {
    html += R"rawliteral(
function beep() {
  let ctx = new (window.AudioContext || window.webkitAudioContext)();
  let osc = ctx.createOscillator();
  osc.type = "sine";
  osc.frequency.setValueAtTime(1000, ctx.currentTime);
  osc.connect(ctx.destination);
  osc.start();
  setTimeout(() => { osc.stop(); }, 200);
}

beep();
setTimeout(beep, 300);
)rawliteral";
  }

  html += R"rawliteral(
</script>

</body>
</html>
)rawliteral";

  server.send(200, "text/html", html);
}

void setup()
{
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(BUZZER, OUTPUT);

  Serial.begin(115200);

  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi Connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // Start server
  server.on("/", handleRoot);
  server.begin();

  Serial.println("Web server started!");
}

void loop()
{
  server.handleClient(); // IMPORTANT
}