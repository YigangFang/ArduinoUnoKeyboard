/* Arduino USB Keyboard HID demo
 * Cut/Copy/Paste Keys
 */
 
#define KEY_LEFT_CTRL	0x01
#define KEY_LEFT_SHIFT	0x02
#define KEY_RIGHT_CTRL	0x10
#define KEY_RIGHT_SHIFT	0x20

// meaningful names for constants used in this sketch
const byte SC_SPACE = 0x2c;            const byte MOD_SHIFT = 0xf1;
const byte SC_ENTER = 0x28;            const byte MOD_ALT = 0xf2;
const byte SC_BCKSPC = 0x2a;           const byte MOD_CTRL = 0xf0;
const byte SC_TAB = 0x2b;              const byte SC_PERIOD = 0x37;
const byte SC_ESCAPE = 0x29;           const byte SC_COMMA = 0x36;
const byte SC_ESC = 0x29;              const byte SC_SEMI_AND_COLON = 0x33;
const byte SC_RIGHT_ARROW = 0xef;      const byte SC_SLASH_AND_QUESTION = 0x38;
const byte SC_LEFT_ARROW = 0x50;       const byte SC_VOL_UP = 0x80; //not working
const byte SC_DOWN_ARROW = 0x51;       const byte SC_VOL_DOWN = 0x81; //not working
const byte SC_UP_ARROW = 0x52;         const byte SC_MUTE = 0x7f; //not working
const byte SC_F1 = 0x3a;
const byte SC_F2 = 0x3b;
const byte SC_F3 = 0x3c;
const byte SC_F4 = 0x3d;
const byte SC_F5 = 0x3e;
const byte SC_F6 = 0x3f;
const byte SC_F7 = 0x40;
const byte SC_F8 = 0x41;
const byte SC_F9 = 0x42;
const byte SC_F10 = 0x43;
const byte SC_F11 = 0x44;
const byte SC_F12 = 0x45;
 
uint8_t buf[8] = { 
  0 }; 	/* Keyboard report buffer */
 
#define PIN_COPY 4
#define PIN_CUT 12
#define PIN_PASTE 2
 
int state = 1;
 
void setup() 
{
  Serial.begin(9600);
 
  pinMode(PIN_COPY, INPUT);
  pinMode(PIN_CUT, INPUT);
  pinMode(PIN_PASTE, INPUT);
  // Enable internal pull-ups
  digitalWrite(PIN_COPY, 1); 
  digitalWrite(PIN_CUT, 1);
  digitalWrite(PIN_PASTE, 1); 
 
  delay(200);
}
 
void loop() 
{
  state = digitalRead(PIN_CUT);
  if (state != 1) {
    
    buf[0] = KEY_LEFT_CTRL; 	// Ctrl
    buf[2] = 27;    // Letter X
    // buf[2] = 123;	  // Cut key: Less portable
    Serial.write(buf, 8);	// Ssend keypress
    releaseKey();
    
    /*buf[2] = SC_F2;	  // Volume up key
    Serial.write(buf, 8);	// Send keypress
    releaseKey();*/
  } 
 
  state = digitalRead(PIN_COPY);
  if (state != 1) {
    
    buf[0] = KEY_LEFT_CTRL; 	// Ctrl
    buf[2] = 6;    // Letter C
    // buf[2] = 124;	  // Copy key: Less portable
    Serial.write(buf, 8);	// Send keypress
    releaseKey();
    
    //buf[2] = SC_F1;	  // Volume up key
    //Serial.write(buf, 8);	// Send keypress
    //releaseKey();
  } 
 
  state = digitalRead(PIN_PASTE);
  if (state != 1) {
    buf[0] = KEY_LEFT_CTRL; 	// Ctrl
    buf[2] = 25;    // Letter V
    // buf[2] = 125;	  // Paste key: Less portable
    Serial.write(buf, 8);	// Send keypress
    releaseKey();
    
    //buf[2] = SC_F3;	  // Volume up key
    //Serial.write(buf, 8);	// Send keypress
    //releaseKey();
  } 
}
 
void releaseKey() 
{
  buf[0] = 0;
  buf[2] = 0;
  Serial.write(buf, 8);	// Release key  
  delay(500);
}
