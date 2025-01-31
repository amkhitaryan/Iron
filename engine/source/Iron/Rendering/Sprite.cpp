#include "Sprite.h"

void Sprite::SetAsSpriteSheet(int tileWidth, int tileHeight)
{
    IsSpriteSheet = true;
    TileWidth = tileWidth;
    TileHeight = tileHeight;
}

void Sprite::GetTexCoord(int tileIndex, glm::vec2* texCoords)
{
    if (!IsSpriteSheet)
    {
        texCoords[0] = glm::vec2(1.0f, 0.0f);
        texCoords[1] = glm::vec2(1.0f, 1.0f);
        texCoords[2] = glm::vec2(0.0f, 0.0f);
        texCoords[3] = glm::vec2(0.0f, 1.0f);

        return;
    }

    float tw = float(TileWidth) / float(Width);
    float th = float(TileHeight) / float(Height);
    int numPerRow = Width / TileWidth;
    float tx = (tileIndex % numPerRow) * tw;
    float ty = (tileIndex / numPerRow) * th;

    texCoords[0] = glm::vec2(tx + tw, ty);
    texCoords[1] = glm::vec2(tx + tw, ty + th);
    texCoords[2] = glm::vec2(tx, ty);
    texCoords[3] = glm::vec2(tx, ty + th);
}

int Sprite::TilesCount()
{
    return IsSpriteSheet ? Width / TileWidth * Height / TileHeight : 1;
}
