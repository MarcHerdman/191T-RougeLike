uniform sampler2D myTexture;
varying vec2 vTexCoord;

void main()
{
gl_FragColor = texture2D(myTexture, vTexCoord).bgra;
}