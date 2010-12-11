#include "core/Car.h"
#include "rendering/CarRenderer.h"

#ifdef WII
#include "rendering/wiigfx/WiiGfxCarRenderer.h"
#else
#include "rendering/reg/RegCarRenderer.h"
#endif

CarRenderer::CarRenderer( Car* car ) : Renderer(), car( car )
{
}

CarRenderer::~CarRenderer()
{
}

CarRenderer* CarRenderer::create( Car* car )
{

#ifdef WII
	return new WiiGfxCarRenderer( car );
#else
	return new RegCarRenderer( car );
#endif

}
