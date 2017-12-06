#version 330 core
struct PointLight {
    vec3 position;  
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
	
    float constant;
    float linear;
    float quadratic;
}; 

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;

out vec4 FragColor;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;

uniform vec3 lightColor;
uniform vec3 viewPos;

uniform PointLight pLight;
uniform bool isSpecular = false;


void main()
{    
	// ������
	vec3 ambient = pLight.ambient * vec3(texture(texture_specular1, TexCoords));

	// ������
	vec3 normal = normalize(Normal);
	//vec3 lightDir = normalize(-pLight.direction);
	vec3 lightDir = normalize(pLight.position - FragPos);
	float diff = max(dot(normal, lightDir), 0.0);
	vec3 diffuse = pLight.diffuse * diff * vec3(texture(texture_diffuse1, TexCoords));
	// �߹ⷴ��
	vec3 specular;
	if(isSpecular){
		vec3 viewDir = normalize(viewPos - FragPos);
		vec3 reflectDir = reflect(-lightDir, normal);
		float spec = pow(max(dot(viewDir, reflectDir), 0.0), 64);
		specular = pLight.specular * spec * vec3(texture(texture_specular1, TexCoords));
	}
	else {
		specular = vec3(0,0,0);
	}
	

	float distance = length(pLight.position - FragPos);
	float attenuation = 1.0 / (pLight.constant + pLight.linear * distance + pLight.quadratic * (distance * distance));    

    FragColor = vec4((ambient + diffuse + specular) * attenuation , 1.0);
}