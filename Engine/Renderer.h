#pragma once
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include "Transform.h"
#include "Mesh.h"
#include "Model.h"
using namespace nu;

namespace nu {

	

	class Renderer
	{
		friend class Text;
	public:
		void Initialize(int, int);
		void Shutdown();

		void Clear() const;
		void Present() const;

		void SetColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255) const;
		void SetColor(float r, float g, float b, float = 1.0f) const;


		void DrawPoint(float x, float y) const;
		void DrawLine(float x1, float y1, float x2, float y2) const;
		void DrawFillRect(float x, float y, float w, float h) const;
		void DrawRect(float x, float y, float w, float h) const;

		void DrawModel(const class Model& model, const struct Transform& transform) const;

		int GetWidth() const { return m_width; }
		int GetHeight() const { return m_height; }


	private:
		SDL_Window* window = nullptr;
		SDL_Renderer* renderer = nullptr;

		int m_width = 0;
		int m_height = 0;

	};
}