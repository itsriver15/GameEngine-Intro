#include "pch.h"
#include "TilemapRendererComponent.h"
#include "Engine.h"
#include "Renderer/Tilemap.h"
#include "Physics/PhysicsBody.h"

namespace nu {

	FACTORY_REGISTER(TilemapRendererComponent)

	TilemapRendererComponent::TilemapRendererComponent(const TilemapRendererComponent& other)
	{
		m_tilemapName = other.m_tilemapName;
	}

	void TilemapRendererComponent::Start()
	{
		m_tilemap = Resources().Get<Tilemap>(m_tilemapName, Engine::Get().GetRenderer());

	}

    void TilemapRendererComponent::Draw(const Renderer& renderer)
    {
        if (!m_tilemap)
            return;

        for (const auto& layer : m_tilemap->GetLayers()) {
            if (!layer.texture) {
                continue;
            }

            for (int i = 0; i < (int)layer.data.size(); i++) {
                int tileId = layer.data[i];

                if (tileId == 0) {
                    continue;
                }

                Rect source = m_tilemap->GetTileRect(layer, tileId);
                Vector2 position = m_tilemap->GetTilePosition(layer, i);

                renderer.DrawTexture(*layer.texture, source, position.x, position.y, 0.0f, 1.0f, false);
            }
        }
    }
	void TilemapRendererComponent::Read(const json::value_t& value)
	{
		RendererComponent::Read(value);

		JSON_READ_NAME_REQ(value, "tilemap_name", m_tilemapName);

	}
}