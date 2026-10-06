#include "Grid.hpp"
#include <cmath>

void DrawGrid2D(Camera2D camera, int screenWidth, int screenHeight, float cellSize, float lineThickness, Color gridColor) {
    if (cellSize <= 0.0f) return;

    // 1. Determina os limites visíveis no mundo com base na câmera
    Vector2 topLeft = GetScreenToWorld2D({ 0.0f, 0.0f }, camera);
    Vector2 bottomRight = GetScreenToWorld2D({ (float)screenWidth, (float)screenHeight }, camera);

    float minX = (topLeft.x < bottomRight.x) ? topLeft.x : bottomRight.x;
    float maxX = (topLeft.x > bottomRight.x) ? topLeft.x : bottomRight.x;
    float minY = (topLeft.y < bottomRight.y) ? topLeft.y : bottomRight.y;
    float maxY = (topLeft.y > bottomRight.y) ? topLeft.y : bottomRight.y;

    // 2. Alinha os limites ao 'grid snap'
    float startX = std::floor(minX / cellSize) * cellSize;
    float endX   = std::ceil(maxX / cellSize) * cellSize;
    float startY = std::floor(minY / cellSize) * cellSize;
    float endY   = std::ceil(maxY / cellSize) * cellSize;

    // 3. Renderização das linhas
    if (lineThickness <= 1.0f) {
        for (float x = startX; x <= endX; x += cellSize) {
            DrawLineV({ x, minY }, { x, maxY }, gridColor);
        }
        for (float y = startY; y <= endY; y += cellSize) {
            DrawLineV({ minX, y }, { maxX, y }, gridColor);
        }
    } else {
        for (float x = startX; x <= endX; x += cellSize) {
            DrawLineEx({ x, minY }, { x, maxY }, lineThickness, gridColor);
        }
        for (float y = startY; y <= endY; y += cellSize) {
            DrawLineEx({ minX, y }, { maxX, y }, lineThickness, gridColor);
        }
    }
}
