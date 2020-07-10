
#include "Encoder.h"

volatile int8_t enc_delta;          // -128 ... 127
static int8_t last;

void encoder_isr(){     // 1ms for manual movement
  int8_t new, diff;

  new = 0;
  if( PHASE_A ) new = 3;
  if( PHASE_B ) new ^= 1;          // convert gray to binary
  diff = last - new;               // difference last - new
  if( diff & 1 ) {                 // bit 0 = value (1)
    last = new;                    // store new as next last
    enc_delta += (diff & 2) - 1;   // bit 1 = direction (+/-)
  }
}

void encode_init( void ){
    Timer2_init(16, encoder_isr); // Init timer
  int8_t new;

  new = 0;
  if( PHASE_A ) new = 3;
  if( PHASE_B ) new ^= 1;       // convert gray to binary
  last = new;                   // power on state
  enc_delta = 0;
}


int8_t encode_read1( void )         // read single step encoders
{
  int8_t val;

  cli();
  val = enc_delta;
  enc_delta = 0;
  sei();
  return val;                   // counts since last call
}


int8_t encode_read2( void )         // read two step encoders
{
  int8_t val;

  cli();
  val = enc_delta;
  enc_delta = val & 1;
  sei();
  return val >> 1;
}


int8_t encode_read4( void )         // read four step encoders
{
  int8_t val;

  cli();
  val = enc_delta;
  enc_delta = val & 3;
  sei();
  return val >> 2;
}


int loop( void )
{
  int32_t val = 0;

  encode_init();
  sei();

  for(;;){
    val += encode_read1();          // read a single step encoder
    PORTB = val;
  }
}
