uniform vec3 fvEyePosition;

varying vec3 ViewDirection;
varying vec3 Normal;


varying vec3 vN;
varying vec3 v;

void main( void )
{
   gl_Position = ftransform();
   vec4 fvObjectPosition = gl_ModelViewMatrix * gl_Vertex;

   ViewDirection  = fvEyePosition - fvObjectPosition.xyz;

   v = vec3(gl_ModelViewMatrix * gl_Vertex);       
   vN = normalize(gl_NormalMatrix * gl_Normal);

   Normal         = gl_NormalMatrix * gl_Normal;
}