#version 330

out vec4 frag_color;

void main() {
    float x = gl_FragCoord.y / 700.0f;
    frag_color = mix(vec4(0.3f, 0.5f, 0.8f, 1.0f), vec4(1.0f, 1.0f, 1.0f, 1.0f), x);
}