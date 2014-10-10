varying vec3 vTexCoord;

void main()
{
    
    vTexCoord = normalize(vec3 (gl_Vertex.x, -gl_Vertex.y, -gl_Vertex.z));

    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}