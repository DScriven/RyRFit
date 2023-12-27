#version 430 core
layout (location=0) out vec4 color;

in vec3 tc;
in float alpha;
uniform sampler2DArray em_images;

void main(void)
{
    vec4 c = texture(em_images, tc);
    color = vec4(c.rgb, alpha);
}

