uniform samplerCube cubemap;
varying vec3 vTexCoord;

void main()
{
    gl_FragColor = textureCube(cubemap, vTexCoord);
}