

smooth in vec2 vTex;
uniform sampler2D textureUnit0;
out vec4 vFragColor;

void main(void) 
{ 
	//vFragColor =  vec4(1.0,1.0,0.0,1.0);
	vFragColor = texture(textureUnit0, vTex); 
}


//#version 300
//in vec2 vTex;
//
//uniform sampler2D textureUnit0;
//
//out vec4 fragColor;
//
//void main(void) 
//{ 
//	//fragColor =  vec4(1.0,1.0,0.0,1.0);
//	fragColor = texture(textureUnit0, vTex); 
//}