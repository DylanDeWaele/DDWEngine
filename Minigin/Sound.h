#pragma once
class Sound
{
public:
	enum class Type
	{
		Music,
		SoundEffect
	};

	//Ctor
	Sound(Type type, bool playOnStart);
	//Dtor
	~Sound() = default;

	//Public member functions
	const Type& GetType() const;
	bool ShouldPlayOnStart() const;

	virtual void Play() {};
	virtual void Pause() {};
	virtual void Stop() {};

private:
	//Private datamembers
	Type m_Type;
	const bool m_PlayOnStart;
};

