varying vec3 vN;
varying vec3 v;
varying vec3 vTexCoord;



void main(void)  
{     
   v = vec3(gl_ModelViewMatrix * gl_Vertex);       
   vN = normalize(gl_NormalMatrix * gl_Normal);
   vec3 vEyeNormal = gl_NormalMatrix * gl_Normal;
   
   vec4 vVert4 = gl_ModelViewMatrix * gl_Vertex;
   vec3 vEyeVertex = normalize (vVert4.xyz);
   
   vec4 vCoords =  vec4(reflect (vEyeVertex, vEyeNormal), 1.0);
   
   vTexCoord.xyz = normalize(-vCoords.xyz);
   
   
   gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;  
}   

