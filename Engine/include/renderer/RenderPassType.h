#pragma once

namespace GibEngine
{
  namespace Renderer 
  {
    enum class RenderPassType
	{
      DEFERRED_GEOMETRY,
      DEFERRED_LIGHTING,
      FORWARD_RENDERING,
	  SKYBOX,
	  RENDER_TO_TEXTURE,
	  RENDERPASSTYPE_LAST,
    };
  }
}