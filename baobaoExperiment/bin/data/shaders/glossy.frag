uniform samplerCube cubeMap;

varying vec3 ViewDirection;
varying vec3 Normal;

const float mother_pearl_brightness = 1.5;

varying vec3 vN;
varying vec3 v;
#define MAX_LIGHTS 3

#define MOTHER_PEARL
#define TOON_SHADE

void main( void )
{
   vec3  fvNormal         = normalize(Normal);
   vec3  fvViewDirection  = normalize(ViewDirection);
   vec3  fvReflection     = normalize(reflect(fvViewDirection, fvNormal)); 

   vec3 N = normalize(vN);
    vec4 finalColor = vec4(0.0, 0.0, 0.0, 0.0);
    
    for (int i=0;i<MAX_LIGHTS;i++)
    {
        vec3 L = normalize(gl_LightSource[i].position.xyz - v);
        vec3 E = normalize(-v); // we are in Eye Coordinates, so EyePos is (0,0,0)
        vec3 R = normalize(-reflect(L,N));
        
        //calculate Ambient Term:
        vec4 Iamb = gl_FrontLightProduct[i].ambient;
        //calculate Diffuse Term:
        vec4 Idiff = gl_FrontLightProduct[i].diffuse * max(dot(N,L), 0.0);
        Idiff = clamp(Idiff, 0.0, 1.0);
        
        // calculate Specular Term:
        vec4 Ispec = gl_FrontLightProduct[i].specular
        * pow(max(dot(R,E),0.0),0.3*gl_FrontMaterial.shininess);
        Ispec = clamp(Ispec, 0.0, 1.0);
        
        finalColor += Iamb + Idiff + Ispec;
        
    }

#ifdef TOON_SHADE
  float intensity = dot(fvViewDirection,N);
  if (intensity > 0.95)
    finalColor = finalColor*vec4(0.95, 0.95, 0.95, 1.0);
  else if (intensity > 0.5)
    finalColor = finalColor*vec4(0.5, 0.5, 0.5, 1.0);
  else if (intensity > 0.25)
    finalColor = finalColor*vec4(0.25, 0.25, 0.25, 1.0);
  else
    finalColor = finalColor*vec4(0.1, 0.1, 0.1, 1.0);
  gl_FragColor = finalColor;
#endif
#ifdef MOTHER_PEARL
   float view_dot_normal = max(dot(fvNormal, fvViewDirection), 0.0);
   float view_dot_normal_inverse = 1.0 - view_dot_normal;

   gl_FragColor = textureCube(cubeMap, fvReflection) * view_dot_normal;
	float dotnormal = (1.0 - view_dot_normal);
   gl_FragColor.r += mother_pearl_brightness * textureCube(cubeMap, fvReflection + vec3(0.1, 0.0, 0.0) * view_dot_normal_inverse).r * dotnormal;
   gl_FragColor.g += mother_pearl_brightness * textureCube(cubeMap, fvReflection + vec3(0.0, 0.1, 0.0) * view_dot_normal_inverse).g * dotnormal;
   gl_FragColor.b += mother_pearl_brightness * textureCube(cubeMap, fvReflection + vec3(0.0, 0.0, 0.1) * view_dot_normal_inverse).b * dotnormal;
   gl_FragColor *= finalColor;
#else
   gl_FragColor = textureCube(cubeMap, fvReflection);// * finalColor;
#endif

}