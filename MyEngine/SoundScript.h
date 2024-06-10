// Purpose: SoundScript class declaration
#include "ysScript.h"
#include "fmod.hpp"
#include "fmod_errors.h"
using namespace ys;

class SoundScript : public Script
{
public:
	void soundLoad(std::wstring soundName);
	void playSound(std::wstring soundName);
private:
	FMOD::System* system;
	FMOD::Sound* sound;
	FMOD::Channel* channel;
	FMOD_RESULT result;
};