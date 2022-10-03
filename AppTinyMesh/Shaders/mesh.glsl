#version 150

#ifdef VERTEX_SHADER
in vec3 vertex;
in vec3 normal;
in vec3 color;

uniform mat4 ModelViewMatrix;
uniform mat4 ProjectionMatrix;
uniform mat4 TRSMatrix;

out vec3 geomNormal;
out vec3 geomVertex;
out vec3 geomColor;

void main(void)
{
	mat4 MVP      = ProjectionMatrix * ModelViewMatrix;
	gl_Position   = MVP * TRSMatrix * (vec4(vertex, 1.0)); 
	geomNormal	  = (TRSMatrix * vec4(normalize(normal), 0.0f)).xyz;
	geomVertex 	  = vertex;
	geomColor	  = color;
} 
#endif

#ifdef GEOMETRY_SHADER
layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

uniform vec2 WIN_SCALE;

in vec3 geomVertex[];
in vec3 geomNormal[];
in vec3 geomColor[];

out vec3 fragVertex;
out vec3 fragNormal;
out vec3 fragColor;
out vec3 dist;
out float ratio;

void main()
{	
	vec2 p0 = WIN_SCALE * gl_in[0].gl_Position.xy / gl_in[0].gl_Position.w;
	vec2 p1 = WIN_SCALE * gl_in[1].gl_Position.xy / gl_in[1].gl_Position.w;
	vec2 p2 = WIN_SCALE * gl_in[2].gl_Position.xy / gl_in[2].gl_Position.w;

	vec2 v0 = p2 - p1;
	vec2 v1 = p2 - p0;
	vec2 v2 = p1 - p0;

	float area = abs(v1.x * v2.y - v1.y * v2.x);

	// Triangle aspect ratio
	float ab = length(geomVertex[0] - geomVertex[1]);
	float bc = length(geomVertex[1] - geomVertex[2]);
	float ca = length(geomVertex[2] - geomVertex[0]);
	float s = 0.5f * (ab + bc + ca);
	float u = (s - ab) * (s - bc) * (s - ca);
	ratio = 8.0f * u / (ab * bc * ca);

	dist = vec3(area / length(v0), 0, 0);
	gl_Position = gl_in[0].gl_Position;
	fragVertex = geomVertex[0]; fragNormal = geomNormal[0]; fragColor = geomColor[0];
	EmitVertex();

	dist = vec3(0, area / length(v1), 0);
	gl_Position = gl_in[1].gl_Position;
	fragVertex = geomVertex[1]; fragNormal = geomNormal[1]; fragColor = geomColor[1];
	EmitVertex();

	dist = vec3(0, 0, area / length(v2));
	gl_Position = gl_in[2].gl_Position;
	fragVertex = geomVertex[2]; fragNormal = geomNormal[2]; fragColor = geomColor[2];
	EmitVertex();

	EndPrimitive();
}  

#endif

#ifdef FRAGMENT_SHADER
in vec3 fragVertex;
in vec3 fragNormal;
in vec3 fragColor;
in vec3 dist;
in float ratio;

uniform int material;
uniform int shading;
uniform int useWireframe;
uniform vec3 viewDir;

out vec4 fragment;

/*!
\brief Determine if a fragment should be discarded based on the shading mode.
This allows for controlling the render primitive (triangles, lines and points) in the fragment shader.
*/
bool ShouldDiscard()
{
	if (shading == 0) 	// Triangles
		return false;
	else				// Lines
		return (min(dist[0], min(dist[1], dist[2])) > 1);	
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
	
	vec4 c = GetBaseColor();
	if (useWireframe == 1)
	{
		float d = min(dist[0], min(dist[1], dist[2]));
		float I = exp2(-7.0 * d * d);
		c 		= vec4((I * 0.85) * c.xyz + (1.0 - I) * c.xyz, 1.0);
	}
	fragment = vec4(c.rgb, 1.0);
}

#endif
