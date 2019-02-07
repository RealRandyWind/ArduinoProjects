/*
 Name:		CameraFocusRingControl.ino
 Created:	2/7/2019 3:07:04 AM
 Author:	RealRandyWind (Randy Wind)
 Email:		wind.randy@gmail.com
*/

#define P1 9
#define P2 10
#define P3 11
#define P4 12
#define JX A0

#define JREF 511
#define JNORM 32
#define JMIN 1

#define P1M 1
#define P2M 2
#define P3M 4
#define P4M 8
#define PALLM 15

#define ONE 1
#define CSHIFT(DIR, STATE) ((DIR) ? ((STATE) << ONE | (STATE) >> PALLM) : ((STATE) >> ONE | (STATE) << PALLM)) & PALLM
#define JNORMALIZE(VALUE)  JNORM - ((VALUE) % (JREF + 1)) * (JNORM / JREF) + JMIN

uint8_t state = ONE;

void setup() {
	pinMode(P1, OUTPUT);
	pinMode(P2, OUTPUT);
	pinMode(P3, OUTPUT);
	pinMode(P4, OUTPUT);
	pinMode(JX, INPUT);
}

void loop() {
	uint8_t vX = analogRead(JX);
	digitalWrite(P1, P1M & state);
	digitalWrite(P2, P2M & state);
	digitalWrite(P3, P3M & state);
	digitalWrite(P4, P4M & state);
	state = CSHIFT(JREF < vX, state);
	delay(JNORMALIZE(vX));
}
