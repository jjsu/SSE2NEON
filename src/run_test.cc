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
#include <string>
#include <cstring>

#ifdef __GNUC__                                               
#  define CV_DECL_ALIGNED(x) __attribute__ ((aligned (x)))    
#elif defined _MSC_VER                                        
#  define CV_DECL_ALIGNED(x) __declspec(align(x))             
#else                                                         
#  define CV_DECL_ALIGNED(x)                                  
#endif                                                        

#ifdef ARM
#define DESKTOP 0
#include "sse2neon.h"
#define INPUT "/data/input"
#else
#define DESKTOP 1
#include <xmmintrin.h>
//#include <emmintrin.h>
#include <pmmintrin.h>
#include <smmintrin.h>
#define INPUT "input"
#endif




#define SET_NUM 73

#define SET_PS_Z 5.4
#define SET_PS_Y 7.7
#define SET_PS_X 2.3
#define SET_PS_W 9.4

#define SET_EPI_W0 4
#define SET_EPI_W1 5
#define SET_EPI_W2 2
#define SET_EPI_W3 1
#define SET_EPI_W4 2
#define SET_EPI_W5 9
#define SET_EPI_W6 7
#define SET_EPI_W7 5

#define __SHUFFLE__(FUNC,SD_TYPE,VERSION)	\
	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 0, 0, 0, 0);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 0, 0, 0, 1);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 0, 0, 0, 2);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 0, 0, 0, 3);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 0, 0, 1, 0);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 0, 0, 1, 1);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 0, 0, 1, 2);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 0, 0, 1, 3);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 0, 0, 2, 0);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 0, 0, 2, 1);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 0, 0, 2, 2);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 0, 0, 2, 3);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 0, 0, 3, 0);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 0, 0, 3, 1);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 0, 0, 3, 2);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 0, 0, 3, 3);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 0, 1, 0, 0);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 0, 1, 0, 1);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 0, 1, 0, 2);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 0, 1, 0, 3);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 0, 1, 1, 0);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 0, 1, 1, 1);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 0, 1, 1, 2);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 0, 1, 1, 3);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 0, 1, 2, 0);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 0, 1, 2, 1);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 0, 1, 2, 2);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 0, 1, 2, 3);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 0, 1, 3, 0);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 0, 1, 3, 1);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 0, 1, 3, 2);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 0, 1, 3, 3);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 0, 2, 0, 0);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 0, 2, 0, 1);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 0, 2, 0, 2);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 0, 2, 0, 3);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 0, 2, 1, 0);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 0, 2, 1, 1);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 0, 2, 1, 2);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 0, 2, 1, 3);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 0, 2, 2, 0);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 0, 2, 2, 1);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 0, 2, 2, 2);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 0, 2, 2, 3);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 0, 2, 3, 0);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 0, 2, 3, 1);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 0, 2, 3, 2);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 0, 2, 3, 3);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 0, 3, 0, 0);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 0, 3, 0, 1);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 0, 3, 0, 2);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 0, 3, 0, 3);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 0, 3, 1, 0);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 0, 3, 1, 1);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 0, 3, 1, 2);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 0, 3, 1, 3);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 0, 3, 2, 0);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 0, 3, 2, 1);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 0, 3, 2, 2);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 0, 3, 2, 3);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 0, 3, 3, 0);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 0, 3, 3, 1);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 0, 3, 3, 2);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 0, 3, 3, 3);	\
	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 1, 0, 0, 0);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 1, 0, 0, 1);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 1, 0, 0, 2);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 1, 0, 0, 3);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 1, 0, 1, 0);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 1, 0, 1, 1);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 1, 0, 1, 2);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 1, 0, 1, 3);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 1, 0, 2, 0);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 1, 0, 2, 1);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 1, 0, 2, 2);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 1, 0, 2, 3);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 1, 0, 3, 0);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 1, 0, 3, 1);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 1, 0, 3, 2);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 1, 0, 3, 3);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 1, 1, 0, 0);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 1, 1, 0, 1);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 1, 1, 0, 2);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 1, 1, 0, 3);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 1, 1, 1, 0);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 1, 1, 1, 1);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 1, 1, 1, 2);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 1, 1, 1, 3);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 1, 1, 2, 0);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 1, 1, 2, 1);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 1, 1, 2, 2);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 1, 1, 2, 3);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 1, 1, 3, 0);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 1, 1, 3, 1);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 1, 1, 3, 2);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 1, 1, 3, 3);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 1, 2, 0, 0);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 1, 2, 0, 1);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 1, 2, 0, 2);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 1, 2, 0, 3);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 1, 2, 1, 0);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 1, 2, 1, 1);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 1, 2, 1, 2);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 1, 2, 1, 3);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 1, 2, 2, 0);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 1, 2, 2, 1);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 1, 2, 2, 2);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 1, 2, 2, 3);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 1, 2, 3, 0);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 1, 2, 3, 1);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 1, 2, 3, 2);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 1, 2, 3, 3);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 1, 3, 0, 0);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 1, 3, 0, 1);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 1, 3, 0, 2);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 1, 3, 0, 3);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 1, 3, 1, 0);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 1, 3, 1, 1);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 1, 3, 1, 2);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 1, 3, 1, 3);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 1, 3, 2, 0);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 1, 3, 2, 1);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 1, 3, 2, 2);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 1, 3, 2, 3);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 1, 3, 3, 0);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 1, 3, 3, 1);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 1, 3, 3, 2);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 1, 3, 3, 3);	\
	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 2, 0, 0, 0);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 2, 0, 0, 1);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 2, 0, 0, 2);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 2, 0, 0, 3);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 2, 0, 1, 0);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 2, 0, 1, 1);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 2, 0, 1, 2);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 2, 0, 1, 3);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 2, 0, 2, 0);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 2, 0, 2, 1);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 2, 0, 2, 2);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 2, 0, 2, 3);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 2, 0, 3, 0);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 2, 0, 3, 1);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 2, 0, 3, 2);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 2, 0, 3, 3);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 2, 1, 0, 0);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 2, 1, 0, 1);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 2, 1, 0, 2);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 2, 1, 0, 3);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 2, 1, 1, 0);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 2, 1, 1, 1);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 2, 1, 1, 2);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 2, 1, 1, 3);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 2, 1, 2, 0);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 2, 1, 2, 1);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 2, 1, 2, 2);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 2, 1, 2, 3);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 2, 1, 3, 0);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 2, 1, 3, 1);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 2, 1, 3, 2);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 2, 1, 3, 3);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 2, 2, 0, 0);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 2, 2, 0, 1);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 2, 2, 0, 2);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 2, 2, 0, 3);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 2, 2, 1, 0);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 2, 2, 1, 1);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 2, 2, 1, 2);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 2, 2, 1, 3);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 2, 2, 2, 0);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 2, 2, 2, 1);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 2, 2, 2, 2);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 2, 2, 2, 3);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 2, 2, 3, 0);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 2, 2, 3, 1);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 2, 2, 3, 2);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 2, 2, 3, 3);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 2, 3, 0, 0);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 2, 3, 0, 1);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 2, 3, 0, 2);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 2, 3, 0, 3);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 2, 3, 1, 0);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 2, 3, 1, 1);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 2, 3, 1, 2);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 2, 3, 1, 3);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 2, 3, 2, 0);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 2, 3, 2, 1);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 2, 3, 2, 2);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 2, 3, 2, 3);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 2, 3, 3, 0);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 2, 3, 3, 1);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 2, 3, 3, 2);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 2, 3, 3, 3);	\
	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 3, 0, 0, 0);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 3, 0, 0, 1);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 3, 0, 0, 2);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 3, 0, 0, 3);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 3, 0, 1, 0);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 3, 0, 1, 1);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 3, 0, 1, 2);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 3, 0, 1, 3);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 3, 0, 2, 0);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 3, 0, 2, 1);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 3, 0, 2, 2);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 3, 0, 2, 3);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 3, 0, 3, 0);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 3, 0, 3, 1);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 3, 0, 3, 2);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 3, 0, 3, 3);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 3, 1, 0, 0);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 3, 1, 0, 1);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 3, 1, 0, 2);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 3, 1, 0, 3);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 3, 1, 1, 0);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 3, 1, 1, 1);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 3, 1, 1, 2);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 3, 1, 1, 3);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 3, 1, 2, 0);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 3, 1, 2, 1);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 3, 1, 2, 2);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 3, 1, 2, 3);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 3, 1, 3, 0);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 3, 1, 3, 1);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 3, 1, 3, 2);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 3, 1, 3, 3);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 3, 2, 0, 0);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 3, 2, 0, 1);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 3, 2, 0, 2);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 3, 2, 0, 3);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 3, 2, 1, 0);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 3, 2, 1, 1);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 3, 2, 1, 2);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 3, 2, 1, 3);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 3, 2, 2, 0);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 3, 2, 2, 1);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 3, 2, 2, 2);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 3, 2, 2, 3);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 3, 2, 3, 0);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 3, 2, 3, 1);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 3, 2, 3, 2);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 3, 2, 3, 3);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 3, 3, 0, 0);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 3, 3, 0, 1);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 3, 3, 0, 2);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 3, 3, 0, 3);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 3, 3, 1, 0);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 3, 3, 1, 1);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 3, 3, 1, 2);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 3, 3, 1, 3);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 3, 3, 2, 0);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 3, 3, 2, 1);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 3, 3, 2, 2);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 3, 3, 2, 3);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 3, 3, 3, 0);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 3, 3, 3, 1);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 3, 3, 3, 2);	SHUFFLE_ ## VERSION(FUNC, SD_TYPE, 3, 3, 3, 3);

#define SHIFT_A_IMM(FUNC,SD_TYPE,IMM)					\
	t = FUNC(r0, IMM);									\
	if (k == 0)											\
		STORE_ ## SD_TYPE(c, t);						\
	else												\
		STOREU_ ## SD_TYPE(c,t);						\
	print("\ta        ", a, N);							\
	print("\tc=OP(a,count)", c, N);						\

#define	SHIFT_0_TO_15(FUNC, SD_TYPE)	\
	SHIFT_A_IMM (FUNC, SD_TYPE, 0  );	SHIFT_A_IMM (FUNC, SD_TYPE, 1  );	SHIFT_A_IMM (FUNC, SD_TYPE, 2  );	SHIFT_A_IMM (FUNC, SD_TYPE, 3  );	SHIFT_A_IMM (FUNC, SD_TYPE, 4  );	SHIFT_A_IMM (FUNC, SD_TYPE, 5  );	SHIFT_A_IMM (FUNC, SD_TYPE, 6  );	SHIFT_A_IMM (FUNC, SD_TYPE, 7  );	SHIFT_A_IMM (FUNC, SD_TYPE, 8  );	SHIFT_A_IMM (FUNC, SD_TYPE, 9  );	SHIFT_A_IMM (FUNC, SD_TYPE, 10 );	SHIFT_A_IMM (FUNC, SD_TYPE, 11 );	SHIFT_A_IMM (FUNC, SD_TYPE, 12 );	SHIFT_A_IMM (FUNC, SD_TYPE, 13 );	SHIFT_A_IMM (FUNC, SD_TYPE, 14 );	SHIFT_A_IMM (FUNC, SD_TYPE, 15 );

#define	SHIFT_1_TO_15(FUNC, SD_TYPE)	\
	SHIFT_A_IMM (FUNC, SD_TYPE, 1  );	SHIFT_A_IMM (FUNC, SD_TYPE, 2  );	SHIFT_A_IMM (FUNC, SD_TYPE, 3  );	SHIFT_A_IMM (FUNC, SD_TYPE, 4  );	SHIFT_A_IMM (FUNC, SD_TYPE, 5  );	SHIFT_A_IMM (FUNC, SD_TYPE, 6  );	SHIFT_A_IMM (FUNC, SD_TYPE, 7  );	SHIFT_A_IMM (FUNC, SD_TYPE, 8  );	SHIFT_A_IMM (FUNC, SD_TYPE, 9  );	SHIFT_A_IMM (FUNC, SD_TYPE, 10 );	SHIFT_A_IMM (FUNC, SD_TYPE, 11 );	SHIFT_A_IMM (FUNC, SD_TYPE, 12 );	SHIFT_A_IMM (FUNC, SD_TYPE, 13 );	SHIFT_A_IMM (FUNC, SD_TYPE, 14 );	SHIFT_A_IMM (FUNC, SD_TYPE, 15 );

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

#define LOAD_FUNC_FLOAT(FUNC,X) FUNC((const float*)X)
#define LOAD_FUNC_INTEGER(FUNC,X) FUNC((const __m128i*)X)
#define STORE_FUNC_FLOAT(FUNC,X,Y) FUNC((float*)X,Y)
#define STORE_FUNC_INTEGER(FUNC,X,Y) FUNC((__m128i*)X,Y)

#define LOAD_M64(X) LOAD_FLOAT(X)
#define LOADU_M64(X) LOADU_FLOAT(X)
#define STORE_FUNC_M64(FUNC,X,Y) FUNC((__m64*)X,Y)
#define LOAD_FUNC_M64(FUNC,X,Y) FUNC(X,(__m64 const*)Y)

#define NULLARY_FOR_LOOP(FUNC,TYPE,LD_TYPE,SD_TYPE,VAL_TYPE,RESULT_TYPE)	\
		for (size_t k = 0; k < N; k++)										\
		{																	\
			std::cout << "iter." << count++ << " : " << std::endl;			\
			TYPE* c = (TYPE*)(buf2)+k;										\
			std::cout << "\t(c) offset : ("									\
			<< k << ")" << std::endl;										\
			RESULT_TYPE  t;													\
																			\
			t = FUNC ();													\
																			\
			if (k==0)														\
				STORE_ ## SD_TYPE(c,t);										\
			else															\
				STOREU_ ## SD_TYPE(c,t);									\
			print("\tc=OP()", c, N);										\
		}																	\

#define UNARY_FOR_LOOP(FUNC,TYPE,LD_TYPE,SD_TYPE,VAL_TYPE,RESULT_TYPE)	\
for (size_t i = 0; i < N; i++)											\
	for (size_t k = 0; k < N; k++)										\
	{																	\
		std::cout << "iter." << count++ << " : " << std::endl;			\
		TYPE* a = (TYPE*)(buf0)+i;										\
		TYPE* c = (TYPE*)(buf2)+k;										\
		std::cout << "\t(a,c) offset : ("								\
		<< i << ","   													\
		<< k << ")" << std::endl;										\
		VAL_TYPE r0;													\
		RESULT_TYPE  t;													\
																		\
		if (i == 0)														\
			r0 = LOAD_ ## LD_TYPE(a);									\
		else															\
			r0 = LOADU_ ## LD_TYPE(a);									\
																		\
		t = FUNC (r0);													\
																		\
		if (k==0)														\
			STORE_ ## SD_TYPE(c,t);										\
		else															\
			STOREU_ ## SD_TYPE(c,t);									\
		print("\ta        ", a, N);										\
		print("\tc=OP(a)", c, N);										\
	}																	\


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


/*maybe need unaligned LOAD*/
#define LOAD_FOR_LOOP(FUNC,TYPE,LD_TYPE,SD_TYPE,VAL_TYPE,RESULT_TYPE)	\
		for (size_t k = 0; k < N; k++)									\
		{																\
			std::cout << "iter." << count++ << " : " << std::endl;		\
			TYPE* a = (TYPE*)(buf0);									\
			TYPE* c = (TYPE*)(buf2)+k;									\
			std::cout << "\t(c) offset : ("								\
			<< k << ")" << std::endl;									\
			RESULT_TYPE  t;												\
																		\
			t = LOAD_FUNC_ ## LD_TYPE(FUNC,a);							\
																		\
			if (k==0)													\
				STORE_ ## SD_TYPE(c,t);									\
			else														\
				STOREU_ ## SD_TYPE(c,t);								\
			print("\ta        ", a, N);									\
			print("\tc=OP(a)", c, N);									\
		}																\

/*maybe need unaligned STORE*/
#define STORE_FOR_LOOP(FUNC,TYPE,LD_TYPE,SD_TYPE,VAL_TYPE,RESULT_TYPE)	\
for (size_t i = 0; i < N; i++)											\
		{																\
			std::cout << "iter." << count++ << " : " << std::endl;		\
			TYPE* a = (TYPE*)(buf0)+i;									\
			TYPE* c = (TYPE*)(buf2);									\
			/*disable warning*/											\
			memcpy(buf2,buf1,32);										\
			std::cout << "\t(a) offset : ("								\
			<< i << ")" << std::endl;									\
			VAL_TYPE r0;												\
																		\
			print("\ta        ", a, N);									\
			print("\tc        ", c, N);									\
			if (i == 0)													\
				r0 = LOAD_ ## LD_TYPE(a);								\
			else														\
				r0 = LOADU_ ## LD_TYPE(a);								\
																		\
			STORE_FUNC_ ## SD_TYPE(FUNC,c,r0);							\
																		\
			print("\tc=OP(*c,a)", c, N);								\
		}																\

#define SET_FOR_LOOP(FUNC,TYPE,LD_TYPE,SD_TYPE,VAL_TYPE,RESULT_TYPE)	\
		for (size_t k = 0; k < N; k++)									\
		{																\
			std::cout << "iter." << count++ << " : " << std::endl;		\
			TYPE* c = (TYPE*)(buf2)+k;									\
			std::cout << "\t(c) offset : ("								\
			<< k << ")" << std::endl;									\
			RESULT_TYPE  t;												\
																		\
			t = FUNC (SET_NUM);											\
																		\
			if (k==0)													\
				STORE_ ## SD_TYPE(c,t);									\
			else														\
				STOREU_ ## SD_TYPE(c,t);								\
			print("\tc=OP(SET_NUM)", c, N);								\
		}																\

#define GET_FOR_LOOP(FUNC,TYPE,LD_TYPE,SD_TYPE,VAL_TYPE,RESULT_TYPE)	\
for (size_t i = 0; i < N; i++)											\
		{																\
			std::cout << "iter." << count++ << " : " << std::endl;		\
			/*disable warning*/											\
			memcpy(buf2,buf0,32);										\
			TYPE* a = (TYPE*)(buf2)+i;									\
			std::cout << "\t(a) offset : ("								\
			<< i << ")" << std::endl;									\
			VAL_TYPE r0;												\
																		\
			if (i == 0)													\
				r0 = LOAD_ ## LD_TYPE(a);								\
			else														\
				r0 = LOADU_ ## LD_TYPE(a);								\
																		\
			auto t = FUNC (r0);											\
																		\
			print("\ta        ", a, N);									\
			std::cout<<"\tc=OP(a) "<<t<<std::endl;						\
		}																\

#define SHIFT_EPI32_FOR_LOOP(FUNC,TYPE,LD_TYPE,SD_TYPE,VAL_TYPE,RESULT_TYPE)	\
for (size_t i = 0; i < N; i++)													\
		for (size_t k = 0; k < N; k++)											\
		{																		\
			std::cout << "iter." << count++ << " : " << std::endl;				\
			TYPE* a = (TYPE*)(buf0)+i;											\
			TYPE* c = (TYPE*)(buf2)+k;											\
			std::cout << "\t(a,c) offset : ("									\
			<< i << ","															\
			<< k << ")" << std::endl;											\
			VAL_TYPE r0;														\
			RESULT_TYPE  t;														\
																				\
			if (i == 0)															\
				r0 = LOAD_ ## LD_TYPE(a);										\
			else																\
				r0 = LOADU_ ## LD_TYPE(a);										\
																				\
			for (int count = 0; count <= 32; count++)							\
			{																	\
				t = FUNC (r0,count);											\
																				\
				if (k==0)														\
					STORE_ ## SD_TYPE(c,t);										\
				else															\
					STOREU_ ## SD_TYPE(c,t);									\
																				\
				print("\ta        ", a, N);											\
				print("\tc=OP(a,count)", c, N);										\
			}																	\
		}																		\


#define LOAD_PI_FOR_LOOP(FUNC,TYPE,LD_TYPE,SD_TYPE,VAL_TYPE,RESULT_TYPE)	\
for (size_t i = 0; i < N; i++)											\
		for (size_t k = 0; k < N; k++)									\
		{																\
			std::cout << "iter." << count++ << " : " << std::endl;		\
			TYPE* a = (TYPE*)(buf0)+i;									\
			/*disable warning*/											\
			memcpy(buf2,buf1,32);										\
			TYPE* c = (TYPE*)(buf2)+k;									\
			std::cout << "\t(a,c) offset : ("							\
			<< i << "," 									\
			<< k << ")" << std::endl;									\
			VAL_TYPE r0;											\
			RESULT_TYPE  t;												\
																		\
			if (i == 0)													\
				r0 = LOAD_ ## LD_TYPE(c);								\
			else														\
				r0 = LOADU_ ## LD_TYPE(c);								\
																		\
			t = LOAD_FUNC_ ## LD_TYPE(FUNC,r0,a);							\
																		\
			if (k==0)													\
				STORE_ ## SD_TYPE(c,t);									\
			else														\
				STOREU_ ## SD_TYPE(c,t);								\
			print("\ta        ", a, N);									\
			print("\tc=OP(a,b)", c, N);									\
		}																\




#define SHUFFLE_UNARY(FUNC,SD_TYPE,z,y,x,w)			\
	t = FUNC (r0,_MM_SHUFFLE(z,y,x,w));				\
	if (k==0)										\
		STORE_ ## SD_TYPE(c,t);						\
	else											\
		STOREU_ ## SD_TYPE(c,t);					\
	print("\ta        ", a, N);						\
	std::cout<<"\tc=OP(a,_MM_SHUFFLE("				\
		<<#z<<","<<#y<<","<<#x<<","<<#w<<")";		\
	print("", c, N);								\

#define SHUFFLE_BINARY(FUNC,SD_TYPE,z,y,x,w)		\
	t = FUNC (r0,r1,_MM_SHUFFLE(z,y,x,w));			\
	if (k==0)										\
		STORE_ ## SD_TYPE(c,t);						\
	else											\
		STOREU_ ## SD_TYPE(c,t);					\
	print("\ta        ", a, N);						\
	print("\tb        ", b, N);						\
	std::cout<<"\tc=OP(a,b,_MM_SHUFFLE("			\
		<<#z<<","<<#y<<","<<#x<<","<<#w<<")";		\
	print("", c, N);								\



#define SHUFFLE_A_IMM(FUNC,SD_TYPE) __SHUFFLE__(FUNC,SD_TYPE,UNARY)
#define SHUFFLE_A_B_IMM(FUNC,SD_TYPE) __SHUFFLE__(FUNC,SD_TYPE,BINARY)

#define SHUFFLE_EPI_FOR_LOOP(FUNC,TYPE,LD_TYPE,SD_TYPE,VAL_TYPE,RESULT_TYPE)	\
for (size_t i = 0; i < N; i++)													\
		for (size_t k = 0; k < N; k++)											\
		{																		\
			std::cout << "iter." << count++ << " : " << std::endl;				\
			TYPE* a = (TYPE*)(buf0)+i;											\
			TYPE* c = (TYPE*)(buf2)+k;											\
			std::cout << "\t(a,c) offset : ("									\
			<< i << ","															\
			<< k << ")" << std::endl;											\
			VAL_TYPE r0;														\
			RESULT_TYPE  t;														\
																				\
			if (i == 0)															\
				r0 = LOAD_ ## LD_TYPE(a);										\
			else																\
				r0 = LOADU_ ## LD_TYPE(a);										\
																				\
			SHUFFLE_A_IMM(FUNC,SD_TYPE);										\
		}																		\

#define SHUFFLE_PS_FOR_LOOP(FUNC,TYPE,LD_TYPE,SD_TYPE,VAL_TYPE,RESULT_TYPE)		\
for (size_t i = 0; i < N; i++)													\
	for (size_t j = 0; j < N; j++)												\
		for (size_t k = 0; k < N; k++)											\
		{																		\
			std::cout << "iter." << count++ << " : " << std::endl;				\
			TYPE* a = (TYPE*)(buf0)+i;											\
			TYPE* b = (TYPE*)(buf1)+j;											\
			TYPE* c = (TYPE*)(buf2)+k;											\
			std::cout << "\t(a,b,c) offset : ("									\
			<< i << "," << j << ","												\
			<< k << ")" << std::endl;											\
			VAL_TYPE r0, r1;													\
			RESULT_TYPE  t;														\
																				\
			if (i == 0)															\
				r0 = LOAD_ ## LD_TYPE(a);										\
			else																\
				r0 = LOADU_ ## LD_TYPE(a);										\
																				\
			if (j==0)															\
				r1 =  LOAD_ ## LD_TYPE(b);										\
			else																\
				r1 =  LOADU_ ## LD_TYPE(b);										\
																				\
			SHUFFLE_A_B_IMM(FUNC,SD_TYPE);										\
		}																		\


#define TEST_DEFINE(PREFIX,FUNC,TYPE,LD_TYPE,SD_TYPE,VAL_TYPE,RESULT_TYPE)			\
	void test_ ## FUNC ## _ ## TYPE() {												\
		std:: cout << "function : "<< __FUNCTION__ << std::endl;					\
		const int   N = 16 / sizeof(TYPE);											\
		char CV_DECL_ALIGNED(16)  buf2[32];											\
		int count = 0;																\
		PREFIX ## _FOR_LOOP(FUNC,TYPE,LD_TYPE,SD_TYPE,VAL_TYPE,RESULT_TYPE)			\
	}

#define SET_PS_FOR_LOOP(FUNC,TYPE,LD_TYPE,SD_TYPE,VAL_TYPE,RESULT_TYPE)	\
		for (size_t k = 0; k < N; k++)									\
		{																\
			std::cout << "iter." << count++ << " : " << std::endl;		\
			TYPE* c = (TYPE*)(buf2)+k;									\
			std::cout << "\t(c) offset : ("								\
			<< k << ")" << std::endl;									\
			RESULT_TYPE  t;												\
																		\
			t = FUNC (SET_PS_Z,SET_PS_Y,SET_PS_X,SET_PS_W);				\
			if (k==0)													\
				STORE_ ## SD_TYPE(c,t);									\
			else														\
				STOREU_ ## SD_TYPE(c,t);								\
			print("\tc=OP(SET_NUM)", c, N);								\
		}																\

#define SET_EPI16_FOR_LOOP(FUNC,TYPE,LD_TYPE,SD_TYPE,VAL_TYPE,RESULT_TYPE)	\
		for (size_t k = 0; k < N; k++)									\
		{																\
			std::cout << "iter." << count++ << " : " << std::endl;		\
			TYPE* c = (TYPE*)(buf2)+k;									\
			std::cout << "\t(c) offset : ("								\
			<< k << ")" << std::endl;									\
			RESULT_TYPE  t;												\
																		\
			t = FUNC (SET_EPI_W0,SET_EPI_W1,SET_EPI_W2,SET_EPI_W3,		\
					SET_EPI_W4,SET_EPI_W5,SET_EPI_W6,SET_EPI_W7);				\
			if (k==0)													\
				STORE_ ## SD_TYPE(c,t);									\
			else														\
				STOREU_ ## SD_TYPE(c,t);								\
			print("\tc=OP(SET_NUM)", c, N);								\
		}																\


#define SHIFT_IMM_FOR_LOOP(FUNC,TYPE,LD_TYPE,SD_TYPE,VAL_TYPE,RESULT_TYPE)	\
for (size_t i = 0; i < N; i++)													\
		for (size_t k = 0; k < N; k++)											\
		{																		\
			std::cout << "iter." << count++ << " : " << std::endl;				\
			TYPE* a = (TYPE*)(buf0)+i;											\
			TYPE* c = (TYPE*)(buf2)+k;											\
			std::cout << "\t(a,c) offset : ("									\
			<< i << ","															\
			<< k << ")" << std::endl;											\
			VAL_TYPE r0;														\
			RESULT_TYPE  t;														\
																				\
			if (i == 0)															\
				r0 = LOAD_ ## LD_TYPE(a);										\
			else																\
				r0 = LOADU_ ## LD_TYPE(a);										\
																				\
		/*  	SHIFT_0_TO_15(FUNC,SD_TYPE);		*/								\
			SHIFT_1_TO_15(FUNC,SD_TYPE);										\
		}																		\


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

#define NULLARY_INIT						\
void init()									\
{											\
}											\

#define LOAD_INIT UNARY_INIT
#define STORE_INIT BINARY_INIT
#define SET_INIT NULLARY_INIT
#define GET_INIT UNARY_INIT
#define SHIFT_EPI32_INIT UNARY_INIT
#define SHUFFLE_EPI_INIT UNARY_INIT 
#define SHUFFLE_PS_INIT BINARY_INIT 
#define SET_PS_INIT NULLARY_INIT
#define SHIFT_IMM_INIT UNARY_INIT
#define SET_EPI16_INIT NULLARY_INIT
#define LOAD_PI_INIT BINARY_INIT

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

#define TEST_DEFINE_INT2FLOAT(PREFIX,FUNC)								\
	TEST_DEFINE(PREFIX,FUNC,uint8_t ,INTEGER,FLOAT,__m128i,__m128);		\
	TEST_DEFINE(PREFIX,FUNC,int8_t  ,INTEGER,FLOAT,__m128i,__m128);		\
	TEST_DEFINE(PREFIX,FUNC,uint16_t,INTEGER,FLOAT,__m128i,__m128);		\
	TEST_DEFINE(PREFIX,FUNC,int16_t ,INTEGER,FLOAT,__m128i,__m128);		\
	TEST_DEFINE(PREFIX,FUNC,uint32_t,INTEGER,FLOAT,__m128i,__m128);		\
	TEST_DEFINE(PREFIX,FUNC,int32_t ,INTEGER,FLOAT,__m128i,__m128);		\
	TEST_DEFINE(PREFIX,FUNC,uint64_t,INTEGER,FLOAT,__m128i,__m128);		\
	TEST_DEFINE(PREFIX,FUNC,int64_t ,INTEGER,FLOAT,__m128i,__m128);		\

#define TEST_DEFINE_FLOAT2INT(PREFIX,FUNC)									\
	TEST_DEFINE(PREFIX,FUNC,float ,FLOAT,INTEGER,__m128,__m128i);			\
	TEST_DEFINE(PREFIX,FUNC,double,FLOAT,INTEGER,__m128,__m128i);			\

#define TEST_DEFINE_SD_M64(PREFIX,FUNC)									\
	TEST_DEFINE(PREFIX,FUNC,float ,FLOAT,M64,__m128,__m128);			\
	TEST_DEFINE(PREFIX,FUNC,double,FLOAT,M64,__m128,__m128);			\

#define TEST_DEFINE_LD_M64(PREFIX,FUNC)									\
	TEST_DEFINE(PREFIX,FUNC,float ,M64,FLOAT,__m128,__m128);			\
	TEST_DEFINE(PREFIX,FUNC,double,M64,FLOAT,__m128,__m128);			\

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

#define TEST_RUN_INT2FLOAT	TEST_RUN_INTEGER
#define TEST_RUN_FLOAT2INT	TEST_RUN_FLOAT
#define TEST_RUN_SD_M64	TEST_RUN_FLOAT
#define TEST_RUN_LD_M64	TEST_RUN_FLOAT


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
#define NULLARY_RUN(FUNC,VAL)    RUN(NULLARY,FUNC,VAL)
#define SHUFFLE_EPI_RUN(FUNC,VAL)    RUN(SHUFFLE_EPI,FUNC,VAL)
#define SHIFT_EPI32_RUN(FUNC,VAL)    RUN(SHIFT_EPI32,FUNC,VAL)
#define SHUFFLE_PS_RUN(FUNC,VAL)    RUN(SHUFFLE_PS,FUNC,VAL)
#define UNARY_RUN(FUNC,VAL)    RUN(UNARY,FUNC,VAL)
#define SET_PS_RUN(FUNC,VAL)    RUN(SET_PS,FUNC,VAL)
#define SHIFT_IMM_RUN(FUNC,VAL)    RUN(SHIFT_IMM,FUNC,VAL)
#define SET_EPI16_RUN(FUNC,VAL)    RUN(SET_EPI16,FUNC,VAL)
#define LOAD_PI_RUN(FUNC,VAL)    RUN(LOAD_PI,FUNC,VAL)

TEST(BINARY, _mm_max_epu8, INTEGER)
TEST(BINARY, _mm_max_epi16, INTEGER)
TEST(BINARY, _mm_max_ps, FLOAT)
TEST(BINARY, _mm_min_epu8, INTEGER)
TEST(BINARY, _mm_min_epi16, INTEGER)
TEST(BINARY, _mm_min_ps, FLOAT)
TEST(BINARY, _mm_add_epi16, INTEGER)
TEST(BINARY, _mm_sub_epi16, INTEGER)
TEST(BINARY, _mm_adds_epu16, INTEGER)

TEST(SET, _mm_cvtsi32_si128, INTEGER)
TEST(GET, _mm_cvtsi128_si32, INTEGER)
TEST(LOAD, _mm_loadl_epi64, INTEGER)
TEST(STORE, _mm_storel_epi64, INTEGER)
TEST(LOAD, _mm_load_ss, FLOAT)
TEST(STORE, _mm_store_ss, FLOAT)

TEST(SET, _mm_set1_epi8, INTEGER)
TEST(BINARY, _mm_xor_si128, INTEGER)
TEST(BINARY, _mm_cmpgt_epi8, INTEGER)
TEST(BINARY, _mm_and_si128, INTEGER)
TEST(BINARY, _mm_andnot_si128, INTEGER)
TEST(BINARY, _mm_subs_epu8, INTEGER)
TEST(SET, _mm_set1_epi16, INTEGER)
TEST(BINARY, _mm_cmpgt_epi16, INTEGER)
TEST(SET, _mm_set1_ps, FLOAT)
TEST(BINARY, _mm_cmpgt_ps, FLOAT)
TEST(BINARY, _mm_and_ps, FLOAT)
TEST(BINARY, _mm_cmple_ps, FLOAT)

TEST(NULLARY, _mm_setzero_si128, INTEGER)
TEST(SHUFFLE_EPI, _mm_shuffle_epi32, INTEGER)
TEST(BINARY, _mm_packs_epi32, INTEGER)
TEST(BINARY, _mm_unpackhi_epi8, INTEGER)
TEST(BINARY, _mm_unpacklo_epi8, INTEGER)
TEST(BINARY, _mm_mulhi_epi16, INTEGER)
TEST(BINARY, _mm_mullo_epi16, INTEGER)
TEST(BINARY, _mm_unpacklo_epi16, INTEGER)
TEST(BINARY, _mm_add_epi32, INTEGER)
TEST(BINARY, _mm_unpackhi_epi16, INTEGER)
TEST(SHIFT_EPI32, _mm_srai_epi32, INTEGER)
TEST(SHUFFLE_PS, _mm_shuffle_ps, FLOAT)
TEST(UNARY, _mm_cvtepi32_ps, INT2FLOAT)

TEST(BINARY, _mm_mul_ps, FLOAT)
TEST(BINARY, _mm_add_ps, FLOAT)
///////////////TEST(UNARY, _mm_cvtps_epi32, FLOAT2INT)
TEST(BINARY, _mm_packus_epi16, INTEGER)
TEST(BINARY, _mm_sub_ps, FLOAT)
TEST(BINARY, _mm_sub_epi32, INTEGER)
TEST(NULLARY, _mm_setzero_ps, FLOAT)

TEST(SET, _mm_set1_epi32, INTEGER)
TEST(BINARY, _mm_andnot_ps, FLOAT)
TEST(BINARY, _mm_hadd_ps, FLOAT)
TEST(STORE, _mm_storel_pi, SD_M64)
TEST(SET_PS, _mm_set_ps, FLOAT)
TEST(SHIFT_EPI32, _mm_slli_epi16, INTEGER)
TEST(SHIFT_EPI32, _mm_srli_epi16, INTEGER)
TEST(SHIFT_IMM, _mm_srli_si128, INTEGER)
TEST(SHIFT_IMM, _mm_slli_si128, INTEGER)
TEST(BINARY, _mm_subs_epi16, INTEGER)
TEST(BINARY, _mm_div_ps, FLOAT)
TEST(BINARY, _mm_or_si128, INTEGER)
TEST(BINARY, _mm_adds_epi16, INTEGER)
TEST(BINARY, _mm_unpacklo_epi32, INTEGER)
TEST(BINARY, _mm_unpacklo_ps, FLOAT)
TEST(BINARY, _mm_unpackhi_ps, FLOAT)
TEST(BINARY, _mm_movelh_ps, FLOAT)
TEST(UNARY, _mm_sqrt_ps, FLOAT)
TEST(BINARY, _mm_movehl_ps, FLOAT)

TEST(SHIFT_EPI32, _mm_srai_epi16, INTEGER)
TEST(BINARY, _mm_madd_epi16, INTEGER)
TEST(BINARY, _mm_unpackhi_epi64, INTEGER)
TEST(BINARY, _mm_sad_epu8, INTEGER)
TEST(SET_EPI16, _mm_setr_epi16, INTEGER)
TEST(LOAD_PI, _mm_loadl_pi, LD_M64)

//TEST(BINARY, _mm_min_epi32, INTEGER)
//TEST(BINARY, _mm_max_epi32, INTEGER)

int main()
{
	//	BINARY_RUN(_mm_max_epu8, t0);
	//	BINARY_RUN(_mm_max_epi16, t1);
	//	BINARY_RUN(_mm_min_epu8, t3);
	//	BINARY_RUN(_mm_min_epi16, t4);
//	BINARY_RUN(_mm_add_epi16, t6);
//	//	BINARY_RUN(_mm_sub_epi16, t7);
//	//	BINARY_RUN(_mm_adds_epu16, t8);
//	//
//	//	SET_RUN(_mm_cvtsi32_si128, t9);
//	//	GET_RUN(_mm_cvtsi128_si32, t10);
//	//	LOAD_RUN(_mm_loadl_epi64, t11);
//	STORE_RUN(_mm_storel_epi64, t12);
//	//	LOAD_RUN(_mm_load_ss, t13);
//	//	STORE_RUN(_mm_store_ss, t14);
//	//
//	//	SET_RUN(_mm_set1_epi8, t15);
//	//	BINARY_RUN(_mm_xor_si128, t16);
//	//	BINARY_RUN(_mm_cmpgt_epi8, t17);
//	//	BINARY_RUN(_mm_and_si128, t18);
//	//	BINARY_RUN(_mm_andnot_si128, t19);
//	//	BINARY_RUN(_mm_subs_epu8, t20);
//	//	SET_RUN(_mm_set1_epi16, t21);
//	//	BINARY_RUN(_mm_cmpgt_epi16, t22);
//	//
//		SET_RUN(_mm_set1_ps, t23);
//	//	BINARY_RUN(_mm_cmpgt_ps, t24);
	//	BINARY_RUN(_mm_and_ps, t25);
	//	BINARY_RUN(_mm_cmple_ps, t26);
	//
	//	NULLARY_RUN(_mm_setzero_si128, t27);
	//	SHUFFLE_EPI_RUN(_mm_shuffle_epi32, t28);
//	BINARY_RUN(_mm_packs_epi32, t29);
//	//	BINARY_RUN(_mm_unpackhi_epi8, t30);
//	//	BINARY_RUN(_mm_unpacklo_epi8, t31);
//	//	BINARY_RUN(_mm_mulhi_epi16, t32);
//	//	BINARY_RUN(_mm_mullo_epi16, t33);
//	//	BINARY_RUN(_mm_unpacklo_epi16, t34);
//	BINARY_RUN(_mm_add_epi32, t35);
////	SHIFT_EPI32_RUN(_mm_srai_epi32, t36);
//	//	SHUFFLE_PS_RUN(_mm_shuffle_ps, t38);
//	UNARY_RUN(_mm_cvtepi32_ps, t37);
	//
	//	BINARY_RUN(_mm_add_ps, t40);
	//	BINARY_RUN(_mm_packus_epi16, t42);
	//	BINARY_RUN(_mm_sub_ps, t43);
//	BINARY_RUN(_mm_sub_epi32, t44);
//	//	NULLARY_RUN(_mm_setzero_ps, t45);
//	//
//	SET_RUN(_mm_set1_epi32, t46);
//	BINARY_RUN(_mm_andnot_ps, t47);
//	STORE_RUN(_mm_storel_pi, t49);
//	SET_PS_RUN(_mm_set_ps, t50);
//	SHIFT_EPI32_RUN(_mm_slli_epi16, t51);
//	SHIFT_EPI32_RUN(_mm_srli_epi16, t52);
//	SHIFT_IMM_RUN(_mm_srli_si128, t53);
//	SHIFT_IMM_RUN(_mm_slli_si128, t54);
//	BINARY_RUN(_mm_subs_epi16, t55);
//	BINARY_RUN(_mm_or_si128, t57);
//	BINARY_RUN(_mm_adds_epi16, t58);
//	BINARY_RUN(_mm_unpacklo_epi32, t59);
//	BINARY_RUN(_mm_unpacklo_ps, t60);
//	BINARY_RUN(_mm_unpackhi_ps, t61);
//	BINARY_RUN(_mm_movelh_ps, t62);
//	BINARY_RUN(_mm_movehl_ps, t64);
	
//	SHIFT_EPI32_RUN(_mm_srai_epi16, t65);
//	BINARY_RUN(_mm_madd_epi16, t66);
//	BINARY_RUN(_mm_unpackhi_epi64, t67);
	BINARY_RUN(_mm_sad_epu8, t68);
	SET_EPI16_RUN(_mm_setr_epi16, t69);
	LOAD_PI_RUN(_mm_loadl_pi, t70);

	//	/* precision loss */
	//	BINARY_RUN(_mm_min_ps, t5);
	//	BINARY_RUN(_mm_max_ps, t2);
//	BINARY_RUN(_mm_mul_ps, t39);
/////////////////////	UNARY_RUN(_mm_cvtps_epi32, t41);
	//	BINARY_RUN(_mm_hadd_ps, t48);
	//BINARY_RUN(_mm_div_ps, t56);
//	UNARY_RUN(_mm_sqrt_ps, t63);

//	SSE4
//	BINARY_RUN(_mm_min_epi32, t68);
//	BINARY_RUN(_mm_max_epi32, t69);
	return 0;
}


