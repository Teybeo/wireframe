
void	renderer_draw0(t_renderer renderer) {

	t_vec3 a = {500, 500, 0};
	t_vec3 b = {801, 800, 0};

	t_vec3i a_i;
	t_vec3i b_i;

	ft_memzero(renderer.pixels, renderer.size.x * renderer.size.y, sizeof(uint32_t));

	static int step_count = 8;
//	step_count = ((cos(clock() / 1000000.f) * 0.5) + 0.5f) * 1000;
	step_count = 10000;
//	printf("step_count: %d\n", step_count);
//	step_count;
	float angle;
	float step = (2 * M_PI_F) / step_count;
	for (angle = 0; angle < (2 * M_PI_F); angle += step)
	{
		b.x = a.x + cos(angle) * 400;
		b.y = a.x + sin(angle) * 400;
		a_i = vec3_round(a);
		b_i = vec3_round(b);
		a_i.z = 0x00FF0000;
		b_i.z = 0x000000FF;
		draw_line(&renderer, a_i, b_i, 0, 0);
	}
//	usleep(100000);
}

void	renderer_draw1(t_renderer renderer) {

	t_vec3 center = {200, 200, 0};
	int length = 200;
	t_vec3 a;
	t_vec3 b;

	ft_memzero(renderer.pixels, renderer.size.x * renderer.size.y, sizeof(uint32_t));

	static float angle = 150;
	float rad = DEG_TO_RAD(angle);
	{
		a.x = cosf(rad) * length;
		a.y = sinf(rad) * length;
		a = vec3_add(a, center);
		b = vec3_sub(center, a);
		(void)b;
//		draw_line(renderer, center, a);
//		t_vec2i a_i = vec3_round2D(a);
//		t_vec2i center_i = vec3_round2D(center);
//		draw_line(renderer, a_i, center_i);
	}
	if (angle > 360)
		angle = 0;
	angle += .5f;
	printf("Angle: %f\n", angle);

//	usleep(100000);
}
