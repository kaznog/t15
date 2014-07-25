#ifdef GL_ES
precision lowp float;
#endif

// Input
varying vec2 v_texCoord;
uniform sampler2D u_texture;
uniform bool u_enableGray;
uniform bool u_enableSepia;

// Gray
const float gRed = 0.298912;
const float gGreen = 0.586611;
const float gBule = 0.114478;
const vec3 gScale = vec3(gRed, gGreen, gBule);

// Sepia
const float sRed = 1.07;
const float sGreen = 0.74;
const float sBule = 0.43;
const vec3 sScale = vec3(sRed, sGreen, sBule);

void main() {
    vec4 baseColor = texture2D(u_texture, v_texCoord);
    float grayColor = dot(baseColor.rgb, gScale);
    
    // Changes Colors.
    if (u_enableSepia) {
        vec3 sepiaColor = vec3(grayColor) * sScale;
        baseColor = vec4(sepiaColor, 1.0);
    } else if (u_enableGray) {
        baseColor = vec4(vec3(grayColor), 1.0);
    }
    
    gl_FragColor = baseColor;
}