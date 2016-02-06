#include "cf25soundfile.h"

#include "spriterengine/global/settings.h"

#include "cf25soundobjectinforeference.h"

namespace SpriterEngine
{
	Cf25SoundFile::Cf25SoundFile(std::string initialFilePath, LPRDATA rdPtr, Extension *ext) :
		SoundFile(initialFilePath), rdPtr(rdPtr), ext(ext)
	{
		name = initialFilePath;
		char sep = '/';
		size_t i = initialFilePath.rfind(sep, initialFilePath.length());
		if (i != string::npos) {
			name = (initialFilePath.substr(i + 1, initialFilePath.length() - i));
		}
		const size_t last_slash_idx = name.find('.');
		if (std::string::npos != last_slash_idx+1)
		{
			name = name.substr(0, last_slash_idx);
		}
		CA2T wstr(name.c_str());
		soundId = FindSndFromName(rdPtr->rHo.hoAdRunHeader->rhIdAppli, SP_WAVE, wstr);
		if (soundId < 0)//if not found
		{
			soundId = -1;
		}
	}

	
	 
	SoundObjectInfoReference * Cf25SoundFile::newSoundInfoReference()
	{
		return new Cf25SoundObjectInfoReference(ext, rdPtr, name, soundId);
	}

}
