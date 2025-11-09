#include <raylib.h>

const int SCREEN_WIDTH = 960;
const int SCREEN_HEIGHT = 544;

int score = 0;

Rectangle player = {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 64, 64};
Rectangle ball = {SCREEN_WIDTH / 2 + 150, SCREEN_HEIGHT / 2, 32, 32};

int ballVelocityX = 300;
int ballVelocityY = 300;

void update(float deltaTime)
{
    if (ball.x < 0 || ball.x > SCREEN_WIDTH - ball.width)
    {
        ballVelocityX *= -1;
    }

    else if (ball.y < 0 || ball.y > SCREEN_HEIGHT - ball.height)
    {
        ballVelocityY *= -1;
    }

    if (CheckCollisionRecs(ball, player))
    {
        ballVelocityX *= -1;
        ballVelocityY *= -1;

        score++;
    }

    ball.x += ballVelocityX * deltaTime;
    ball.y += ballVelocityY * deltaTime;
}

int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Starter");
    SetTargetFPS(60);

    bool isGamePaused = false;

    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_SPACE))
        {
            isGamePaused = !isGamePaused;
        }

        Vector2 mousePosition = GetMousePosition();

        float deltaTime = GetFrameTime();

        if (!isGamePaused)
        {
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            {
                player.x = mousePosition.x;
                player.y = mousePosition.y;
            }

            update(deltaTime);
        }

        BeginDrawing();

        ClearBackground(BLACK);

        DrawText(TextFormat("%i", score), 230, 20, 80, WHITE);

        DrawRectangleRec(player, WHITE);

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            DrawRectangleRec(player, RED);
        }
        else
        {
            DrawRectangleRec(player, BLUE);
        }

        DrawRectangleRec(ball, YELLOW);

        if (isGamePaused)
        {
            DrawText("Game Paused", 220, 100, 80, WHITE);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}