#include <raylib.h>

int main()
{
    const int SCREEN_WIDTH = 960;
    const int SCREEN_HEIGHT = 544;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Starter");
    SetTargetFPS(60);

    Rectangle player = {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 64, 64};
    Rectangle ball = {SCREEN_WIDTH / 2 + 150, SCREEN_HEIGHT / 2, 32, 32};

    Vector2 ballVelocity = {300, 300};

    int score = 0;

    while (!WindowShouldClose())
    {
        Vector2 mousePosition = GetMousePosition();

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            player.x = mousePosition.x;
            player.y = mousePosition.y;
        }

        if (ball.x < 0 || ball.x > SCREEN_WIDTH - ball.width)
        {
            ballVelocity.x *= -1;
        }

        else if (ball.y < 0 || ball.y > SCREEN_HEIGHT - ball.height)
        {
            ballVelocity.y *= -1;
        }

        if (CheckCollisionRecs(ball, player))
        {
            ballVelocity.x *= -1;
            ballVelocity.y *= -1;

            score++;
        }

        float deltaTime = GetFrameTime();

        ball.x += ballVelocity.x * deltaTime;
        ball.y += ballVelocity.y * deltaTime;

        BeginDrawing();

        ClearBackground(BLACK);

        DrawText(TextFormat("%i", score), SCREEN_WIDTH / 2, 20, 80, WHITE);

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

        EndDrawing();
    }

    CloseWindow();
    return 0;
}