in vec3 pos;        //输入顶点的属性
attribute vec2 texCoord;
varying vec2 outCoord;

void main(void)
{
    //顶点着色器的输出
    gl_Position = vec4(pos,1.0);
    outCoord = texCoord;
}
