#version 330 core
layout (location = 0) in vec3 aPos;     // the position variable has attribute position 0
layout (location = 1) in vec3 aNormal;  // the normal variable has attribute position 1
layout (location = 2) in vec2 aUv;      // the Uv variable has attribute position 2
  
void main()
{
    gl_Position = vec4(aPos, 1.0);
}       