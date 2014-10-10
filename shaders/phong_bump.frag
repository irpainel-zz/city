varying vec3 vN; //normal
varying vec3 vT; //tangent
varying vec3 vB; //binormal
varying vec3 v; 
#define MAX_LIGHTS 4
uniform sampler2D tex;

void main (void) 
{ 
	vec3 N = normalize( texture2D(tex,gl_TexCoord[0].st).rgb * 2.0 - 1.0);

	vec4 finalColor = vec4(0.0, 0.0, 0.0, 0.0);
   
	for (int i=0;i<MAX_LIGHTS;i++)
	{
		float insideSpot = 1.0;
		vec3 L; 
		vec3 E; 
   
		vec3 tmpVec = normalize(gl_LightSource[i].position.xyz - v);
		L.x = dot(tmpVec, vT);
		L.y = dot(tmpVec, vB);
		L.z = dot(tmpVec, vN);

		tmpVec = normalize(-v);
		E.x = dot(tmpVec, vT);
		E.y = dot(tmpVec, vB);
		E.z = dot(tmpVec, vN);

		vec3 R = normalize(reflect(-L,N)); 
   
		//calculate Ambient Term: 
		vec4 Iamb = gl_LightSource[i].ambient * gl_FrontMaterial.ambient; 


		if (gl_LightSource[i].spotCutoff <= 90.0)
		{
			float clampedCosine = max(0.0, dot(-L, normalize(gl_LightSource[i].spotDirection)));
			if (clampedCosine < cos(radians(gl_LightSource[i].spotCutoff))) // outside of spotlight cone?
			{
				insideSpot = 0.0;
			}
		}
					
		//calculate Diffuse Term: 
		vec4 Idiff = gl_LightSource[i].diffuse * gl_FrontMaterial.diffuse* max(dot(N,L), 0.0);
		Idiff = insideSpot * clamp(Idiff, 0.0, 1.0); 
   
   
		float specular = pow(max(dot(R,E),0.0), gl_FrontMaterial.shininess );
		vec4 Ispec = gl_LightSource[0].specular * gl_FrontMaterial.specular * specular;
		Ispec = insideSpot * clamp(Ispec, 0.0, 1.0); 
		
		finalColor += Iamb + Idiff + Ispec;
	}
   
   // write Total Color: 
   gl_FragColor = gl_FrontLightModelProduct.sceneColor + finalColor; 
}