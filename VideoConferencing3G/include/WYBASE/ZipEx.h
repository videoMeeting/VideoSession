/**********************************************************
 * Name: Zip.h
 * Author: zhouxiaochuan@gmail.com
 * Date: 2007-08-03
 **********************************************************/

#pragma once

//---------------------------------------------------------------------------------------
class AFX_EXT_CLASS KZipEx
{
public:
	KZipEx(){};
	~KZipEx(){};

	/* Compression
	 * Takes a pointer to memory and how many bytes are there
	 * Compresses the memory into a new buffer this function allocates
	 * Returns a pointer to the new buffer, and writes its size under pnOutput,
	 * Note: member to delete[] pResult. */
	static unsigned char* Compress(void* pInput, unsigned long nInput, unsigned long* pnOutput, unsigned long nSuggest=0);

	/* Decompression
	 * Takes a pointer to compressed input bytes, and how many are there
	 * Decompresses the memory into a new buffer this function allocates
	 * Returns a pointer to the new buffer, and writes its size under pnOutput
	 * Note: member to delete[] pResult. */
	static unsigned char* Decompress(const void* pInput, unsigned long nInput, unsigned long* pnOutput, unsigned long nSuggest=0);
};

