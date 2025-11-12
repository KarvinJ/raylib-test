#include <raylib.h>

int main()
{
    const int SCREEN_WIDTH = 960;
    const int SCREEN_HEIGHT = 544;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Raylib-Web");
    SetTargetFPS(60);
    InitAudioDevice();

    Texture2D texture = LoadTexture("assets/img/alien.png");
    Rectangle rectangle = {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, (float)texture.width, (float)texture.height};

    Rectangle ball = {SCREEN_WIDTH / 2 + 150, SCREEN_HEIGHT / 2, 32, 32};
    Vector2 ballVelocity = {300, 300};

    Sound hitSound = LoadSound("assets/sounds/okay.wav");

    Music music = LoadMusicStream("assets/music/pixel3.mp3");
    music.looping = true;
    PlayMusicStream(music);

    int score = 0;

    while (!WindowShouldClose())
    {
        UpdateMusicStream(music);

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            Vector2 mousePosition = GetMousePosition();

            rectangle.x = mousePosition.x;
            rectangle.y = mousePosition.y;
        }

        if (ball.x < 0 || ball.x > SCREEN_WIDTH - ball.width)
        {
            ballVelocity.x *= -1;
        }

        else if (ball.y < 0 || ball.y > SCREEN_HEIGHT - ball.height)
        {
            ballVelocity.y *= -1;
        }

        if (CheckCollisionRecs(ball, rectangle))
        {
            ballVelocity.x *= -1;
            ballVelocity.y *= -1;

            score++;

            PlaySound(hitSound);
        }

        float deltaTime = GetFrameTime();

        ball.x += ballVelocity.x * deltaTime;
        ball.y += ballVelocity.y * deltaTime;

        BeginDrawing();

        ClearBackground(BLACK);

        DrawText(TextFormat("%i", score), SCREEN_WIDTH / 2, 20, 80, WHITE);

        DrawTexture(texture, rectangle.x, rectangle.y, WHITE);

        DrawRectangleRec(ball, YELLOW);

        EndDrawing();
    }

    UnloadTexture(texture);
    UnloadSound(hitSound);
    UnloadMusicStream(music);
    CloseAudioDevice();
    CloseWindow();
    return 0;
}