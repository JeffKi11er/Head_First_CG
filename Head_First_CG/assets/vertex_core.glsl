#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
out vec3 ourColor;

uniform mat4 transform; //set in code 

void main(){
	gl_Position = vec4(aPos, 1.0);
	ourColor = aColor;
}
/*out vec4 color;

void main(){
	gl_Position = vec4(aPos, 1.0);*/
	/*if (aPos.x < 0.0){
		color = vec4(1.0, 0.0, 0.0, 1.0);
	}else if (aPos.x == 0){
		color = vec4(0.0, 1.0, 0.0, 1.0);
	}else {
		//color = vec4(0.0, 0.0, 1.0, 1.0);
		color = vec4(vec2(0.0), vec2(1.0));
	}*/
/*}*/