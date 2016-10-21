// =====================================================================================
// 
//       Filename:  sse2neon.h
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  2016年10月14日 21时58分08秒
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Su Junjie (USTC), jjsu@email.ustc.edu.cn
//        Company:  
// 
// =====================================================================================

#ifndef SSE2NEON_H
#define SSE2NEON_H

#define ENABLE_CPP_VERSION 0
#define GCC 1

#if GCC
#define INLINE					inline __attribute__((always_inline))
#else
#define INLINE					inline
#endif

#include <arm_neon.h>


typedef float32x4_t __m128;
typedef int32x4_t __m128i;

/***************************************************************************
 *                max and min
 ***************************************************************************/

INLINE __m128i _mm_max_epu8 (__m128i a, __m128i b)
{
	return (__m128i)vmaxq_u8((uint8x16_t) a, (uint8x16_t) b);
}

INLINE __m128i _mm_max_epi16 (__m128i a, __m128i b)
{
	return (__m128i)vmaxq_s16((int16x8_t) a, (int16x8_t) b);
}

INLINE __m128 _mm_max_ps(__m128 a, __m128 b)
{
	return vmaxq_f32(a, b);
}

INLINE __m128i _mm_min_epu8 (__m128i a, __m128i b)
{
	return (__m128i)vminq_u8((uint8x16_t) a, (uint8x16_t) b);
}

INLINE __m128i _mm_min_epi16(__m128i a, __m128i b)
{
	return (__m128i)vminq_s16((int16x8_t)a, (int16x8_t)b);
}

INLINE __m128 _mm_min_ps(__m128 a, __m128 b)
{
	return vminq_f32(a, b);
}

/***************************************************************************
 *                add and sub
 ***************************************************************************/
INLINE __m128i _mm_add_epi16(__m128i a, __m128i b)
{
	return (__m128i)vaddq_s16((int16x8_t)a, (int16x8_t)b);
}

INLINE __m128i _mm_sub_epi16 (__m128i a, __m128i b)
{
	return (__m128i)vsubq_s16((int16x8_t) a, (int16x8_t) b);
}

INLINE __m128i _mm_adds_epu16 (__m128i a, __m128i b)
{
	return (__m128i)vqaddq_u16((uint16x8_t) a, (uint16x8_t) b);
}

INLINE __m128i _mm_subs_epu16 (__m128i a, __m128i b)
{
	return (__m128i)vqsubq_u16((uint16x8_t) a, (uint16x8_t) b);
}



/***************************************************************************
 *                load and store
 ***************************************************************************/

INLINE __m128i _mm_load_si128(const __m128i *p)
{
	return vld1q_s32((int32_t *)p);
}
INLINE void _mm_store_si128(__m128i *p, __m128i a ) 
{
	vst1q_s32((int32_t*) p,a);
}

INLINE __m128 _mm_load_ps(const float * p)
{
	return vld1q_f32(p);
}

INLINE void _mm_store_ps(float *p, __m128 a)
{
	vst1q_f32(p, a);
}

#define _mm_loadu_si128 _mm_load_si128
#define _mm_storeu_si128 _mm_store_si128

#define _mm_loadu_ps _mm_load_ps
#define _mm_storeu_ps _mm_store_ps

INLINE __m128i _mm_loadl_epi64(__m128i const*p)
{
	/* Load the lower 64 bits of the value pointed to by p into the lower 64 bits of the result, zeroing the upper 64 bits of the result. */
	return vcombine_s32(vld1_s32((int32_t const *)p),vcreate_s32(0));
}

INLINE void _mm_storel_epi64(__m128i* a, __m128i b)
{
	/* Reads the lower 64 bits of b and stores them into the lower 64 bits of a. */
	//
	//*a = (__m128i)vsetq_lane_s64((int64_t)vget_low_s32(b), *(int64x2_t*)a, 0);
	//vst1_s64( (int64_t *) a, vget_low_s64((int64x2_t)b));
	vst1_s32( (int32_t *) a, vget_low_s32((int32x4_t)b));
}

INLINE __m128 _mm_load_ss(const float * p)
{
	/* Loads an single-precision, floating-point value into the low word and clears the upper three words. */
	__m128 result = vdupq_n_f32(0);
	return vsetq_lane_f32(*p, result, 0);
}

INLINE void _mm_store_ss(float *p, __m128 a)
{
	/* Stores the lower single-precision, floating-point value. */
	vst1q_lane_f32(p, a, 0);
}
/***************************************************************************
 *                SET 
 ***************************************************************************/
INLINE __m128i _mm_cvtsi32_si128(int a)
{
	/* 
	 Moves 32-bit integer a to the least significant 32 bits of an __m128 object, zero extending the upper bits.
	 * */
	__m128i result = vdupq_n_s32(0);
	return vsetq_lane_s32(a, result, 0);
}

/***************************************************************************
 *                GET 
 ***************************************************************************/
INLINE int _mm_cvtsi128_si32(__m128i a)
{
	/* Moves the least significant 32 bits of a to a 32-bit integer. */
	return vgetq_lane_s32(a, 0);
}

#endif
