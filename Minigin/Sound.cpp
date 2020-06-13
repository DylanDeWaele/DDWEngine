#include "MiniginPCH.h"
#include "Sound.h"

Sound::Sound(Type type, bool playOnStart)
	: m_Type{type},
	m_PlayOnStart{playOnStart}
{
}

const Sound::Type& Sound::GetType() const
{
	return m_Type;
}

bool Sound::ShouldPlayOnStart() const
{
	return m_PlayOnStart;
}
