float tex2DprojBilinear(sampler depths, float2 size, float2 uv, float compare){
    float2 texelSize = 1.0f.xx/size;
    float2 f = frac(uv*size+0.5);;
    float2 centroidUV = floor(uv*size+0.5)/size;

    float lb = tex2Dproj(depths, float4(centroidUV+texelSize*float2(0.0, 0.0), compare, 1.0f)).x;
    float lt = tex2Dproj(depths, float4(centroidUV+texelSize*float2(0.0, 1.0), compare, 1.0f)).x;
    float rb = tex2Dproj(depths, float4(centroidUV+texelSize*float2(1.0, 0.0), compare, 1.0f)).x;
    float rt = tex2Dproj(depths, float4(centroidUV+texelSize*float2(1.0, 1.0), compare, 1.0f)).x;
    float a = lerp(lb, lt, f.y);
    float b = lerp(rb, rt, f.y);
    float c = lerp(a, b, f.x);
    return c;
}

float4 cubic(float v)
{
    float4 n = float4(1.0, 2.0, 3.0, 4.0) - v;
    float4 s = n * n * n;
    float x = s.x;
    float y = s.y - 4.0 * s.x;
    float z = s.z - 4.0 * s.y + 6.0 * s.x;
    float w = 6.0 - x - y - z;
    return float4(x, y, z, w);
}

float tex2DprojBicubic(sampler texSample, float2 texRes, float2 texCoords, float compare) {

    float2 texSize = texRes;
    float2 invTexSize = 1.0 / texSize;

    texCoords = texCoords * texSize - 0.5;


    float2 fxy = frac(texCoords);
    texCoords -= fxy;

    float4 xcubic = cubic(fxy.x);
    float4 ycubic = cubic(fxy.y);

    float4 c = texCoords.xxyy + float2(-0.5, +1.5).xyxy;

    float4 s = float4(xcubic.xz + xcubic.yw, ycubic.xz + ycubic.yw);
    float4 offset = c + float4(xcubic.yw, ycubic.yw) / s;

    offset *= invTexSize.xxyy;

    float4 sample0 = tex2Dproj(
        texSample, float4(offset.xz, compare, 1.0f));
    float4 sample1 = tex2Dproj(
        texSample, float4(offset.yz, compare, 1.0f));
    float4 sample2 = tex2Dproj(
        texSample, float4(offset.xw, compare, 1.0f));
    float4 sample3 = tex2Dproj(
        texSample, float4(offset.yw, compare, 1.0f));

    float sx = s.x / (s.x + s.y);
    float sy = s.z / (s.z + s.w);

    return lerp(
        lerp(sample3, sample2, sx), lerp(sample1, sample0, sx), sy);
}

float PCF(sampler depths, float2 size, float2 uv, float compare){
    float result = 0.0;
	const int blursize = 1;
    float2 invSize = 1.0f.xx / size;
    for(int x=-blursize; x<blursize + 1; x++){
        for(int y=-blursize; y<blursize +1; y++){
            //result += tex2DprojBicubic(depths, size, uv+float2(x/size.x,y/size.y), compare);
            float2 off = float2(float(x), float(y)) * invSize;
			result += tex2Dproj(depths, float4(uv+off, compare, 1.0f)).x;

        }
    }
    return result/pow(blursize * 2 +1, 2);
}