out vec4 vFragColor;

uniform samplerCube cubeMap;

varying vec3 vVaryingTexCoord;

void main(void)
{
	 //gl_FragColor = texture(cubeMap, vVaryingTexCoord);
		vFragColor = texture (cubeMap, vVaryingTexCoord);
}
