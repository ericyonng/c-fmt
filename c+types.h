//
//  c+types.h
//

#ifndef c_types_h
#define c_types_h

namespace cplus {

	/* IEEE-754 Double-precision floating point */

	union double_bits {
		double f;
		unsigned long long u;
		struct {
		#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
			unsigned long long man  : 52;
			unsigned long long exp  : 11;
			unsigned long long sign : 1;
		#else
			unsigned long long sign : 1;
			unsigned long long exp  : 11;
			unsigned long long man  : 52;
		#endif
		} r;
		struct {
		#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
			unsigned int d1;
			unsigned int d0;
		#else
			unsigned int d0;
			unsigned int d1;
		#endif
		} w;
	};

	struct double_type {
		typedef double              float_type;
		typedef unsigned long long  size_type;
		typedef double_bits         bits_type;
		enum {
			man_size = 52,
			man_digits = man_size + 1,
			exp_size = 11,
			exp_max = 1024,
			exp_denorm = 0,
			exp_inf = (1 << exp_size) - 1,
			dec_digits = 17
		};
	};

	/* arg types */

	enum arg_type : unsigned char {
		arg_type_none,
		arg_type_ptr,
		arg_type_cstr,
		arg_type_sstr,
		arg_type_char,
		arg_type_sint,
		arg_type_uint,
		arg_type_dbl
	};

	/* holder */

	union type_holder {
		const void*        ptr;
		const char*        cstr;
		std::string*       sstr;
		signed long long   sll;
		unsigned long long ull;
		double             dbl;
	};

	/* argument list */

	struct arg_list
	{
		const arg_type *at;
		const type_holder *th;
		const int elem;
		int nextarg;

		inline arg_list(const arg_type *at, const type_holder *th, const int elem) :
			at(at), th(th), elem(elem), nextarg(0) {}

		inline bool check(arg_type type) {
			if (nextarg >= elem) return false;
			if (type != arg_type_none && at[nextarg] != type) return false;
			return true;
		}

		inline bool get_int(unsigned long long &val) {
			if (check(arg_type_none)) {
				val = th[nextarg++].ull;
				return true;
			} else {
				return false;
			}
		}

		inline bool get_dbl(double &val) {
			if (check(arg_type_dbl)) {
				val = th[nextarg++].dbl;
				return true;
			} else {
				return false;
			}
		}

		inline bool get_char(int &val) {
			if (check(arg_type_char)) {
				val = th[nextarg++].sll;
				return true;
			} else {
				return false;
			}
		}

		inline bool get_str(std::string &str) {
			if (!check(arg_type_none)) {
				return false;
			} else if (th[nextarg].ptr == nullptr) {
				str = "(null)";
				nextarg++;
				return true;
			} else if (check(arg_type_sstr)) {
				str = *th[nextarg++].sstr;
				return true;
			} else if (check(arg_type_cstr)) {
				str = th[nextarg++].cstr;
				return true;
			} else {
				return false;
			}
		}
	};
}

#endif