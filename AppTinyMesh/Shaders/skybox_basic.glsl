#version 150

#ifdef VERTEX_SHADER
void main(void)
{
    vec4 vertices[4] = vec4[4](vec4(-1.0, -1.0, 1.0, 1.0),
                               vec4( 1.0, -1.0, 1.0, 1.0),
                               vec4(-1.0,  1.0, 1.0, 1.0),
                               vec4( 1.0,  1.0, 1.0, 1.0));
    vec4 pos = vertices[gl_VertexID];

    gl_Position = pos;
}
#endif

#ifdef FRAGMENT_SHADER
uniform vec3 CamPos;
uniform vec3 CamLookAt;
uniform vec3 CamUp;
uniform vec2 iResolution;

out vec4 color;

void main(void)
{
	color = vec4(222.0/255.0, 248.0/255.0, 1.0, 1.0);
}
#endif
