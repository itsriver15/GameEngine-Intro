#include "pch.h"
#include "Renderer.h"
#include "Vector2.h"
#include "Model.h"
#include "MathUtils.h"
#include <iostream>
#include <string>
using namespace nu;

void Renderer::Initialize(int width, int height)
{
	SDL_Init(SDL_INIT_VIDEO);
	m_width = width;
	m_height = height;
	window = SDL_CreateWindow("SDL3 Project", width, height, 0);

	if (window == nullptr)
	{
		std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
	}


	renderer = SDL_CreateRenderer(window, nullptr);

	if (renderer == nullptr)
	{
		std::cerr << "SDL_CreateRenderer Error: "
			<< SDL_GetError() << std::endl;

		SDL_DestroyWindow(window);
		SDL_Quit();
	}

	SDL_SetRenderVSync(renderer, 1);

	if (!TTF_Init()) {
		std::cerr << "TTF_Init Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
	}


}

void Renderer::Shutdown() {
	TTF_Quit();
	if (renderer != nullptr) {
		SDL_DestroyRenderer(renderer);
	}
	if (window != nullptr) {
		SDL_DestroyWindow(window);
	}

	SDL_Quit();
}


void Renderer::Clear() const {
	SDL_RenderClear(renderer);
}

void Renderer::Present() const{
	SDL_RenderPresent(renderer);
}

void Renderer::SetColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) const {
	SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

void Renderer::SetColor(float r, float g, float b, float a) const {
	SDL_SetRenderDrawColorFloat(renderer, r, g, b, a);
}


void Renderer::DrawPoint(float x, float y) const {
	SDL_RenderPoint(renderer, x, y);
}

void Renderer::DrawLine(float x1, float y1, float x2, float y2) const {
	SDL_RenderLine(renderer, x1, y1, x2, y2);
}


void Renderer::DrawFillRect(float x, float y, float w, float h) const{
	SDL_FRect rect{ x, y, w, h };
	SDL_RenderFillRect(renderer, &rect);
}


void Renderer::DrawRect(float x, float y, float w, float h) const {
	SDL_FRect rect{ x, y, w, h };
	SDL_RenderRect(renderer, &rect);
}

void Renderer::DrawModel (const class Model& model, const struct Transform& transform) const
{
	
	for (auto mesh : model.GetMeshes()) {
		auto& points = mesh.GetPoints();
		SetColor(mesh.GetColor().r, mesh.GetColor().g, mesh.GetColor().b, 1.0f);


		for (int i = 0; i + 1 < mesh.GetPoints().size(); i++) {
			Vector2 v1 = points.at(i);
			Vector2 v2 = points.at(i + 1);

			v1 *= transform.scale;
			v2 *= transform.scale;

			v1 = v1.Rotate(transform.rotation * DegToRad);
			v2 = v2.Rotate(transform.rotation * DegToRad);

			v1 += transform.position;
			v2 += transform.position;
			DrawLine(v1.x, v1.y, v2.x, v2.y);
		}
	}

}





