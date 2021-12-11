float3 packNormals(float3 n)
{
    //return normalize(n) * 0.5f + 1.0f;
    return n;
}

float3 unpackNormals(float3 n)
{
    //return normalize(n * 2.0f - 1.0f);
    return n;
}