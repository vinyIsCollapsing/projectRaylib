#include "raylib.h"
#include <vector>
#include <cstdlib>
#include <ctime>   
#include <cmath>

struct Circle {
    Vector2 position;
    float radius;
    Vector2 speed;
    Color color;
};

bool CheckCircleCollision(Circle &a, Circle &b) {
    float distance = sqrt(pow(b.position.x - a.position.x, 2) + pow(b.position.y - a.position.y, 2));
    return distance <= (a.radius + b.radius);
}

void ResolveCollision(Circle &a, Circle &b) {
    Vector2 normal = { b.position.x - a.position.x, b.position.y - a.position.y };
    float distance = sqrt(normal.x * normal.x + normal.y * normal.y);

    if (distance == 0.0f) return;

    // Normaliza o vetor normal
    normal.x /= distance;
    normal.y /= distance;

    // Calcular a velocidade relativa
    Vector2 relativeVelocity = { b.speed.x - a.speed.x, b.speed.y - a.speed.y };

    // Calcular a velocidade ao longo da linha normal
    float velocityAlongNormal = relativeVelocity.x * normal.x + relativeVelocity.y * normal.y;

    // Se os círculos estão se afastando, não faz nada
    if (velocityAlongNormal > 0) return;

    // Calcular a restituição (bouncing coefficient, 1 para colisões perfeitamente elásticas)
    float restitution = 1.0f;

    // Calcular o impulso escalar
    float impulseScalar = -(1 + restitution) * velocityAlongNormal / (1 / a.radius + 1 / b.radius);

    // Calcular o vetor de impulso
    Vector2 impulse = { impulseScalar * normal.x, impulseScalar * normal.y };

    // Aplicar o impulso aos círculos
    a.speed.x -= impulse.x / a.radius;
    a.speed.y -= impulse.y / a.radius;
    b.speed.x += impulse.x / b.radius;
    b.speed.y += impulse.y / b.radius;

    // Separar os círculos para evitar sobreposição
    float overlap = (a.radius + b.radius) - distance;
    a.position.x -= normal.x * overlap / 2;
    a.position.y -= normal.y * overlap / 2;
    b.position.x += normal.x * overlap / 2;
    b.position.y += normal.y * overlap / 2;
}

int main() {
    // Inicializa a janela
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Exemplo Básico Raylib - Vários Círculos com Colisão e Atrito");

    // Inicializa o gerador de números aleatórios
    srand(time(NULL));

    // Define a quantidade de círculos
    const int numCircles = 20;

    // Define a gravidade
    const float gravity = 9.8f;

    // Define o coeficiente de atrito
    const float friction = 0.4f;

    // Cria um vetor de círculos
    std::vector<Circle> circles;

    // Inicializa os círculos com posições, raios e velocidades aleatórias
    for (int i = 0; i < numCircles; i++) {
        Circle circle;
        circle.position = { (float)(rand() % screenWidth), (float)(rand() % screenHeight) };
        circle.radius = (float)(20 + rand() % 30);
        circle.speed = { (float)(rand() % 5 - 2), 0.0f }; // Velocidade horizontal aleatória entre -2 e 2, velocidade vertical inicial 0
        circle.color = { (unsigned char)(rand() % 256), (unsigned char)(rand() % 256), (unsigned char)(rand() % 256), 255 };
        circles.push_back(circle);
    }

    // Define a taxa de frames por segundo
    SetTargetFPS(60);

    // Loop principal do jogo
    while (!WindowShouldClose()) {
        // Atualização
        for (auto &circle : circles) {
            // Aplicação da gravidade
            circle.speed.y += gravity;

            // Aplicação do atrito
            circle.speed.x *= friction;
            circle.speed.y *= friction;

            // Atualização da posição
            circle.position.y += circle.speed.y;
            circle.position.x += circle.speed.x;

            // Verificação de colisão com o chão
            if (circle.position.y + circle.radius >= screenHeight) {
                circle.position.y = screenHeight - circle.radius;
                circle.speed.y *= -1; // Inverte a direção vertical
            }

            // Verificação de colisão com as paredes laterais
            if (circle.position.x + circle.radius >= screenWidth) {
                circle.position.x = screenWidth - circle.radius;
                circle.speed.x *= -1; // Inverte a direção horizontal
            } else if (circle.position.x - circle.radius <= 0) {
                circle.position.x = circle.radius;
                circle.speed.x *= -1; // Inverte a direção horizontal
            }
        }

        // Detecção e resolução de colisão entre círculos
        for (size_t i = 0; i < circles.size(); i++) {
            for (size_t j = i + 1; j < circles.size(); j++) {
                if (CheckCircleCollision(circles[i], circles[j])) {
                    ResolveCollision(circles[i], circles[j]);
                }
            }
        }

        // Desenho
        BeginDrawing();
        ClearBackground(RAYWHITE);

        for (const auto &circle : circles) {
            DrawCircleV(circle.position, circle.radius, circle.color);
        }

        DrawText("Vários círculos com tamanhos diferentes, colisão e atrito", 10, 10, 20, DARKGRAY);

        EndDrawing();
    }

    // Fecha a janela e libera recursos
    CloseWindow();

    return 0;
}
