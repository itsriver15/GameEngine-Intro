#pragma once
#include "../Resources/ResourceManager.h"
#include "../Math/Vector2.h"
#include "../Renderer/Texture.h"
#include "../Math/Rect.h"
#include <string>

namespace nu {
	class TextureFrames : public Resource {
	public:
		bool Load(const std::string& filename, class Renderer& renderer);
		Rect GetFrameRect(int frame);

	private:
		int m_numColumns = 0;
		int m_numRows = 0;

		int m_startFrame = 0;
		int m_totalFrames = 0;

		Vector2 m_frameSize{ 0.0f, 0.0f };
		res_t<Texture> m_texture;

	};

	Rect TextureFrames::GetFrameRect(int frame) {

		if (frame <= 0 || frame >= m_totalFrames) {
			std::cerr << "Texture Frames frame is < 0 || >= total frames\n";
			frame = 0;
		}

		int currentFrame = m_startFrame + frame;

		int column = currentFrame % m_numColumns;
		int row = currentFrame % m_numColumns;

		float x = column * m_frameSize.x;
		float y = row * m_frameSize.y;

		return Rect{
			x, y, m_frameSize.x, m_frameSize.y
		};
	}
}