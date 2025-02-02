#version 150

#define MAX_LIGHTS 300 // Use a define to specify the max number of lights

out vec4 outColor;
in vec2 texCoord;
// Ensure these are actually world coordinates
in vec3 exWorldPos; 
in vec3 exWorldNormal;
uniform sampler2D texUnit;

uniform vec3 cameraPos;

// Light sources
uniform int lightCount; // Actual number of lights in use
uniform vec3 lightSourcesDirPos[MAX_LIGHTS];
uniform vec3 lightSourcesColors[MAX_LIGHTS];
uniform int isDirectional[MAX_LIGHTS];

void main(void) {
    vec3 finalShade = vec3(0.0);
    vec3 ambient = vec3(0.5);
    vec3 diffuse = vec3(0.0);
    vec3 specular = vec3(0.0);
    float specularExponent = 32.0;
    // ambient, diffuse, specular coefficients
    float k_a = 1, k_d = 1, k_s = 1; 
    // attenuation coefficients
    int a = 1, b = 1, c = 0;

    for (int i = 0; i < lightCount; i++) {
        float d = distance(exWorldPos, lightSourcesDirPos[i]);
        float attenuation = 1.0 / (a + b * d + c * d * d);
        vec3 lightDir = isDirectional[i] == 1
            ? lightSourcesDirPos[i]
            : normalize(lightSourcesDirPos[i] - exWorldPos); // s
        
        // diffuse component
        float diff = max(dot(exWorldNormal, lightDir), 0.0); // max to avoid negative values (cos Phi)
        diffuse += diff * attenuation * lightSourcesColors[i];

        // specular component
        vec3 reflectDir = reflect(-lightDir, exWorldNormal); // r
        vec3 viewDir = normalize(cameraPos - exWorldPos); // v

        vec3 halfwayDir = normalize(lightDir + viewDir); // h, blinn-phong

        float spec = pow(max(dot(exWorldNormal, halfwayDir), 0.0), specularExponent);
        specular += spec * attenuation * lightSourcesColors[i];
    }

    // Fetch the texture color
    vec4 texColor = texture(texUnit, texCoord);
    finalShade = k_a * ambient + k_d * diffuse + k_s * specular;
    // Modulate texture color with the calculated lighting
    outColor = texColor * vec4(finalShade, 1.0);

}
