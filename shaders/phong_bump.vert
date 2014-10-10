varying vec3 vN; //normal
varying vec3 vT; //tangent
varying vec3 vB; //binormal
varying vec3 v;

void main(void)  
{     
	v = vec3(gl_ModelViewMatrix * gl_Vertex);       
	vN = normalize(gl_NormalMatrix * gl_Normal);
	   
	vec3 c1 = cross(gl_Normal, vec3(0.0, 0.0, 1.0)); 
	vec3 c2 = cross(gl_Normal, vec3(0.0, 1.0, 0.0)); 
	
	if(length(c1)>length(c2))
	{
		vT = c1;	
	}
	else
	{
		vT = c2;	
	}
	
	vT = normalize(vT);
	
	vB = cross(gl_Normal, vT); 
	vB = normalize(vB);
	
	gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;
	 
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;  
}
