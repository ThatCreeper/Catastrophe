#pragma once

#include <cassert>

R RRead(const char *fname);
R RWrite(const char *fname);
void RClose(R &r);

#define SERIALIZE(r, field) Serialize(r, field)

#define ADD(rev, field) \
	if (r.revision >= rev) { \
		SERIALIZE(r, s.field); \
	}
#define ADD_CONDITIONAL(rev, cond, field) \
	if (r.revision >= rev && (cond)) { \
		SERIALIZE(r, s.field); \
	}
#define REM(rev, removed, type, field, def) \
	type field = def; \
	if (r.revision >= rev && r.revision < removed) { \
		SERIALIZE(r, field); \
	}

void SerializeBinary(R & r, void *x, size_t s);
#define SER_BIN(type, fmt) inline void Serialize(R &r, type &s) { SerializeBinary(r, &s, sizeof(s)); }

#define SER_CHECK \
	{ \
		int check = r.counter; \
		SERIALIZE(r, check); \
		assert(check == r.counter++); /* no-op when writing */ \
	}

#define SER_REV(r) { if (r.IsWriting()) r.revision = SR_LATEST; SERIALIZE(r, r.revision); assert(r.revision <= SR_LATEST); }

#define SERIALIZER(type) void Serialize(R &r, type &s)
#define SERIALIZER_END
#define DECL_SERIALIZER(type) SERIALIZER(type);
