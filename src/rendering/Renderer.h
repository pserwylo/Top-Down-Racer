#ifndef RENDERER_H_
#define RENDERER_H_

class Renderer
{

public:
	Renderer() {};
	virtual ~Renderer() {};
	virtual void render() = 0;
};

#endif /* RENDERER_H_ */
