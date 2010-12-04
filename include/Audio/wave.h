#include <hal/io.h>
#include <stdio.h>

#pragma pack(1)
struct WAV_Head
{
	char ChunkID[4]; //"RIFF"
	unsigned int ChunkSize;
	char Format[4]; //"WAVE"
	char Subchunk1ID[4]; //"fmt "
	unsigned int Subchunk1Size;
	short int AudioFormat;
	short int NumChannels;
	unsigned int SampleRate;
	unsigned int ByteRate;
	short int BlockAlign;
	short int BitsPerSample;
	char Subchunk2ID[4]; //"data"
	unsigned int Subchunk2Size;
};
#pragma pack()

void Load_Wave(char* fileName, WAV_Head wavHead)
{
	// Read in our header information
    FILE* fp = fopen("test.wav", "rb");

    fread(&wavHead, 1, sizeof(wavHead), fp);
    
    fclose(fp);
}
