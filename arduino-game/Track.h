#ifndef TRACK_H
#define TRACK_H

#include <Arduino.h>
#include <FastLED.h>
#include "Button.h"
#include "PlayerController.h"

#define LED_STRIP_PIN D4
#define STRIP_LENGTH 50
#define STRIP_COUNT 1 // TODO: Support this being 2 (using logical strips)
#define MAX_LAPS 3
#define NUM_PLAYERS_POSSIBLE 4
#define TRAFFIC_START 7 // +1 from bottom, for aesthetics. Must be at least 6

extern CRGB TRAFFIC_RED;
extern CRGB TRAFFIC_YELLOW;
extern CRGB TRAFFIC_GREEN;

class Track {
  private:
    // Board state
    PlayerController* players[NUM_PLAYERS_POSSIBLE];
    CRGB leds[STRIP_LENGTH * STRIP_COUNT];
    unsigned long startTimeMs;
    bool inGame;
    Button* startBtn;
    unsigned long lightsStartMs;

    // Physics / game engine
    void updatePlayers();

    // Rendering
    void clearStrip();
    void drawPlayers();
    void render();
  
  public:
    // Constructors and functions
    Track(byte startPin, PlayerController* players[]);
    void update();
};

#endif