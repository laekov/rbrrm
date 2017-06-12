#include <textreporter.hh>
#include <cstdio>

void TextReporter::print(const char* fileName) {
	FILE* fout(fopen(fileName ? fileName : "out.txt", "w"));
	fprintf(fout, "%d %d %d\n", n, m, w);
	for (LineArr::const_iterator it = lines.begin(); it != lines.end(); ++ it) {
		fprintf(fout, "%d %d\n", it->first, it->second);
	}
	fclose(fout);
	fprintf(stderr, "Answer printed to %s\n", fileName ? fileName : "out.txt");
}

