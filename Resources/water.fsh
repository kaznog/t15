#ifdef GL_ES
//precision mediump float;
varying mediump vec2 v_texCoord1;
varying mediump vec2 v_texCoord2;
varying mediump vec2 v_texCoord3;
varying lowp vec4 v_fragmentColor;
#else
varying vec2 v_texCoord1;
varying vec2 v_texCoord2;
varying vec2 v_texCoord3;
varying vec4 v_fragmentColor;
#endif
//uniform sampler2D u_NoiseTexture;
//uniform sampler2D u_CausticTexture;

void main(){
	vec2 distortion = 2.0*texture2D(CC_Texture2, v_texCoord3).xy - 1.0;
	vec2 distortionOffset = distortion*0.05;
	
	gl_FragColor = v_fragmentColor*texture2D(CC_Texture0, v_texCoord2 + distortionOffset);
	gl_FragColor += 0.5 * texture2D(CC_Texture1, v_texCoord2 - distortionOffset);
}
