#ifndef CF25SOUNDFILE_H
#define CF25SOUNDFILE_H

#include "spriterengine/override/soundfile.h"

#include "Common.h"

namespace SpriterEngine
{

	class Cf25SoundFile : public SoundFile
	{
	public:
		Cf25SoundFile(std::string initialFilePath, LPRDATA rdPtr, Extension *ext);

		SoundObjectInfoReference * newSoundInfoReference();

	private:
		LPRDATA rdPtr; //pointer to runtime data, required to interact with sound manager in CF25
		Extension *ext;// pointer to extension
		UINT soundId; //sound id in CF25 sound bank
		string name;
	};

}

#endif // CF25SOUNDFILE_H
