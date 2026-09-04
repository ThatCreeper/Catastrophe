#include "version.h"

#if !SER_DEBUG

R RRead(const char* fname) {
	R r;
	r.reading = true;
#if __linux__
	r.file = fopen(fname, "r");
#elifndef PLATFORM_WEB
	fopen_s(&r.file, fname, "r");
#endif
	return r;
}

R RWrite(const char* fname) {
	R r;
	r.reading = false;
#if __linux__
	r.file = fopen(fname, "w");
#elifndef PLATFORM_WEB
	fopen_s(&r.file, fname, "w");
#endif
	return r;
}

void RClose(R& r) {
	if (r.file)
		fclose(r.file);
}

void SerializeBinary(R& r, void* x, size_t s) {
	if (r.IsReading()) {
		fread(x, s, 1, r.file);
	}
	else {
		fwrite(x, s, 1, r.file);
	}
}

#endif
