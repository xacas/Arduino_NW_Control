/*
 * SLIP_NW_Control HelloServer example.
 *
 * Based upon uIP SMTP example by Adam Dunkels <adam@sics.se>
 * SerialIP was ported to Arduino IDE by Adam Nielsen <malvineous@shikadi.net>
 * This code is wrriten by Masahiro Kusaka <masahiro906@gmail.com>
 */

#include <SerialIP.h>
#include <TimerOne.h>

// This is the SMTP server to connect to.  This default assumes an SMTP server
// on your PC.  Note this is a parameter list, so use commas not dots!
#define HELLO_SERVER 192,168,5,1

// IP and subnet that the Arduino will be using.  Commas again, not dots.
#define MY_IP 192,168,5,2
#define MY_SUBNET 255,255,255,0

// If you're using a real Internet server, the Arduino will need to route
// traffic via your PC, so set the PC's IP address here.  Note that this IP is
// for the PC end of the SLIP connection (not any other IP your PC might have.)
// Your PC will have to be configured to share its Internet connection over the
// SLIP interface for this to work.
//#define GATEWAY_IP 192,168,5,1

// Because some of the weird uIP declarations confuse the Arduino IDE, we
// need to manually declare a couple of functions.
void uip_callback(uip_tcp_appstate_t *s);

typedef struct {
  char input_buffer[16];
  char name[20];
} connection_data;

uip_ipaddr_t hello_server;
struct uip_conn *conn;
#define SET_IP(var, ip)  uip_ipaddr(var, ip)
bool flag=true;

void setup() {

  Serial.begin(115200);
  SerialIP.use_device(Serial);
  SerialIP.set_uip_callback(uip_callback);
  SerialIP.begin({MY_IP}, {MY_SUBNET});
  pinMode(12, OUTPUT);
  SET_IP(hello_server, HELLO_SERVER);
#ifdef GATEWAY_IP
  SerialIP.set_gateway({GATEWAY_IP});
#endif
  Timer1.initialize(500000);
  Timer1.attachInterrupt(control);

  Timer1.start();
}

void control() {
  
  if(!uip_connected()){
    conn = uip_connect(&hello_server, HTONS(8000));
    if (conn == NULL) {
      return;
    }
  }
}

void loop() {
  // Check the serial port and process any incoming data.
  SerialIP.tick();
}

void uip_callback(uip_tcp_appstate_t *s)
{

  if (uip_connected()) {
    connection_data *d = (connection_data *)malloc(sizeof(connection_data));
    s->user = d;
    PSOCK_INIT(&s->p, (uint8_t *)(d->input_buffer), sizeof(d->input_buffer));
  }

    // Call/resume our protosocket handler.
  handle_connection(s,(connection_data *)s->user);
  // If the connection has been closed, release the data we allocated earlier.
  if (uip_closed()) {
    if (s->user) free(s->user);
    s->user = NULL;
  }
}

int handle_connection(uip_tcp_appstate_t *s,connection_data *d)
{

  PSOCK_BEGIN(&s->p);

  // Send some text over the connection.
  PSOCK_SEND_STR(&s->p, "Hello. What is your name?\n");

  // Read some returned text into the input buffer we set in PSOCK_INIT.  Data
  // is read until a newline (\n) is received, or the input buffer gets filled
  // up.  (Which, at 16 chars by default, isn't hard!)
  PSOCK_READTO(&s->p, '\n');
  strncpy(d->name, d->input_buffer, sizeof(d->name));
  PSOCK_SEND_STR(&s->p, "Hello ");
  PSOCK_SEND_STR(&s->p, d->name);

  // Disconnect.
  PSOCK_CLOSE(&s->p);

  // All protosockets must end with this macro.  It closes the switch().
  PSOCK_END(&s->p);
}
