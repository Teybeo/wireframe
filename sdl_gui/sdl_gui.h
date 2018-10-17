/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_gui.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdarchiv <tdarchiv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 15:06:26 by tdarchiv          #+#    #+#             */
/*   Updated: 2018/10/17 15:34:41 by tdarchiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SDL_GUI_H
# define SDL_GUI_H

# include <SDL_video.h>
# include <SDL_render.h>
# include <SDL_events.h>

# include "renderer.h"

typedef struct	s_sdl_app {
	SDL_Window		*window;
	SDL_Renderer	*sdl_renderer;
	SDL_Texture		*texture;
	uint32_t		*pixels;
	t_renderer		renderer;
	t_vec2i			texture_size;
	bool			is_running;
	bool			is_mouse_captured;
}				t_sdl_app;

void			sdl_init(t_sdl_app *ctx, t_map map);
void			sdl_run(t_sdl_app *app);
void			sdl_event(t_sdl_app *ctx);
void			sdl_update(t_sdl_app *context);
void			sdl_draw(t_sdl_app *app);

t_camera_key	get_camera_key(SDL_Scancode scancode);
t_renderer_key	get_renderer_key(SDL_Scancode scancode);

#endif
