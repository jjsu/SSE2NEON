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
#include <fstream>
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

#define LOAD_INTEGER(X) _mm_load_si128((const __m128i *)X)
#define LOADU_INTEGER(X) _mm_loadu_si128((const __m128i *)X)
#define LOAD_FLOAT(X) _mm_load_ps((const float *)X)
#define LOADU_FLOAT(X) _mm_loadu_ps((const float *)X)
#define STORE_INTEGER(X,Y) _mm_store_si128((__m128i *)X, Y)
#define STOREU_INTEGER(X,Y) _mm_storeu_si128((__m128i *)X, Y)
#define STORE_FLOAT(X,Y) _mm_store_ps((float *)X, Y)
#define STOREU_FLOAT(X,Y) _mm_storeu_ps((float *)X, Y)


#define UNARY_FOR_LOOP(FUNC,TYPE,LD_TYPE,SD_TYPE,VAL_TYPE,RESULT_TYPE)	\
for (size_t i = 0; i < N; i++)											\
	for (size_t k = 0; k < N; k++)									\
	{																\
		std::cout << "iter." << count++ << " : " << std::endl;		\
		TYPE* a = (TYPE*)(buf0)+i;									\
		TYPE* c = (TYPE*)(buf2)+k;									\
		std::cout << "\t(a,c) offset : ("							\
		<< i << ","   												\
		<< k << ")" << std::endl;									\
		VAL_TYPE r0, r1;											\
		RESULT_TYPE  t;												\
																	\
		if (i == 0)													\
			r0 = LOAD_ ## LD_TYPE(a);								\
		else														\
			r0 = LOADU_ ## LD_TYPE(a);								\
																	\
		t = FUNC (r0);												\
																	\
		if (k==0)													\
			STORE_ ## SD_TYPE(c,t);									\
		else														\
			STOREU_ ## SD_TYPE(c,t);								\
		print("\ta        ", a, N);									\
		print("\tc=OP(a)", c, N);									\
	}																\


#define BINARY_FOR_LOOP(FUNC,TYPE,LD_TYPE,SD_TYPE,VAL_TYPE,RESULT_TYPE)	\
for (size_t i = 0; i < N; i++)											\
	for (size_t j = 0; j < N; j++)										\
		for (size_t k = 0; k < N; k++)									\
		{																\
			std::cout << "iter." << count++ << " : " << std::endl;		\
			TYPE* a = (TYPE*)(buf0)+i;									\
			TYPE* b = (TYPE*)(buf1)+j;									\
			TYPE* c = (TYPE*)(buf2)+k;									\
			std::cout << "\t(a,b,c) offset : ("							\
			<< i << "," << j << ","										\
			<< k << ")" << std::endl;									\
			VAL_TYPE r0, r1;											\
			RESULT_TYPE  t;												\
																		\
			if (i == 0)													\
				r0 = LOAD_ ## LD_TYPE(a);								\
			else														\
				r0 = LOADU_ ## LD_TYPE(a);								\
																		\
			if (j==0)													\
				r1 =  LOAD_ ## LD_TYPE(b);								\
			else														\
				r1 =  LOADU_ ## LD_TYPE(b);								\
																		\
			t = FUNC (r0,r1);											\
																		\
			if (k==0)													\
				STORE_ ## SD_TYPE(c,t);									\
			else														\
				STOREU_ ## SD_TYPE(c,t);								\
			print("\ta        ", a, N);									\
			print("\tb        ", b, N);									\
			print("\tc=OP(a,b)", c, N);									\
		}																\
																						


#define TEST_DEFINE(PREFIX,FUNC,TYPE,LD_TYPE,SD_TYPE,VAL_TYPE,RESULT_TYPE)	\
	void test_ ## FUNC ## _ ## TYPE() {												\
		std:: cout << "function : "<< __FUNCTION__ << std::endl;					\
		const int   N = 16 / sizeof(TYPE);											\
		char CV_DECL_ALIGNED(16)  buf2[32];											\
		int count = 0;																\
		PREFIX ## _FOR_LOOP(FUNC,TYPE,LD_TYPE,SD_TYPE,VAL_TYPE,RESULT_TYPE)			\
	}

#ifdef ARM
#define INPUT "/data/input"
#else
#define INPUT "input"
#endif

#define BINARY_INIT										\
private:												\
	char CV_DECL_ALIGNED(16)  buf0[32];					\
	char CV_DECL_ALIGNED(16)  buf1[32];					\
void init()												\
{														\
	std::ifstream infile(INPUT);						\
	if(!infile)											\
	{													\
		std::cout << "No input file!" << std::endl;		\
		exit(-1);										\
	}													\
	int x;												\
	for (size_t i = 0; i < 32; i++)						\
	{													\
		infile >> x;									\
		buf0[i] = x;									\
	}													\
	for (size_t i = 0; i < 32; i++)						\
	{													\
		infile >> x;									\
		buf1[i] = x; 									\
	}													\
}														\

#define UNARY_INIT							\
private:									\
	char CV_DECL_ALIGNED(16)  buf0[32];		\
void init()									\
{											\
	std::ifstream infile(INPUT);			\
	int x;									\
	for (size_t i = 0; i < 32; i++)			\
	{										\
		infile >> x;						\
		buf0[i] = x;						\
	}										\
}											\

#define TEST_DEFINE_INTEGER(PREFIX,FUNC)								\
	TEST_DEFINE(PREFIX,FUNC,uint8_t ,INTEGER,INTEGER,__m128i,__m128i);	\
	TEST_DEFINE(PREFIX,FUNC,int8_t  ,INTEGER,INTEGER,__m128i,__m128i);	\
	TEST_DEFINE(PREFIX,FUNC,uint16_t,INTEGER,INTEGER,__m128i,__m128i);	\
	TEST_DEFINE(PREFIX,FUNC,int16_t ,INTEGER,INTEGER,__m128i,__m128i);	\
	TEST_DEFINE(PREFIX,FUNC,uint32_t,INTEGER,INTEGER,__m128i,__m128i);	\
	TEST_DEFINE(PREFIX,FUNC,int32_t ,INTEGER,INTEGER,__m128i,__m128i);	\
	TEST_DEFINE(PREFIX,FUNC,uint64_t,INTEGER,INTEGER,__m128i,__m128i);	\
	TEST_DEFINE(PREFIX,FUNC,int64_t ,INTEGER,INTEGER,__m128i,__m128i);	\

#define TEST_DEFINE_FLOAT(PREFIX,FUNC)									\
	TEST_DEFINE(PREFIX,FUNC,float ,FLOAT,FLOAT,__m128,__m128);			\
	TEST_DEFINE(PREFIX,FUNC,double,FLOAT,FLOAT,__m128,__m128);			\

#define TEST_DEFINE_I2F(PREFIX,FUNC)									\
	TEST_DEFINE(PREFIX,FUNC,uint8_t ,INTEGER,FLOAT,__m128i,__m128);		\
	TEST_DEFINE(PREFIX,FUNC,int8_t  ,INTEGER,FLOAT,__m128i,__m128);		\
	TEST_DEFINE(PREFIX,FUNC,uint16_t,INTEGER,FLOAT,__m128i,__m128);		\
	TEST_DEFINE(PREFIX,FUNC,int16_t ,INTEGER,FLOAT,__m128i,__m128);		\
	TEST_DEFINE(PREFIX,FUNC,uint32_t,INTEGER,FLOAT,__m128i,__m128);		\
	TEST_DEFINE(PREFIX,FUNC,int32_t ,INTEGER,FLOAT,__m128i,__m128);		\
	TEST_DEFINE(PREFIX,FUNC,uint64_t,INTEGER,FLOAT,__m128i,__m128);		\
	TEST_DEFINE(PREFIX,FUNC,int64_t ,INTEGER,FLOAT,__m128i,__m128);		\

#define TEST_RUN(FUNC,TYPE)												\
	test_ ## FUNC ## _ ##TYPE () ;

#define TEST_RUN_INTEGER(PREFIX,FUNC)									\
	TEST_RUN(FUNC,uint8_t);												\
	TEST_RUN(FUNC,int8_t);												\
	TEST_RUN(FUNC,uint16_t);											\
	TEST_RUN(FUNC,int16_t);												\
	TEST_RUN(FUNC,uint32_t);											\
	TEST_RUN(FUNC,int32_t);												\
	TEST_RUN(FUNC,uint64_t);											\
	TEST_RUN(FUNC,int64_t);												\
						
#define TEST_RUN_FLOAT(PREFIX,FUNC)										\
	TEST_RUN(FUNC,float);												\
	TEST_RUN(FUNC,double);												\

#define TEST(PREFIX,FUNC,TYPE)											\
class PREFIX ## Test ## FUNC											\
{																		\
	PREFIX ## _INIT														\
public:																	\
	PREFIX ## Test ## FUNC() {											\
		init();															\
		run();															\
	}																	\
	~PREFIX ## Test ## FUNC() {};										\
	void run() {														\
		TEST_RUN_ ## TYPE(PREFIX,FUNC);									\
	}																	\
																		\
private:																\
																		\
	TEST_DEFINE_ ## TYPE(PREFIX , FUNC)									\
																		\
																		\
};		


#define RUN(PREFIX,FUNC,VAL)   PREFIX ## Test ## FUNC VAL;

#define BINARY_RUN(FUNC,VAL)    RUN(BINARY,FUNC,VAL)
#define SET_RUN(FUNC,VAL)    RUN(SET,FUNC,VAL)
#define GET_RUN(FUNC,VAL)    RUN(GET,FUNC,VAL)
#define LOAD_RUN(FUNC,VAL)    RUN(LOAD,FUNC,VAL)
#define STORE_RUN(FUNC,VAL)    RUN(STORE,FUNC,VAL)
#define ZE_RUN(FUNC,VAL)    RUN(ZE,FUNC,VAL)
#define SHUFFLEEPI32_RUN(FUNC,VAL)    RUN(SHUFFLEEPI32,FUNC,VAL)
#define SHIFFT_IMM_RUN(FUNC,VAL)    RUN(SHIFFT_IMM,FUNC,VAL)
#define SHUFFLEPS(FUNC,VAL)    RUN(SHUFFLEPS,FUNC,VAL)
#define SI_RUN(FUNC,VAL)    RUN(SI,FUNC,VAL)

TEST(BINARY,_mm_max_epu8,INTEGER)
TEST(BINARY,_mm_max_epi16,INTEGER)
TEST(BINARY,_mm_max_ps,FLOAT)
TEST(BINARY,_mm_min_epu8,INTEGER)
TEST(BINARY,_mm_min_epi16,INTEGER)
TEST(BINARY,_mm_min_ps,FLOAT)
TEST(BINARY,_mm_add_epi16,INTEGER)
TEST(BINARY,_mm_sub_epi16,INTEGER)
TEST(BINARY,_mm_adds_epu16,INTEGER)

//TEST(SET,_mm_cvtsi32_si128,INTEGER)
//TEST(GET,_mm_cvtsi128_si32,INTEGER)
//TEST(LOAD,_mm_loadl_epi64,INTEGER)
//TEST(STORE,_mm_storel_epi64,INTEGER)
//TEST(LOAD,_mm_load_ss,FLOAT)
//TEST(STORE,_mm_store_ss,FLOAT)

//TEST(SET,_mm_set1_epi8,INTEGER)
TEST(BINARY,_mm_xor_si128,INTEGER)
TEST(BINARY,_mm_cmpgt_epi8,INTEGER)
TEST(BINARY,_mm_and_si128,INTEGER)
TEST(BINARY,_mm_andnot_si128,INTEGER)
TEST(BINARY,_mm_subs_epu8,INTEGER)
//TEST(SET,_mm_set1_epi16,INTEGER)
TEST(BINARY,_mm_cmpgt_epi16,INTEGER)
//TEST(SET,_mm_set1_ps,FLOAT)
TEST(BINARY,_mm_cmpgt_ps,FLOAT)
TEST(BINARY,_mm_and_ps,FLOAT)
TEST(BINARY,_mm_cmple_ps,FLOAT)

//TEST(ZE,_mm_setzero_si128,INTEGER)
//TEST(SHUFFLEEPI32,_mm_shuffle_epi32,INTEGER)
TEST(BINARY,_mm_packs_epi32,INTEGER)
TEST(BINARY,_mm_unpackhi_epi8,INTEGER)
TEST(BINARY,_mm_unpacklo_epi8,INTEGER)
TEST(BINARY,_mm_mulhi_epi16,INTEGER)
TEST(BINARY,_mm_mullo_epi16,INTEGER)
TEST(BINARY,_mm_unpacklo_epi16,INTEGER)
TEST(BINARY,_mm_add_epi32,INTEGER)
TEST(BINARY,_mm_unpackhi_epi16,INTEGER)
//TEST(SHIFFT_IMM,_mm_srai_epi32,INTEGER)
//TEST(SHUFFLEPS,_mm_shuffle_ps,FLOAT)
//TEST(SI,_mm_cvtepi32_ps,I2F)

int main()
{
	BINARY_RUN(_mm_max_epu8,t0);
	BINARY_RUN(_mm_max_epi16,t1);
	BINARY_RUN(_mm_max_ps,t2);
	BINARY_RUN(_mm_min_epu8,t3);
	BINARY_RUN(_mm_min_epi16,t4);
	BINARY_RUN(_mm_min_ps,t5);
	BINARY_RUN(_mm_add_epi16,t6);
	BINARY_RUN(_mm_sub_epi16,t7);
	BINARY_RUN(_mm_adds_epu16,t8);
	//
	//	SET_RUN(_mm_cvtsi32_si128,t9);
	//	GET_RUN(_mm_cvtsi128_si32,t10);
	//	LOAD_RUN(_mm_loadl_epi64,t11);
	//	STORE_RUN(_mm_storel_epi64,t12);
	//	LOAD_RUN(_mm_load_ss,t13);
	//	STORE_RUN(_mm_store_ss,t14);

	//	SET_RUN(_mm_set1_epi8,t15);
	BINARY_RUN(_mm_xor_si128,t16);
	BINARY_RUN(_mm_cmpgt_epi8,t17);
	BINARY_RUN(_mm_and_si128,t18);
	BINARY_RUN(_mm_andnot_si128,t19);
	BINARY_RUN(_mm_subs_epu8,t20);
	//	SET_RUN(_mm_set1_epi16,t21);
	BINARY_RUN(_mm_cmpgt_epi16,t22);

	//	SET_RUN(_mm_set1_ps,t23);
	BINARY_RUN(_mm_cmpgt_ps,t24);
	BINARY_RUN(_mm_and_ps,t25);
	BINARY_RUN(_mm_cmple_ps,t26);

	//	ZE_RUN(_mm_setzero_si128,t27);
	//	SHUFFLEEPI32_RUN(_mm_shuffle_epi32,t28);
	BINARY_RUN(_mm_packs_epi32,t29);
	BINARY_RUN(_mm_unpackhi_epi8,t30);
	BINARY_RUN(_mm_unpacklo_epi8,t31);
	BINARY_RUN(_mm_mulhi_epi16,t32);
	BINARY_RUN(_mm_mullo_epi16,t33);
	BINARY_RUN(_mm_unpacklo_epi16,t34);
	BINARY_RUN(_mm_add_epi32, t35);
	//SHIFFT_IMM_RUN(_mm_srai_epi32, t36);
	//SI_RUN(_mm_cvtepi32_ps, t37);

	return 0;

}



