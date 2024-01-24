#include "main.h"

#include <stdlib.h>
#include <stdio.h>
#include <raylib.h>
#include <raymath.h>

#define FPS 1
#define DEPTH 7

typedef struct Turtle {
    Vector2 position;
    float angle;
    float lineLength;
    float hue;
} Turtle;

Turtle turtle = {{0, 0}, 0, 0, 0};
int two = 2;

int main(int argc, char **argv) {
    InitWindow(1000, 1000, "hilbilly curves");
    SetTargetFPS(FPS);

    //turtle.lineLength = GetScreenWidth() / pow(DEPTH, GetScreenWidth() / 400.0);
    turtle.lineLength = atof(argv[2]);

    while (!WindowShouldClose()) {
        turtle.position = (Vector2) {500, 500};
        turtle.hue = 0.0;
        two = 2;

        BeginDrawing();
        ClearBackground(BLACK);
        Hilbert(DEPTH, -atof(argv[1]));
        EndDrawing();
    }

    CloseWindow();
    return 0;
}


void Hilbert(int level, int angle) {
    if (level <= 0) {
        return;
    }

    turtle.angle -= angle;
    Hilbert(level - 1, -angle);
    Forward();
    turtle.angle += angle;

    Hilbert(level - 1, angle);
    Forward();
    Hilbert(level - 1, angle);

    turtle.angle += angle;
    Forward();
    Hilbert(level - 1, -angle);
    turtle.angle -= angle;
}

void Forward() {
    turtle.hue += (350 / (pow(4, DEPTH) - 1)) * two;
    if (turtle.hue >= 350) {
        two *= -1;
    }
    
    Color color = ColorFromHSV(turtle.hue, 1, 1);
    Vector2 newPos = Vector2Add(turtle.position, Vector2Rotate((Vector2) {0, -turtle.lineLength}, turtle.angle * DEG2RAD));
    DrawLineV(turtle.position, newPos, color);
    turtle.position = newPos;
}