#pragma once

#include <FreeImage.h>

namespace sparky {
	static BYTE* load_image(const char* filename, GLsizei* width, GLsizei* height, int* BPP) {
		FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
		FIBITMAP *dib = nullptr;
		fif = FreeImage_GetFileType(filename, 0);
		if (fif == FIF_UNKNOWN) {
			fif = FreeImage_GetFIFFromFilename(filename);
		}
		if (fif == FIF_UNKNOWN) {
			return nullptr;
		}

		if (FreeImage_FIFSupportsReading(fif)) {
			dib = FreeImage_Load(fif, filename);
		}
		if (!dib) {
			return nullptr;
		}

		BYTE* result = FreeImage_GetBits(dib);
		*BPP = FreeImage_GetBPP(dib);
		*width = FreeImage_GetWidth(dib);
		*height = FreeImage_GetHeight(dib);

		return result;
	}
}