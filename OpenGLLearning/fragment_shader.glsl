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

uniform vec3 lightColor;
uniform vec3 viewPos;

uniform PointLight pLight;

void main()
{    
	// 环境光
	vec3 ambient = pLight.ambient;

	// 漫反射
	vec3 normal = normalize(Normal);
	//vec3 lightDir = normalize(-pLight.direction);
	vec3 lightDir = normalize(pLight.position - FragPos);
	float diff = max(dot(normal, lightDir), 0.0);
	vec3 diffuse = pLight.diffuse * diff;

	// 高光反射
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 64);
	vec3 specular = pLight.specular * spec;  

	float distance = length(pLight.position - FragPos);
	float attenuation = 1.0 / (pLight.constant + pLight.linear * distance + pLight.quadratic * (distance * distance));    

    FragColor = vec4((ambient + diffuse + specular) * attenuation * vec3(texture(texture_diffuse1, TexCoords)), 1.0);
}