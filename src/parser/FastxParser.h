/*
 * FastxParser.h
 *
 *  Created on: Aug 22, 2012
 *      Author: fritz
 */

#ifndef FASTXPARSER_H_
#define FASTXPARSER_H_

#include "IParser.h"
#include <zlib.h>

class FastXParser: public IParser {

private:
	gzFile fp;

	kseq_t * tmp;

public:

	virtual ~FastXParser() {
		if(tmp != 0)
		{
			kseq_destroy(tmp);
			tmp = 0;
		}
		gzclose(fp);
	}

	virtual void init(char const * fileName, bool const keepTags) {
		fp = gzopen(fileName, "r");
		tmp = kseq_init(fp);
	}

	virtual int doParseRead(MappedRead * read) {
		if(read == 0 || read->Seq == 0 || read->name == 0 || read->qlty == 0) {
			Log.Error("Here!");

		}
		int l = kseq_read(tmp);
		return copyToRead(read, tmp, l);
	}

};

#endif /* FASTXPARSER_H_ */
