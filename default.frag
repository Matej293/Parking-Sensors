#version 330 core

// Outputs colors in RGBA
out vec4 FragColor;

// Inputs the texture coordinates from the Vertex Shader
in vec2 texCoord;

// Gets the Texture Units from the main function
uniform sampler2D frontTex[4];
uniform sampler2D backTex[4];

// Inputs the selected texture index
uniform int frontTexIndex;
uniform int backTexIndex;

// Additional uniform to determine which texture set to use
uniform int activeTextureSet;

void main()
{
    if (activeTextureSet == 0)
    {
        FragColor = texture(frontTex[frontTexIndex], texCoord);
    }
    else
    {
        FragColor = texture(backTex[backTexIndex], texCoord);
    }
}
