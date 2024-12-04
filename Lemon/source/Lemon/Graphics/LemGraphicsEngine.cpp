#include <Lemon/Graphics/LemGraphicsEngine.h>
#include <glad/glad.h>

void LemGraphicsEngine::clear(const LemVec4& color)
{
    glClearColor(color.x, color.y, color.z, color.w);
    glClear(GL_COLOR_BUFFER_BIT);
}
