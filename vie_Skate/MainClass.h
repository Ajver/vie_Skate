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

	void onFatalError(const std::string& errMsg);
	void onLog(const std::string& errMsg);

private:
	CameraControll* cameraControll;
	Map* map;

};