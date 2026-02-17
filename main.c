#include "raylib.h"
#include <stdlib.h>

int main(void)
{
    const int WIDTH = 960, HEIGHT = 640;

    InitWindow(WIDTH, HEIGHT, "WallBall");
    SetTargetFPS(60);

    int ballX = 40;
    int ballY = 80;
    int ballVx = 5;
    int ballVy = 5;
    int ballR = 10;

    int racketX = WIDTH / 2;
    int racketY = HEIGHT - 50;
    int racketW = 120;
    int racketH = 12;

    typedef enum { TITLE, PLAY, OVER } Scene;
    Scene scene = TITLE;
    int timer = 0;
    int score = 0;
    int highScore = 1000;
    int dx, dy;

    Texture2D imgBg = LoadTexture("image/bg.png");
    Texture2D imgBall = LoadTexture("image/monsterball.png");

    /* InitAudioDevice();
    Sound bgm = LoadSound("sound/bgm.mp3");
    Sound jin = LoadSound("sound/gameover.mp3");
    Sound se  = LoadSound("sound/hit.mp3");
    SetSoundVolume(bgm, 0.5f);
    SetSoundVolume(jin, 0.5f); */

    while (!WindowShouldClose())
    {
        timer++;

        switch (scene)
        {
        case TITLE:
            if (IsKeyDown(KEY_SPACE))
            {
                ballX = 40;
                ballY = 80;
                ballVx = 5;
                ballVy = 5;
                racketX = WIDTH / 2;
                racketY = HEIGHT - 50;
                score = 0;
                scene = PLAY;
                /* PlaySound(bgm); */
            }
            break;

        case PLAY:
            ballX = ballX + ballVx;
            if (ballX < ballR && ballVx < 0) ballVx = -ballVx;
            if (ballX > WIDTH - ballR && ballVx > 0) ballVx = -ballVx;
            ballY = ballY + ballVy;
            if (ballY < ballR && ballVy < 0) ballVy = -ballVy;
            if (ballY > HEIGHT)
            {
                scene = OVER;
                timer = 0;
                /* StopSound(bgm);
                PlaySound(jin); */
                break;
            }

            if (IsKeyDown(KEY_LEFT))
            {
                racketX = racketX - 10;
                if (racketX < racketW / 2) racketX = racketW / 2;
            }
            if (IsKeyDown(KEY_RIGHT))
            {
                racketX = racketX + 10;
                if (racketX > WIDTH - racketW / 2) racketX = WIDTH - racketW / 2;
            }

            dx = ballX - racketX;
            dy = ballY - racketY;
            if (-racketW / 2 - 10 < dx && dx < racketW / 2 + 10 && -20 < dy && dy < 0)
            {
                ballVy = -5 - rand() % 5;
                score += 100;
                if (score > highScore) highScore = score;
                /* PlaySound(se); */
            }
            break;

        case OVER:
            if (timer > 60 * 5) scene = TITLE;
            break;
        }

        BeginDrawing();
        ClearBackground(BLACK);
        DrawTexture(imgBg, 0, 0, WHITE);

        switch (scene)
        {
        case TITLE:
        {
            const char *title = "WallBall";
            DrawText(title, WIDTH / 2 - MeasureText(title, 50) / 2, HEIGHT / 3, 50, GREEN);
            if (timer % 60 < 30)
            {
                const char *msg = "Press SPACE to start.";
                DrawText(msg, WIDTH / 2 - MeasureText(msg, 30) / 2, HEIGHT * 2 / 3, 30, (Color){0, 255, 255, 255});
            }
            break;
        }

        case PLAY:
        {
            Rectangle src = {0, 0, (float)imgBall.width, (float)imgBall.height};
            Rectangle dst = {(float)(ballX - ballR), (float)(ballY - ballR), (float)(ballR * 2), (float)(ballR * 2)};
            DrawTexturePro(imgBall, src, dst, (Vector2){0, 0}, 0, WHITE);

            DrawRectangle(racketX - racketW / 2 - 2, racketY - racketH / 2 - 2,
                          racketW + 2, racketH + 2, (Color){64, 192, 255, 255});
            DrawRectangle(racketX - racketW / 2, racketY - racketH / 2,
                          racketW + 2, racketH + 2, (Color){32, 64, 128, 255});
            break;
        }

        case OVER:
        {
            const char *msg = "GAME OVER";
            DrawText(msg, WIDTH / 2 - MeasureText(msg, 40) / 2, HEIGHT / 3, 40, RED);
            break;
        }
        }

        DrawText(TextFormat("SCORE %d", score), 10, 10, 30, WHITE);
        DrawText(TextFormat("HI-SC %d", highScore), WIDTH - 200, 10, 30, YELLOW);

        EndDrawing();
    }

    UnloadTexture(imgBg);
    UnloadTexture(imgBall);
    /* UnloadSound(bgm);
    UnloadSound(jin);
    UnloadSound(se);
    CloseAudioDevice(); */
    CloseWindow();
    return 0;
}
