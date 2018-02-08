#ifndef DOABCCONTEXT_H
#define DOABCCONTEXT_H
#include <vector>

namespace SWF {
	class DoABCContext {
	public:
		DoABCContext();
		virtual ~DoABCContext();

		std::vector<unsigned char *> getContext();
		std::vector<int> getLen();
		std::vector<unsigned char *> getContext() const;
		std::vector<int> getLen() const;

        int getTotalLen();
		void setContext(unsigned char *buf, int length);

	private:
		std::vector<unsigned char *> context_;
		std::vector<int> len_vec_;
        int total_len_;
	};

}

#endif