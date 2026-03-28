String input = "";

#define LED_PIN 13   // Built-in LED (can change if needed)

void setup() {
  Serial.begin(9600);   // UART from ESP32
  pinMode(LED_PIN, OUTPUT);

  Serial.println("Arduino Ready ✅");
}

void loop() {
  while (Serial.available()) {
    char c = Serial.read();

    if (c == '\n') {
      input.trim();

      Serial.print("Received from ESP32: ");
      Serial.println(input);

      processCommand(input);   // 🔥 Process command

      input = "";
    } else {
      input += c;
    }
  }
}

// 🔥 Command processing logic
void processCommand(String cmd) {

  cmd.toUpperCase();

  if (cmd == "LED ON") {
    digitalWrite(LED_PIN, HIGH);
    Serial.println("LED turned ON ✅");
  }
  else if (cmd == "LED OFF") {
    digitalWrite(LED_PIN, LOW);
    Serial.println("LED turned OFF ❌");
  }
  else if (cmd.startsWith("MOTOR")) {
    Serial.println("Simulating motor movement...");

    // 🔁 Simulate motor using LED blink
    for (int i = 0; i < 5; i++) {
      digitalWrite(LED_PIN, HIGH);
      delay(200);
      digitalWrite(LED_PIN, LOW);
      delay(200);
    }

    Serial.println("Motor simulation complete ⚙️");
  }
  else {
    Serial.println("Unknown command ❓");
  }
}