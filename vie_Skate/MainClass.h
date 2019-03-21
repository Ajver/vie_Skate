#include <vie/Engine.h>

#include "CameraControll.h"
#include "Map.h"

class MainClass : public vie::Engine
{
public:
	MainClass();
	~MainClass();

	void onCreate();
	void update(float et);
	void render(vie::Graphics* g);

private:
	CameraControll* cameraControll;
	Map* map;

};