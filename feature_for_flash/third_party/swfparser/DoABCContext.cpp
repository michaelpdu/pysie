#include "DoABCContext.h"
#include <cstdlib>

namespace SWF {

	DoABCContext::DoABCContext() {
        total_len_ = 0;
	}

	DoABCContext::~DoABCContext() {
		for (int i = 0; i < context_.size(); ++i) {
            delete context_[i];
        }
	}


	std::vector<unsigned char *>DoABCContext::getContext() {
		return context_;
	}

	std::vector<int> DoABCContext::getLen() {
		return len_vec_;
	}

	std::vector<unsigned char *> DoABCContext::getContext() const {
		return context_;
	}

	std::vector<int> DoABCContext::getLen() const {
		return len_vec_;
	}

	void DoABCContext::setContext(unsigned char *buf, int length) {
        if (NULL == buf || 0 == length) {
            return;
        }
		context_.push_back(buf);
        len_vec_.push_back(length);
        total_len_ += length;
	}
	
    int DoABCContext::getTotalLen() {
        return total_len_;
    }
}