
attribute vec4 a_position;
attribute vec4 a_color;
attribute vec2 a_texCoord;
#ifdef GL_ES
precision mediump float;
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
uniform vec2 u_NoiseTextureSize;
uniform vec2 resolution;

void main(){
	gl_Position = CC_PMatrix * a_position;
	v_fragmentColor = clamp(a_color, 0.0, 1.0);
	v_texCoord1 = a_texCoord;
	v_texCoord2 = a_texCoord;
	v_texCoord3 = a_texCoord;
	
//	vec2 distortionScroll = vec2(CC_Time[0], 0.0);
	vec2 distortionScroll = vec2(CC_Time.x * 3.0, 0.0);
	vec2 screen01 = (0.5*gl_Position.xy/gl_Position.w + 0.5);
	v_texCoord3 = screen01*resolution/u_NoiseTextureSize + distortionScroll;
}
