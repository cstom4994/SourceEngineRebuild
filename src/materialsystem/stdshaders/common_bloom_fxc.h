
float4 BloomShape(float4 cColor, float4 params, float flBloomExp, float flBloomSaturation)
{
#if ( BLOOMTYPE == 1 )
	{
		float flLum = dot(cColor.xyz, params.xyz);
		cColor.rgb = pow(cColor.xyz, params.w) * flLum;
	}
#endif

#if ( BLOOMTYPE == 2 )
	{
		float flScale = 1.55f; // Color scale
		float flBias = -0.09f; // Color bias
		float flBrightnessClamp = 0.59f; // After scale and bias, clamp RGB values brighter than this
		cColor.rgb = pow(saturate(min(flBrightnessClamp, (cColor.rgb * flScale) + flBias)), flBloomExp);

		// Saturation
		cColor.rgb = lerp(dot(params.rgb, cColor.rgb), cColor.rgb, flBloomSaturation);
	}
#endif

#if ( BLOOMTYPE == 3 )
	{
		float lum = (0.3f * cColor.x) + (0.59f * cColor.y) + (0.11f * cColor.z);
		cColor.rgb = lum * cColor.rgb;
	}
#endif

	return cColor;
}