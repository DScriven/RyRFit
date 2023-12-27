#version 430 core
layout(location = 0) in int ImageNo;
layout(location = 1) in float Flip;
layout(location = 2) in float Transparency;
//uniform mat4 transform;

out vec3 tc;
out float alpha;

void main(void)
{
  const vec2 vertices[] =  vec2[](vec2(-0.5, -0.5),
                           vec2( 0.5, -0.5),
                           vec2(-0.5,  0.5),
                           vec2( 0.5,  0.5));
  alpha = Transparency;
  vec2 pos = vec2(2.0*vertices[gl_VertexID].x, 2.0*Flip*vertices[gl_VertexID].y);
  gl_Position = vec4(pos.x,pos.y,0.0,1.0); //transform*
  tc = vec3((vertices[gl_VertexID].xy + vec2(0.5)), ImageNo);
}
