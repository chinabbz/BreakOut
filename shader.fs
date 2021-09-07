#version 330 core

out vec4 FragColor;

in vec2 TexCoords;

uniform vec3 spriteColor;
uniform sampler2D texture1;

void main()
{
	 FragColor = texture(texture1, TexCoords)*vec4(spriteColor, 1.0);
}

////环境光强度
//float ambientStrenth = 0.1f;
//vec3 ambientColor = ambientStrenth * lightColor;
//
////计算直射光线的方向
//vec3 lightDir = normalize(lightPos - FragPos);
//
////漫反射
//vec3 norm = normalize(normal);
////对norm和lightDir向量进行点乘，来计算光对当前片段的实际的散射影响
//float diff = max(dot(norm, lightDir), 0.0);
//vec3 diffuse = diff * lightColor;
//
////镜面反射
//float specularStrength = 0.5;//镜面反射强度
//vec3 viewDir = normalize(viewPos - FragPos);
//vec3 reflectDir = reflect(-lightDir, norm);//reflect函数要求第一个向量是从光源指向片段位置的向量
////计算镜面亮度分量
//float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
//vec3 specular = specularStrength * spec * lightColor;