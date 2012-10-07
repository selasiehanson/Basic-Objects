uniform vec4 vColor;
out vec4 vFragColor;
void main(void)
{
    //gl_FragColor = vec4(1.0,1.0,0.0,1.0); //set color to yellow
    vFragColor = vColor ;// set color picked from code
}