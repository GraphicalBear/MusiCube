#include <Adafruit_NeoPixel.h>


#include "I2Cdev.h"

#include "MPU6050_6Axis_MotionApps20.h"
//#include "MPU6050.h" // not necessary if using MotionApps include file

// Arduino Wire library is required if I2Cdev I2CDEV_ARDUINO_WIRE implementation
// is used in I2Cdev.h
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    #include "Wire.h"
#endif

#define PIN 3
#define LED_COUNT 5

byte mode = 0;
byte gyro = 1;
byte accel[3] = { };
byte gyro_list[0] = { };
byte ledRed = 0;
byte ledGreen = 0;
byte ledBlue = 0;
byte motion = 0;



Adafruit_NeoPixel led_matrix = Adafruit_NeoPixel(LED_COUNT, PIN, NEO_GRB + NEO_KHZ800);

byte conv(float input) {
  return ((byte) ((input + 3000) / 120));
}

void sendDataPacket() {
  //Serial.println((250 + gyro));
  //Serial.println((0 + accel[0]));
  //Serial.println((100 + accel[1]));
  //Serial.println((200 + accel[2]));
  
  Serial.println(motion);
}


void updateGyroData(float y, float z) {

  if (y >= -45 && y <= 45 && z >= -90 && z <= -45) {
    gyro = 2;
  } else if (y >= -45 && y <= 45 && z >= 45 && z <= 90) {
    gyro = 3;
  } else if (y >= 45 && y <= 90 && z >= -45 && z <= 45) {
    gyro = 4;
  } else if (y <= 45 && y >= -90 && z >= -45 && z <= 45) {
    gyro = 5;
  } else if (y >= -45 && y <= 45 && z >= -45 && z <= 45) {
    gyro = 1;
  } else {
    gyro = 1;
  }
}

void clearLEDs()
{
  for (int i=0; i<LED_COUNT; i++)
  {
    led_matrix.setPixelColor(i, 0);
  }
  led_matrix.show();
}

void lowOn() {
  for (int i = 0; i < LED_COUNT; i++) {
    led_matrix.setPixelColor(i, 26, 122, 232);
  }
  led_matrix.show();
}

void solidColor(byte r, byte g, byte b) {
  for (int i = 0; i < LED_COUNT; i++) {
    led_matrix.setPixelColor(i, r, g, b);
  }
  led_matrix.show();
}

void beat()  {
   for (int i = 0; i < LED_COUNT; i++) {
    led_matrix.setPixelColor(i, 255, 128, 244);
  }
  led_matrix.show();
  delay(850);
  for (int i = 0; i < LED_COUNT; i++) {
    led_matrix.setPixelColor(i, 206, 128, 255);
  }
  led_matrix.show();
  delay(180);
  for (int i = 0; i < LED_COUNT; i++) {
    led_matrix.setPixelColor(i, 255, 128, 223);
  }
  led_matrix.show();
  delay(950);
  clearLEDs();
  led_matrix.show();
}

void oppBeat() {
   for (int i = 0; i < LED_COUNT; i++) {
    led_matrix.setPixelColor(i, 242, 255, 0);
  }
  led_matrix.show();
  delay(1030);
  for (int i = 0; i < LED_COUNT; i++) {
    led_matrix.setPixelColor(i, 255, 0, 0);
  }
  led_matrix.show();
  delay(950);
  clearLEDs();
  led_matrix.show();
}

void fullBeat() {
  for (int i = 0; i < LED_COUNT; i++) {
    led_matrix.setPixelColor(i, 0, 255, 255);
  }
  led_matrix.show();
  delay(1030);
  for (int i = 0; i < LED_COUNT; i++) {
    led_matrix.setPixelColor(i, 255, 0, 255);
  }
  led_matrix.show();
  delay(950);
  clearLEDs();
  led_matrix.show();
}

void pulse() {
  led_matrix.setPixelColor(0, 0, 255, 81);
  led_matrix.show();
  delay(250);
  led_matrix.setPixelColor(1, 0, 255, 208);
  led_matrix.show();
  delay(250);
  led_matrix.setPixelColor(2, 0, 195, 255);
  led_matrix.show();
  delay(250);
  led_matrix.setPixelColor(3, 0, 119, 255);
  led_matrix.show();
  delay(250);
  clearLEDs();
  led_matrix.show();
}


uint32_t rainbowOrder(byte position) 
{
  // 6 total zones of color change:
  if (position < 31)  // Red -> Yellow (Red = FF, blue = 0, green goes 00-FF)
  {
    return led_matrix.Color(0xFF, position * 8, 0);
  }
  else if (position < 63)  // Yellow -> Green (Green = FF, blue = 0, red goes FF->00)
  {
    position -= 31;
    return led_matrix.Color(0xFF - position * 8, 0xFF, 0);
  }
  else if (position < 95)  // Green->Aqua (Green = FF, red = 0, blue goes 00->FF)
  {
    position -= 63;
    return led_matrix.Color(0, 0xFF, position * 8);
  }
  else if (position < 127)  // Aqua->Blue (Blue = FF, red = 0, green goes FF->00)
  {
    position -= 95;
    return led_matrix.Color(0, 0xFF - position * 8, 0xFF);
  }
  else if (position < 159)  // Blue->Fuchsia (Blue = FF, green = 0, red goes 00->FF)
  {
    position -= 127;
    return led_matrix.Color(position * 8, 0, 0xFF);
  }
  else  //160 <position< 191   Fuchsia->Red (Red = FF, green = 0, blue goes FF->00)
  {
    position -= 159;
    return led_matrix.Color(0xFF, 0x00, 0xFF - position * 8);
  }
}

void rainbow(byte startPosition) 
{
  // Need to scale our rainbow. We want a variety of colors, even if there
  // are just 10 or so pixels.
  int rainbowScale = 192 / LED_COUNT;
  
  // Next we setup each pixel with the right color
  for (int i=0; i<LED_COUNT; i++)
  {
    // There are 192 total colors we can get out of the rainbowOrder function.
    // It'll return a color between red->orange->green->...->violet for 0-191.
    led_matrix.setPixelColor(i, rainbowOrder((rainbowScale * (i + startPosition)) % 192));
  }
  // Finally, actually turn the LEDs on:
  led_matrix.show();
}

void Still_Alive() {
  lowOn();
  delay(1000);
  for (int i = 0; i <= 29; i++) {
    pulse();
  }
  lowOn();
  delay(1000);
  for (int i = 0; i <= 7; i++) {
    beat();
  }
  for (int i = 0; i <= 18; i++) {
    oppBeat();
  }
  for (int i = 0; i <= 11; i++) {
    fullBeat();
  }
  for (int i = 0; i <= 16; i++) {
    pulse();
  }
  for (int i = 0; i <= 7; i++) {
    oppBeat();
  }
  for (int i = 0; i <= 7; i++) {
    fullBeat();
  }
  for (int i = 0; i <= 23; i++) {
    pulse();
  }
  lowOn();
  delay(3000);
  clearLEDs();
  led_matrix.show();
}

MPU6050 mpu;


#define OUTPUT_READABLE_YAWPITCHROLL
#define OUTPUT_READABLE_WORLDACCEL



#define LED_PIN 13 // (Arduino is 13, Teensy is 11, Teensy++ is 6)
bool blinkState = false;

// MPU control/status vars
bool dmpReady = false;  // set true if DMP init was successful
uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
uint16_t fifoCount;     // count of all bytes currently in FIFO
uint8_t fifoBuffer[64]; // FIFO storage buffer

// orientation/motion vars
Quaternion q;           // [w, x, y, z]         quaternion container
VectorInt16 aa;         // [x, y, z]            accel sensor measurements
VectorInt16 aaReal;     // [x, y, z]            gravity-free accel sensor measurements
VectorInt16 aaWorld;    // [x, y, z]            world-frame accel sensor measurements
VectorFloat gravity;    // [x, y, z]            gravity vector
float euler[3];         // [psi, theta, phi]    Euler angle container
float ypr[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector

// packet structure for InvenSense teapot demo
uint8_t teapotPacket[14] = { '$', 0x02, 0,0, 0,0, 0,0, 0,0, 0x00, 0x00, '\r', '\n' };



// ================================================================
// ===               INTERRUPT DETECTION ROUTINE                ===
// ================================================================

volatile bool mpuInterrupt = false;     // indicates whether MPU interrupt pin has gone high
void dmpDataReady() {
    mpuInterrupt = true;
}



// ================================================================
// ===                      INITIAL SETUP                       ===
// ================================================================

void setup() {
  

   led_matrix.begin();  // Call this to start up the LED strip.
     // This function, defined below, turns all LEDs off...
   led_matrix.show();   // ...but the LEDs don't actually update until you call this.

    solidColor(255, 255, 255);
    // join I2C bus (I2Cdev library doesn't do this automatically)
    #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
        Wire.begin();
        TWBR = 24; // 400kHz I2C clock (200kHz if CPU is 8MHz)
    #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
        Fastwire::setup(400, true);
    #endif

    // initialize serial communication
    // (115200 chosen because it is required for Teapot Demo output, but it's
    // really up to you depending on your project)
    Serial.begin(115200);
    while (!Serial); // wait for Leonardo enumeration, others continue immediately

    // NOTE: 8MHz or slower host processors, like the Teensy @ 3.3v or Ardunio
    // Pro Mini running at 3.3v, cannot handle this baud rate reliably due to
    // the baud timing being too misaligned with processor ticks. You must use
    // 38400 or slower in these cases, or use some kind of external separate
    // crystal solution for the UART timer.

    // initialize device
    Serial.println(F("Initializing I2C devices..."));
    mpu.initialize();

    // verify connection
    Serial.println(F("Testing device connections..."));
    Serial.println(mpu.testConnection() ? F("MPU6050 connection successful") : F("MPU6050 connection failed"));

    // wait for ready
    Serial.println(F("\nSend any character to begin DMP programming and demo: "));
    while (Serial.available() && Serial.read()); // empty buffer
    while (!Serial.available());                 // wait for data
    while (Serial.available() && Serial.read()); // empty buffer again

    // load and configure the DMP
    Serial.println(F("Initializing DMP..."));
    devStatus = mpu.dmpInitialize();

    // supply your own gyro offsets here, scaled for min sensitivity
    mpu.setXGyroOffset(34);
    mpu.setYGyroOffset(-8);
    mpu.setZGyroOffset(21);
    mpu.setZAccelOffset(1626); // 1688 factory default for my test chip

    // make sure it worked (returns 0 if so)
    if (devStatus == 0) {
        // turn on the DMP, now that it's ready
        Serial.println(F("Enabling DMP..."));
        mpu.setDMPEnabled(true);

        // enable Arduino interrupt detection
        Serial.println(F("Enabling interrupt detection (Arduino external interrupt 0)..."));
        attachInterrupt(0, dmpDataReady, RISING);
        mpuIntStatus = mpu.getIntStatus();

        // set our DMP Ready flag so the main loop() function knows it's okay to use it
        Serial.println(F("DMP ready! Waiting for first interrupt..."));
        dmpReady = true;

        // get expected DMP packet size for later comparison
        packetSize = mpu.dmpGetFIFOPacketSize();
    } else {
        // ERROR!
        // 1 = initial memory load failed
        // 2 = DMP configuration updates failed
        // (if it's going to break, usually the code will be 1)
        Serial.print(F("DMP Initialization failed (code "));
        Serial.print(devStatus);
        Serial.println(F(")"));
    }

    // configure LED for output
    pinMode(LED_PIN, OUTPUT);
}


// ================================================================
// ===                    MAIN PROGRAM LOOP                     ===
// ================================================================

void loop() {

    // if programming failed, don't try to do anything
    if (!dmpReady) return;

    // wait for MPU interrupt or extra packet(s) available
    while (!mpuInterrupt && fifoCount < packetSize) {



      while (mode == 0) {
        if (Serial.available()) {
          mode = Serial.read();
        }
      }
      
      if (mode == 1) {
        sendDataPacket();
         for (int i=0; i<LED_COUNT*10; i++) {
          rainbow(i);
          delay(100);
        } 
      }

      if (mode == 2) {
        Still_Alive();
        mode = 1;
      }
      
    
      mode = Serial.read();
      while (Serial.available()) {
        Serial.read();
      }
         
    }

    // reset interrupt flag and get INT_TATUS byte
    mpuInterrupt = false;
    mpuIntStatus = mpu.getIntStatus();

    // get current FIFO count
    fifoCount = mpu.getFIFOCount();

    // check for overflow (this should never happen unless our code is too inefficient)
    if ((mpuIntStatus & 0x10) || fifoCount == 1024) {
        // reset so we can continue cleanly
        mpu.resetFIFO();
        Serial.println(F("FIFO overflow!"));

    // otherwise, check for DMP data ready interrupt (this should happen frequently)
    } else if (mpuIntStatus & 0x02) {
        // wait for correct available data length, should be a VERY short wait
        while (fifoCount < packetSize) fifoCount = mpu.getFIFOCount();

        // read a packet from FIFO
        mpu.getFIFOBytes(fifoBuffer, packetSize);
        
        // track FIFO count here in case there is > 1 packet available
        // (this lets us immediately read more without waiting for an interrupt)
        fifoCount -= packetSize;



        #ifdef OUTPUT_READABLE_YAWPITCHROLL
            // display Euler angles in degrees
            mpu.dmpGetQuaternion(&q, fifoBuffer);
            mpu.dmpGetGravity(&gravity, &q);
            mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
            updateGyroData(((byte) (ypr[1] * 180/M_PI)), ((byte) (ypr[2] * 180/M_PI)));
            gyro_list[0] = abs(((byte) (ypr[0] * 180/M_PI) * 2.5));
            gyro_list[1] = abs(((byte) (ypr[1] * 180/M_PI) * 2.5));
            gyro_list[2] = abs(((byte) (ypr[2] * 180/M_PI) * 2.5));
        #endif
        
        #ifdef OUTPUT_READABLE_WORLDACCEL
            // display initial world-frame acceleration, adjusted to remove gravity
            // and rotated based on known orientation from quaternion
            mpu.dmpGetQuaternion(&q, fifoBuffer);
            mpu.dmpGetAccel(&aa, fifoBuffer);
            mpu.dmpGetGravity(&gravity, &q);
            mpu.dmpGetLinearAccel(&aaReal, &aa, &gravity);
            mpu.dmpGetLinearAccelInWorld(&aaWorld, &aaReal, &q);
            accel[0] = (byte) conv(aaWorld.x);
            accel[1] = (byte) conv(aaWorld.y);
            accel[2] = (byte) conv(aaWorld.z - 180);
           
        #endif

        // blink LED to indicate activity
        blinkState = !blinkState;
        digitalWrite(LED_PIN, blinkState);
    }
}
