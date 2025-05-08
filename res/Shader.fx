float4 vsmain(float4 position : POSITION) : SV_POSITION {
	if (position.y > 0 && position.y < 1){
		position.x += 0.25f;
	}
	if (position.x > -1 && position.x < 0){
		position.y += 0.25f;
	}
	return position;
}

float4 psmain(float4 position : POSITION) : SV_Target {
	return float4(0.8f, 0.9f, 0.4f, 1.0f);   
}