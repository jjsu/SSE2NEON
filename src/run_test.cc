// =====================================================================================
// 
//       Filename:  run_test.cc
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  2016年10月18日 20时25分24秒
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Su Junjie (USTC), jjsu@email.ustc.edu.cn
//        Company:  
// 
// =====================================================================================

#include <iostream>
//#include <fstream>
#include <cstdint>
#include <cstdlib>
#include <ctime>
#include <string>

#ifdef __GNUC__                                               
#  define CV_DECL_ALIGNED(x) __attribute__ ((aligned (x)))    
#elif defined _MSC_VER                                        
#  define CV_DECL_ALIGNED(x) __declspec(align(x))             
#else                                                         
#  define CV_DECL_ALIGNED(x)                                  
#endif                                                        

#ifdef ARM
#define DESKTOP 0
#else
#define DESKTOP 1
#endif

#if DESKTOP
#include <xmmintrin.h>
//#include <emmintrin.h>
#include <pmmintrin.h>
#else
#include "sse2neon.h"
#endif

void print(std::string s, int8_t *a, int n)								
{																		
	std::cout << s << ": ";												
	for (int i = 0; i < n; i++)											
		std::cout << (int)a[i] << " ";									
	std::cout << std::endl;												
}																		

void print(std::string s, uint8_t *a, int n)							
{																		
	std::cout << s << ": ";												
	for (int i = 0; i < n; i++)											
		std::cout << (int)a[i] << " ";									
	std::cout << std::endl;												
}																		

void print(std::string s, int16_t *a, int n)							
{																		
	std::cout << s << ": ";												
	for (int i = 0; i < n; i++)											
		std::cout << a[i] << " ";										
	std::cout << std::endl;												
}																		

void print(std::string s, uint16_t *a, int n)							
{																		
	std::cout << s << ": ";												
	for (int i = 0; i < n; i++)											
		std::cout << a[i] << " ";										
	std::cout << std::endl;												
}																		

void print(std::string s, int32_t *a, int n)							
{																		
	std::cout << s << ": ";												
	for (int i = 0; i < n; i++)											
		std::cout << a[i] << " ";										
	std::cout << std::endl;												
}																		

void print(std::string s, uint32_t *a, int n)							
{																		
	std::cout << s << ": ";												
	for (int i = 0; i < n; i++)											
		std::cout << a[i] << " ";										
	std::cout << std::endl;												
}																		

void print(std::string s, int64_t *a, int n)							
{																		
	std::cout << s << ": ";												
	for (int i = 0; i < n; i++)											
		std::cout << a[i] << " ";										
	std::cout << std::endl;												
}																		

void print(std::string s, uint64_t *a, int n)							
{																		
	std::cout << s << ": ";												
	for (int i = 0; i < n; i++)											
		std::cout << a[i] << " ";										
	std::cout << std::endl;												
}																		

void print(std::string s, float  *a, int n)								
{																		
	std::cout << s << ": ";												
	for (int i = 0; i < n; i++)											
		std::cout << a[i] << " ";										
	std::cout << std::endl;												
}																		

void print(std::string s, double  *a, int n)							
{																		
	std::cout << s << ": ";												
	for (int i = 0; i < n; i++)											
		std::cout << a[i] << " ";										
	std::cout << std::endl;												
}																		


#define BI_TEST_DEFINE(FUNC,TYPE,SUBFIX,PTR_TYPE,VAL_TYPE)					\
	void test_ ## FUNC ## _ ##TYPE() {										\
		std:: cout << "function : "<< __FUNCTION__ << std::endl;			\
		const int   N = 16 / sizeof(TYPE);									\
		char CV_DECL_ALIGNED(16)  buf2[32];									\
		int count = 0;														\
		for (size_t i = 0; i < N; i++)										\
			for (size_t j = 0; j < N; j++)									\
				for (size_t k = 0; k < N; k++)								\
				{															\
					std:: cout << "iter."<< count++<<" : " << std::endl;	\
					TYPE* a = (TYPE*)(buf0)+i;								\
					TYPE* b = (TYPE*)(buf1)+j;								\
					TYPE* c = (TYPE*)(buf2)+k;								\
					std::cout << "\t(a,b,c) offset : ("						\
						<< i << "," << j << ","								\
						<< k << ")" << std::endl;							\
					VAL_TYPE r0,r1,t;										\
																			\
					if (i==0)												\
						r0 =  _mm_load_ ## SUBFIX((const PTR_TYPE *)a);		\
					else													\
						r0 =  _mm_loadu_ ## SUBFIX((const PTR_TYPE *)a);	\
																			\
					if (j==0)												\
						r1 =  _mm_load_ ## SUBFIX((const PTR_TYPE *)b);		\
					else													\
						r1 =  _mm_loadu_ ## SUBFIX((const PTR_TYPE *)b);	\
																			\
					t = FUNC (r0,r1);										\
																			\
					if (k==0)												\
						_mm_store_ ## SUBFIX(( PTR_TYPE *)c,t);				\
					else													\
						_mm_storeu_ ## SUBFIX((PTR_TYPE *)c,t);				\
					print("\ta        ", a, N);										\
					print("\tb        ", b, N);										\
					print("\tc=OP(a,b)", c, N);								\
				}															\
	}


#define SET_TEST_DEFINE(FUNC,TYPE,SUBFIX,PTR_TYPE,VAL_TYPE)					\
	void test_ ## FUNC ## _ ##TYPE() {										\
		std:: cout << "function : "<< __FUNCTION__ << std::endl;			\
		const int   N = 16 / sizeof(TYPE);									\
		char CV_DECL_ALIGNED(16)  buf2[32];									\
		int count = 0;														\
		for (size_t k = 0; k < N; k++)								\
		{															\
			std:: cout << "iter."<< count++<<" : " << std::endl;	\
			TYPE* c = (TYPE*)(buf2)+k;								\
			std::cout << "\t(c) offset : ("						\
				<< k << ")" << std::endl;							\
			VAL_TYPE t;										\
																	\
																			\
																			\
			t = FUNC (77);										\
																		\
			if (k==0)												\
				_mm_store_ ## SUBFIX(( PTR_TYPE *)c,t);				\
			else													\
				_mm_storeu_ ## SUBFIX((PTR_TYPE *)c,t);				\
			print("\tc=OP(a)", c, N);								\
		}															\
	}

#define GET_TEST_DEFINE(FUNC,TYPE,SUBFIX,PTR_TYPE,VAL_TYPE)					\
	void test_ ## FUNC ## _ ##TYPE() {										\
		std:: cout << "function : "<< __FUNCTION__ << std::endl;			\
		const int   N = 16 / sizeof(TYPE);									\
		int count = 0;														\
		for (size_t i = 0; i < N; i++)										\
				{															\
					std:: cout << "iter."<< count++<<" : " << std::endl;	\
					TYPE* a = (TYPE*)(buf0)+i;								\
					std::cout << "\t(a,b,c) offset : ("						\
						<< i 						\
						<< ")" << std::endl;							\
/*  					std::cout << "\t(a,b,c) address : ("				\
						<< static_cast<void*>(a)							\
						<< "," << static_cast<void*>(b)						\
						<< "," << static_cast<void*>(c)						\
						<< ")" << std::endl;								\
*/																			\
					VAL_TYPE r0;										\
																			\
					if (i==0)												\
						r0 =  _mm_load_ ## SUBFIX((const PTR_TYPE *)a);		\
					else													\
						r0 =  _mm_loadu_ ## SUBFIX((const PTR_TYPE *)a);	\
																			\
																			\
					int t = FUNC (r0);										\
																			\
					print("\ta        ", a, N);										\
					std::cout<<"\tc=OP(a) "<<t<<std::endl;					\
				}															\
	}

#define LOAD_TEST_DEFINE(FUNC,TYPE,SUBFIX,PTR_TYPE,VAL_TYPE)					\
	void test_ ## FUNC ## _ ##TYPE() {										\
		std:: cout << "function : "<< __FUNCTION__ << std::endl;			\
		const int   N = 16 / sizeof(TYPE);									\
		char CV_DECL_ALIGNED(16)  buf2[32];									\
		int count = 0;														\
		for (size_t k = 0; k < N; k++)								\
		{															\
			std:: cout << "iter."<< count++<<" : " << std::endl;	\
			TYPE* a = (TYPE*)(buf0);								\
			TYPE* c = (TYPE*)(buf2)+k;								\
			std::cout << "\t(c) offset : ("						\
				<< k << ")" << std::endl;							\
			VAL_TYPE t;										\
																	\
			t =  FUNC ((const PTR_TYPE *)a);		\
																	\
																	\
																	\
			if (k==0)												\
				_mm_store_ ## SUBFIX(( PTR_TYPE *)c,t);				\
			else													\
				_mm_storeu_ ## SUBFIX((PTR_TYPE *)c,t);				\
			print("\ta        ", a, N);										\
			print("\tc=OP(a)", c, N);								\
		}															\
	}

#define STORE_TEST_DEFINE(FUNC,TYPE,SUBFIX,PTR_TYPE,VAL_TYPE)					\
	void test_ ## FUNC ## _ ##TYPE() {										\
		std:: cout << "function : "<< __FUNCTION__ << std::endl;			\
		const int   N = 16 / sizeof(TYPE);									\
		int count = 0;														\
		for (size_t i = 0; i < N; i++)										\
		{															\
			std:: cout << "iter."<< count++<<" : " << std::endl;	\
			TYPE* a = (TYPE*)(buf0)+i;								\
			TYPE* b = (TYPE*)(buf1);								\
			std::cout << "\t(a) offset : ("						\
				<< i  								\
				<< ")" << std::endl;							\
			VAL_TYPE r0;										\
																	\
			if (i==0)												\
				r0 =  _mm_load_ ## SUBFIX((const PTR_TYPE *)a);		\
			else													\
				r0 =  _mm_loadu_ ## SUBFIX((const PTR_TYPE *)a);	\
																	\
			print("\ta        ", a, N);										\
			print("\tb        ", b, N);										\
																	\
			FUNC ((PTR_TYPE *)b,r0);										\
																	\
			print("\tOP(b,a)", b, N);								\
		}															\
	}





#define TEST_RUN(FUNC,TYPE)												\
	test_ ## FUNC ## _ ##TYPE () ;


#define TEST_DEFINE_INTEGER(PREFIX,FUNC)											\
	PREFIX ## _TEST_DEFINE(FUNC,uint8_t ,si128,__m128i,__m128i);			\
	PREFIX ## _TEST_DEFINE(FUNC,int8_t  ,si128,__m128i,__m128i);			\
	PREFIX ## _TEST_DEFINE(FUNC,uint16_t,si128,__m128i,__m128i);				\
	PREFIX ## _TEST_DEFINE(FUNC,int16_t ,si128,__m128i,__m128i);				\
	PREFIX ## _TEST_DEFINE(FUNC,uint32_t,si128,__m128i,__m128i);				\
	PREFIX ## _TEST_DEFINE(FUNC,int32_t ,si128,__m128i,__m128i);				\
	PREFIX ## _TEST_DEFINE(FUNC,uint64_t,si128,__m128i,__m128i);				\
	PREFIX ## _TEST_DEFINE(FUNC,int64_t ,si128,__m128i,__m128i);				\

#define TEST_DEFINE_FLOAT(PREFIX,FUNC)										\
	PREFIX ## _TEST_DEFINE(FUNC,float,ps,float,__m128);					\
	PREFIX ## _TEST_DEFINE(FUNC,double,ps,float,__m128);				\


#define TEST_RUN_INTEGER(PREFIX,FUNC)									\
	TEST_RUN(FUNC,uint8_t);											\
	TEST_RUN(FUNC,int8_t);											\
	TEST_RUN(FUNC,uint16_t);										\
	TEST_RUN(FUNC,int16_t);											\
	TEST_RUN(FUNC,uint32_t);										\
	TEST_RUN(FUNC,int32_t);											\
	TEST_RUN(FUNC,uint64_t);										\
	TEST_RUN(FUNC,int64_t);											\

#define TEST_RUN_FLOAT(PREFIX,FUNC)										\
	TEST_RUN(FUNC,float);											\
	TEST_RUN(FUNC,double);										\

#define TEST(PREFIX,FUNC,TYPE)											\
class PREFIX ## Test ## FUNC											\
{																		\
public:																	\
	PREFIX ## Test ## FUNC() {											\
		for (size_t i = 0; i < 32; i++)										\
		{int x; std::cin >> x; buf0[i]=x;}									\
		for (size_t i = 0; i < 32; i++)										\
		{int x; std::cin >> x; buf1[i]=x;}									\
		run();																\
	}																		\
	~PREFIX ## Test ## FUNC() {};													\
	void run() {															\
		TEST_RUN_ ## TYPE(PREFIX,FUNC);											\
	}																		\
																			\
private:																	\
	char CV_DECL_ALIGNED(16)  buf0[32];										\
	char CV_DECL_ALIGNED(16)  buf1[32];										\
																			\
	TEST_DEFINE_ ## TYPE(PREFIX , FUNC)											\
																			\
																			\
};																			\



#define RUN(PREFIX,FUNC,VAL)   PREFIX ## Test ## FUNC VAL;

#define BI_RUN(FUNC,VAL)    RUN(BI,FUNC,VAL)
#define SET_RUN(FUNC,VAL)    RUN(SET,FUNC,VAL)
#define GET_RUN(FUNC,VAL)    RUN(GET,FUNC,VAL)
#define LOAD_RUN(FUNC,VAL)    RUN(LOAD,FUNC,VAL)
#define STORE_RUN(FUNC,VAL)    RUN(STORE,FUNC,VAL)











TEST(BI,_mm_max_epu8,INTEGER)
TEST(BI,_mm_max_epi16,INTEGER)
TEST(BI,_mm_max_ps,FLOAT)
TEST(BI,_mm_min_epu8,INTEGER)
TEST(BI,_mm_min_epi16,INTEGER)
TEST(BI,_mm_min_ps,FLOAT)
TEST(BI,_mm_add_epi16,INTEGER)
TEST(BI,_mm_sub_epi16,INTEGER)
TEST(BI,_mm_adds_epu16,INTEGER)

TEST(SET,_mm_cvtsi32_si128,INTEGER)
TEST(GET,_mm_cvtsi128_si32,INTEGER)
TEST(LOAD,_mm_loadl_epi64,INTEGER)
TEST(STORE,_mm_storel_epi64,INTEGER)
TEST(LOAD,_mm_load_ss,FLOAT)
TEST(STORE,_mm_store_ss,FLOAT)

int main()
{
	BI_RUN(_mm_max_epu8,t0);
	BI_RUN(_mm_max_epi16,t1);
	BI_RUN(_mm_max_ps,t2);
	BI_RUN(_mm_min_epu8,t3);
	BI_RUN(_mm_min_epi16,t4);
	BI_RUN(_mm_min_ps,t5);
	BI_RUN(_mm_add_epi16,t6);
	BI_RUN(_mm_sub_epi16,t7);
	BI_RUN(_mm_adds_epu16,t8);

	SET_RUN(_mm_cvtsi32_si128,t9);
	GET_RUN(_mm_cvtsi128_si32,t10);
	LOAD_RUN(_mm_loadl_epi64,t11);
	STORE_RUN(_mm_storel_epi64,t12);
	LOAD_RUN(_mm_load_ss,t13);
	STORE_RUN(_mm_store_ss,t14);


	return 0;

}

