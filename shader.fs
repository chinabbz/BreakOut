#version 330 core

out vec4 FragColor;

in vec2 TexCoords;

uniform vec3 spriteColor;
uniform sampler2D texture1;

void main()
{
	 FragColor = texture(texture1, TexCoords)*vec4(spriteColor, 1.0);
}

////������ǿ��
//float ambientStrenth = 0.1f;
//vec3 ambientColor = ambientStrenth * lightColor;
//
////����ֱ����ߵķ���
//vec3 lightDir = normalize(lightPos - FragPos);
//
////������
//vec3 norm = normalize(normal);
////��norm��lightDir�������е�ˣ��������Ե�ǰƬ�ε�ʵ�ʵ�ɢ��Ӱ��
//float diff = max(dot(norm, lightDir), 0.0);
//vec3 diffuse = diff * lightColor;
//
////���淴��
//float specularStrength = 0.5;//���淴��ǿ��
//vec3 viewDir = normalize(viewPos - FragPos);
//vec3 reflectDir = reflect(-lightDir, norm);//reflect����Ҫ���һ�������Ǵӹ�Դָ��Ƭ��λ�õ�����
////���㾵�����ȷ���
//float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
//vec3 specular = specularStrength * spec * lightColor;