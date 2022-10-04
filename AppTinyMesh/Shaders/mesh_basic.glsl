#version 150

#ifdef VERTEX_SHADER
in vec3 vertex;
in vec3 normal;
in vec3 color;

uniform mat4 ModelViewMatrix;
uniform mat4 ProjectionMatrix;
uniform mat4 TRSMatrix;

out vec3 fragNormal;
out vec3 fragVertex;
out vec3 fragColor;

void main(void)
{
	mat4 MVP      = ProjectionMatrix * ModelViewMatrix;
	gl_Position   = MVP * TRSMatrix * (vec4(vertex, 1.0)); 
	fragNormal	  = (TRSMatrix * vec4(normalize(normal), 0.0f)).xyz;
	fragVertex 	  = vertex;
	fragColor	  = color;
} 
#endif

#ifdef FRAGMENT_SHADER
in vec3 fragVertex;
in vec3 fragNormal;
in vec3 fragColor;

uniform int material;
uniform int shading;
uniform int useWireframe;
uniform vec3 viewDir;

out vec4 fragment;

bool ShouldDiscard()
{
	return false;
}

// Compute smooth diffuse color
// normal : Normal vector
// lighting : Lighting vector
float Diffuse(in vec3 normal, in vec3 lighting)
{
	// Modified diffuse lighting
	float d = 0.5 * (1.0 + dot(normal, lighting));
	return clamp(0.25 + (d * d), 0, 1);
}

vec4 GetBaseColor()
{
	// Normal
	if (material == 0)
	{
		return vec4(0.2 * (vec3(3.0) + 2.0 * fragNormal.xyz), 1.0);
	}
	// Color
	if (material == 1)
	{
		// normalize(-vec3(0.2, 0.8, 0.0))
		return vec4(fragColor.xyz * Diffuse(fragNormal, -viewDir), 1.0);
	}
}

void main()
{
	if (ShouldDiscard())
		discard;
	fragment = vec4(GetBaseColor().rgb, 1.0);
}

#endif
