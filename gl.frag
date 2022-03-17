uniform sampler2D texture;
varying vec2 outCoord;
void main(void)
{
    //片段着色器的输出
    gl_FragColor = texture2D(texture,outCoord);
}
