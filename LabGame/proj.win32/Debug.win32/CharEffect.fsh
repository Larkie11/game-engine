varying vec4 v_fragmentColor;
varying vec2 v_texCoord;
uniform vec2 loc;

void main()
{
	//Get pixel value at curr location from built in cocos2d uniform "CC_Texture0"
	vec4 v_orColor = v_fragmentColor * texture2D(CC_Texture0, v_texCoord);
	//v_texCoord is curre loc. Get distance to "loc" uniform we have defined
	float coeff = 1.0-1.5*distance(v_texCoord,loc);
	coeff = clamp(coeff, 0.0, 1.0);
	gl_FragColor = vec4(coeff * v_orColor.r, coeff * v_orColor.g, coeff * v_orColor.b, coeff * v_orColor.a);
}