#include "pch.h"
#include "SpriteAnimationRendererComponent.h"
#include "Renderer/TextureFrames.h"
#include "Engine.h"
#include "Math/MathUtils.h"

namespace nu {

	FACTORY_REGISTER(SpriteAnimationRendererComponent)
	
	void SpriteAnimationRendererComponent::Update(float dt)
	{
		if (!m_textureFrames) {
			std::cerr << "Texture frames not set!" << std::endl;
			return;
		}

		m_frameTimer += dt;
		float frameTime = 1.0f / m_framesPerSecond;

		//increase frame while frame timer is greater than frame time
		while (m_frameTimer >= frameTime) {
			m_currentFrame++;
			if (m_loop) {
				//loop frames
				m_currentFrame = m_currentFrame % m_textureFrames->GetTotalFrames();
			}
			else {
				//stop on last frame
				m_currentFrame = Clamp(0u, m_textureFrames->GetTotalFrames() - 1, m_currentFrame);
			}

			m_frameTimer -= frameTime;
		}
	}

	void SpriteAnimationRendererComponent::Draw(const Renderer& renderer)
	{
		if (!m_textureFrames) {
			std::cerr << "Texture frames not set!" << std::endl;
			return;
		}

		auto transform = GetOwner()->GetTransform();

		renderer.DrawTexture(
			*m_textureFrames->GetTexture(),
			m_textureFrames->GetFrameRect(m_currentFrame),
			transform.position.x,
			transform.position.y,
			transform.rotation,
			transform.scale
		);
	}

	void SpriteAnimationRendererComponent::Read(const json::value_t& value)
	{
		RendererComponent::Read(value);
		JSON_READ_NAME_REQ(value, "frames_per_second", m_framesPerSecond);
		JSON_READ_NAME(value, "loop", m_loop);

		std::string texture_frames;
		JSON_READ_REQ(value, texture_frames);

		if (texture_frames.empty()) {
			std::cerr << "Could not load texture frames: " << texture_frames << std::endl;

		} else {
			m_textureFrames = Resources().Get<TextureFrames>(texture_frames, Engine::Get().GetRenderer());
		}
	}
}
