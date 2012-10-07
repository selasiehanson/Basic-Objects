

smooth in vec2 vTex;
uniform sampler2D textureUnit0;
out vec4 vFragColor;

void main(void) 
{ 
	//vFragColor =  vec4(1.0,1.0,0.0,1.0);
	vFragColor = texture(textureUnit0, vTex); 
}