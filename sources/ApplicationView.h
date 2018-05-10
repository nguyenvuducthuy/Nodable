#pragma once

#include "Nodable.h"
#include <imgui.h>
#include <SDL2/SDL.h>
#include <string>

namespace Nodable
{
	class ApplicationView
	{
	public:
		ApplicationView(const char* _name, Node_Application* _application);
		~ApplicationView();
		void draw();
		bool init();
	private:		
		Node_Application  *application;
		SDL_Window        *window;
		SDL_GLContext     glcontext;
		ImVec4            clear_color = ImColor(50, 50, 50);
		std::string       name;
	};
}