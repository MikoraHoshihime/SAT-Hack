#include "mapping.h"
#include "turn_right.h"
#include "get_distance.h"

// --- Pin Definitions ---
#define Trig A4 
#define Echo A5

// --- Movement Variables ---
int MotSpeed1 = 200; 
int MotSpeed2 = 200;
int Speed_adjustment = 120;
int stop_bit = 0;
float distance = 0.0;
int set_dis = 30;

// --- Grid Component Constants ---
const int8_t WALL = -1;
const int8_t UNKNOWN = -2;
const int8_t EMPTY = 0;

// --- Global Variable Definitions (NO extern here) ---
int8_t grid[100][200]; 
double start_pos[2] = {50.0, 2.0};
double end_pos[2] = {50.0, 150.0};
double end_tolerance = 10.0;
double sat_pos[2] = {50.0, 25.0}; 
double sat_dir = 0.0; 

// --- Combined Setup Function ---
void setup() {
    // 1. Start Communications
    Serial.begin(115200);

    // 2. Configure Hardware Pins
    pinMode(5, OUTPUT);
    pinMode(6, OUTPUT);
    pinMode(9, OUTPUT);
    pinMode(10, OUTPUT);
    pinMode(Trig, OUTPUT);   
    pinMode(Echo, INPUT); 

    // 3. Initialize Grid Memory
    // Note: This loop might take a moment if the grid is 400x700
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 200; j++) {
            grid[i][j] = UNKNOWN;
        }
    }
    
    Serial.println("SatHack System Initialized");
}

void loop() {
    // Call your mapping() function here later
    mapping()

}