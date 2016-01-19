#ifndef LOADEDASSET_H
#define LOADEDASSET_H

#include <iostream>
using std::istream;

class LoadedAsset
{
private:
	istream *stream;
	char *filepath;
public:
	LoadedAsset()
	{}

	LoadedAsset(LoadedAsset &asset)
	{
		this->stream = asset.getStream();
		this->filepath = asset.getFilePath();
	}

	LoadedAsset(istream *stream, char *filepath)
	{
		this->stream = stream;
		this->filepath = filepath;
	}

	istream *getStream()
	{
		return stream;
	}

	void setStream(istream *stream)
	{
		this->stream = stream;
	}

	char *getFilePath()
	{
		return filepath;
	}

	void setFilePath(char *filepath)
	{
		this->filepath = filepath;
	}
};

#endif