float2 BUFFER_PIXEL_SIZE : register( c1 );

static const int iBlurSamples = 4;

#define CONST_LOG2(v) (((v) & 0xAAAAAAAA) != 0) | ((((v) & 0xFFFF0000) != 0) << 4) | ((((v) & 0xFF00FF00) != 0) << 3) | ((((v) & 0xF0F0F0F0) != 0) << 2) | ((((v) & 0xCCCCCCCC) != 0) << 1)

static const float double_pi = 6.283185307179586476925286766559;
static const float3 luma_value = float3(0.2126, 0.7152, 0.0722);

float4 tex2DExB(sampler sp, float2 uv)
{
    float4 col = tex2D(sp, uv);
    float b = 0.2990 * col.r + 0.5870 * col.g  + 0.1140 * col.b;
    float c = clamp(b - 1.0, 0, 10);

    return col * c;
}

float3 blur1(sampler sp, float2 uv, float scale) {
    float2 ps = BUFFER_PIXEL_SIZE * scale;
    
    static const float kernel[9] = { 
        0.0269955, 0.0647588, 0.120985, 0.176033, 0.199471, 0.176033, 0.120985, 0.0647588, 0.0269955 
    };
    static const float accum = 1.02352;
    
    float gaussian_weight = 0.0;
    float3 col = 0.0;
    
    [unroll]
    for (int x = -iBlurSamples; x <= iBlurSamples; ++x) {
        [unroll]
        for (int y = -iBlurSamples; y <= iBlurSamples; ++y) {
            gaussian_weight = kernel[x + iBlurSamples] * kernel[y + iBlurSamples];
            col += tex2DExB(sp, uv + ps * float2(x, y)).rgb * gaussian_weight;
        }
    }

    return col * accum;
}

float3 blur(sampler sp, float2 uv, float scale) {
    float2 ps = BUFFER_PIXEL_SIZE * scale;
    
    static const float kernel[9] = { 
        0.0269955, 0.0647588, 0.120985, 0.176033, 0.199471, 0.176033, 0.120985, 0.0647588, 0.0269955 
    };
    static const float accum = 1.02352;
    
    float gaussian_weight = 0.0;
    float3 col = 0.0;
    
    [unroll]
    for (int x = -iBlurSamples; x <= iBlurSamples; ++x) {
        [unroll]
        for (int y = -iBlurSamples; y <= iBlurSamples; ++y) {
            gaussian_weight = kernel[x + iBlurSamples] * kernel[y + iBlurSamples];
            col += tex2D(sp, uv + ps * float2(x, y)).rgb * gaussian_weight;
        }
    }

    return col * accum;
}

float3 tonemap(float3 col, float exposure) {
    static const float A = 0.15; //shoulder strength
    static const float B = 0.50; //linear strength
	static const float C = 0.10; //linear angle
	static const float D = 0.20; //toe strength
	static const float E = 0.02; //toe numerator
	static const float F = 0.30; //toe denominator
	static const float W = 11.2; //linear white point value

    col *= exposure;

    col = ((col * (A * col + C * B) + D * E) / (col * (A * col + B) + D * F)) - E / F;
    static const float white = 1.0 / (((W * (A * W + C * B) + D * E) / (W * (A * W + B) + D * F)) - E / F);
    col *= white;
    return col;
}

float3 blend_screen(float3 a, float3 b) {
    return 1.0 - (1.0 - a) * (1.0 - b);
}