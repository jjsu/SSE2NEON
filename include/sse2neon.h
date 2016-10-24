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

//#define ENABLE_CPP_VERSION 0
#define GCC 1

#if GCC
#define INLINE					inline __attribute__((always_inline))
#else
#define INLINE					inline
#endif

#include <arm_neon.h>


typedef float32x4_t __m128;
typedef int32x4_t __m128i;

/*  expands to the following value */
#define _MM_SHUFFLE(z, y, x, w)    ( (z<<6) | (y<<4) | (x<<2) | w )


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
/* Subtracts the 16 unsigned 8-bit integers of b from the 16 unsigned 8-bit integers of a and saturates.
 * r0 := UnsignedSaturate(a0 - b0)
 * r1 := UnsignedSaturate(a1 - b1)
 * ...
 * r15 := UnsignedSaturate(a15 - b15)
 * */
INLINE __m128i _mm_subs_epu8 (__m128i a, __m128i b)
{
	return (__m128i)vqsubq_u8((uint8x16_t) a, (uint8x16_t) b);
}

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

/* Adds the 4 signed or unsigned 32-bit integers in a to the 4 signed or unsigned 32-bit integers in b.
 * r0 := a0 + b0
 * r1 := a1 + b1
 * r2 := a2 + b2
 * r3 := a3 + b3
 * */
INLINE __m128i _mm_add_epi32(__m128i a, __m128i b)
{
	return vaddq_s32(a, b);
}
/***************************************************************************
 *                Multiply
 ***************************************************************************/

/* Multiplies the 8 signed 16-bit integers from a by the 8 signed 16-bit integers from b.
 * r0 := (a0 * b0)[31:16]
 * r1 := (a1 * b1)[31:16]
 * ...
 * r7 := (a7 * b7)[31:16]
 * */
INLINE __m128i _mm_mulhi_epi16(__m128i a, __m128i b)
{
	return (__m128i)vshrq_n_s16(vqdmulhq_s16((int16x8_t)a, (int16x8_t)b), 1);
}

/* Multiplies the 8 signed or unsigned 16-bit integers from a by the 8 signed or unsigned 16-bit integers from b.
 * r0 := (a0 * b0)[15:0]
 * r1 := (a1 * b1)[15:0]
 * ...
 * r7 := (a7 * b7)[15:0]
 * */
INLINE __m128i _mm_mullo_epi16(__m128i a, __m128i b)
{
	return (__m128i)vmulq_s16((int16x8_t)a, (int16x8_t)b);
}

/***************************************************************************
 *                logic
 ***************************************************************************/

/* Computes the bitwise XOR of the 128-bit value in a and the 128-bit value in b. 
 * r := a ^ b
 * */
INLINE __m128i _mm_xor_si128(__m128i a, __m128i b)
{
	return veorq_s32(a, b);
}

/* Computes the bitwise AND of the 128-bit value in b and the bitwise NOT of the 128-bit value in a. 
 * r := (~a) & b
 * */
INLINE __m128i _mm_andnot_si128(__m128i a, __m128i b)
{
	return vbicq_s32(b, a); // *NOTE* argument swap
}


/* Computes the bitwise AND of the 128-bit value in a and the 128-bit value in b.
 * r := a & b
 * */
INLINE __m128i _mm_and_si128(__m128i a, __m128i b)
{
	return vandq_s32(a, b);
}

/* Computes the bitwise AND of the four single-precision, floating-point values of a and b.
 * r0 := a0 & b0
 * r1 := a1 & b1
 * r2 := a2 & b2
 * r3 := a3 & b3
 * */
INLINE __m128 _mm_and_ps(__m128 a, __m128 b)
{
	return (__m128)vandq_s32((__m128i)a, (__m128i)b);
}

/* Compares the 16 signed 8-bit integers in a and the 16 signed 8-bit integers in b for greater than. 
 * r0 := (a0 > b0) ? 0xff : 0x0
 * r1 := (a1 > b1) ? 0xff : 0x0
 * ...
 * r15 := (a15 > b15) ? 0xff : 0x0
 */
INLINE __m128i _mm_cmpgt_epi8 (__m128i a, __m128i b)
{
	return (__m128i)vcgtq_s8((int8x16_t) a,( int8x16_t) b);
}

/* Compares the 8 signed 16-bit integers in a and the 8 signed 16-bit integers in b for greater than.
 * r0 := (a0 > b0) ? 0xffff : 0x0
 * r1 := (a1 > b1) ? 0xffff : 0x0
 * ...
 * r7 := (a7 > b7) ? 0xffff : 0x0
 * */
INLINE __m128i _mm_cmpgt_epi16 (__m128i a, __m128i b)
{
	return (__m128i)vcgtq_s16((int16x8_t) a,( int16x8_t) b);
}

/* Compares for greater than.
 * r0 := (a0 > b0) ? 0xffffffff : 0x0
 * r1 := (a1 > b1) ? 0xffffffff : 0x0
 * r2 := (a2 > b2) ? 0xffffffff : 0x0
 * r3 := (a3 > b3) ? 0xffffffff : 0x0
 * */
INLINE __m128 _mm_cmpgt_ps(__m128 a, __m128 b)
{
	return (__m128)vcgtq_f32(a, b);
}

/* Compares for less than or equal.
 * r0 := (a0 <= b0) ? 0xffffffff : 0x0
 * r1 := (a1 <= b1) ? 0xffffffff : 0x0
 * r2 := (a2 <= b2) ? 0xffffffff : 0x0
 * r3 := (a3 <= b3) ? 0xffffffff : 0x0
 * */
INLINE __m128 _mm_cmple_ps(__m128 a, __m128 b)
{
	return (__m128)vcleq_f32(a, b);
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
/* Moves 32-bit integer a to the least significant 32 bits of an __m128 object, zero extending the upper bits.
 * r0 := a
 * r1 := 0x0 ; r2 := 0x0 ; r3 := 0x0
 * */
INLINE __m128i _mm_cvtsi32_si128(int a)
{
	__m128i result = vdupq_n_s32(0);
	return vsetq_lane_s32(a, result, 0);
}

/* Sets the 16 signed 8-bit integer values to b.
 * r0 := b
 * r1 := b
 * ...
 * r15 := b
 * */
INLINE __m128i _mm_set1_epi8 (char b)
{
	return (__m128i)vdupq_n_s8((int8_t)b);
}

/* Sets the 8 signed 16-bit integer values to w.
 * r0 := w
 * r1 := w
 * ...
 * r7 := w
 * */
INLINE __m128i _mm_set1_epi16 (short w)
{
	return (__m128i)vdupq_n_s16((int16_t)w);
}

/* Sets the four single-precision, floating-point values to w
 * r0 := r1 := r2 := r3 := w 
 * */
INLINE __m128 _mm_set1_ps(float w)
{
	return vdupq_n_f32(w);
}
#define _mm_set_ps1 _mm_set1_ps

//todo ~~~~~~~~~~~~~~~~~~~~~~~~~
/* Shuffles the 4 signed or unsigned 32-bit integers in a as specified by imm. */
INLINE __m128i _mm_shuffle_epi32 (__m128i a, int imm)
{
	switch (imm)
	{
		case 0 : 
			return vdupq_n_s32(vgetq_lane_s32(a, 0)); 
			break;
		default: 

			__m128i ret;
			ret[0] = a[imm & 0x3];
			ret[1] = a[(imm >> 2) & 0x3];
			ret[2] = a[(imm >> 4) & 0x03];
			ret[3] = a[(imm >> 6) & 0x03];
			return ret;
	}
}

//todo ~~~~~~~~~~~~~~~~~~~~~~~~~
/* Selects four specific single-precision, floating-point values from a and b, based on the mask i. */
INLINE __m128 _mm_shuffle_ps(__m128 a , __m128 b , int i )
{
	switch (i)
	{
//		case 0 : 
//			return 
//			break;
		default: 
			__m128 ret;                  
			ret[0] = a[i & 0x3];         
			ret[1] = a[(i >> 2) & 0x3];  
			ret[2] = b[(i >> 4) & 0x03]; 
			ret[3] = b[(i >> 6) & 0x03]; 
			return ret;
	}
}
/***************************************************************************
 *                GET 
 ***************************************************************************/
INLINE int _mm_cvtsi128_si32(__m128i a)
{
	/* Moves the least significant 32 bits of a to a 32-bit integer. */
	return vgetq_lane_s32(a, 0);
}

/* Sets the 128-bit value to zero.
 * r := 0x0
 * */
INLINE __m128i _mm_setzero_si128()
{
	return vdupq_n_s32(0);
}

/***************************************************************************
 *                convert 
 ***************************************************************************/

/* Packs the 8 signed 32-bit integers from a and b into signed 16-bit integers and saturates.
 * r0 := SignedSaturate(a0)
 * r1 := SignedSaturate(a1)
 * r2 := SignedSaturate(a2)
 * r3 := SignedSaturate(a3)
 * r4 := SignedSaturate(b0)
 * r5 := SignedSaturate(b1)
 * r6 := SignedSaturate(b2)
 * r7 := SignedSaturate(b3)
 * */
INLINE __m128i _mm_packs_epi32(__m128i a, __m128i b)
{
	return (__m128i)vcombine_s16(vqmovn_s32(a), vqmovn_s32(b));
}

/* Interleaves the upper 8 signed or unsigned 8-bit integers in a with the upper 8 signed or unsigned 8-bit integers in b.
 * r0 := a8 ; r1 := b8
 * r2 := a9 ; r3 := b9
 * ...
 * r14 := a15 ; r15 := b15
 * */
INLINE __m128i _mm_unpackhi_epi8(__m128i a, __m128i b)
{
	int8x8_t a_h = vget_high_s8((int8x16_t)a);
	int8x8_t b_h = vget_high_s8((int8x16_t)b);
	int8x8x2_t r = vzip_s8(a_h, b_h);
	return (__m128i)vcombine_s8(r.val[0],r.val[1]);
}

/* Interleaves the lower 8 signed or unsigned 8-bit integers in a with the lower 8 signed or unsigned 8-bit integers in b.
 * r0 := a0 ; r1 := b0
 * r2 := a1 ; r3 := b1
 * ...
 * r14 := a7 ; r15 := b7
 * */
INLINE __m128i _mm_unpacklo_epi8(__m128i a, __m128i b)
{
	int8x8_t a_l = vget_low_s8((int8x16_t)a);
	int8x8_t b_l = vget_low_s8((int8x16_t)b);
	int8x8x2_t r = vzip_s8(a_l, b_l);
	return (__m128i)vcombine_s8(r.val[0],r.val[1]);
}

/* Interleaves the upper 4 signed or unsigned 16-bit integers in a with the upper 4 signed or unsigned 16-bit integers in b.
 * r0 := a4 ; r1 := b4
 * r2 := a5 ; r3 := b5
 * r4 := a6 ; r5 := b6
 * r6 := a7 ; r7 := b7
 * */
INLINE __m128i _mm_unpackhi_epi16(__m128i a, __m128i b)
{
	int16x4_t a_h = vget_high_s16((int16x8_t)a);
	int16x4_t b_h = vget_high_s16((int16x8_t)b);
	int16x4x2_t result = vzip_s16(a_h, b_h);
	return (__m128i)vcombine_s16(result.val[0], result.val[1]);
}

/* Interleaves the lower 4 signed or unsigned 16-bit integers in a with the lower 4 signed or unsigned 16-bit integers in b.
 * r0 := a0 ; r1 := b0
 * r2 := a1 ; r3 := b1
 * r4 := a2 ; r5 := b2
 * r6 := a3 ; r7 := b3
 * */
INLINE __m128i _mm_unpacklo_epi16(__m128i a, __m128i b)
{
	int16x4_t a_l = vget_low_s16((int16x8_t)a);
	int16x4_t b_l = vget_low_s16((int16x8_t)b);
	int16x4x2_t result = vzip_s16(a_l, b_l);
	return (__m128i)vcombine_s16(result.val[0], result.val[1]);
}

INLINE __m128i _mm_unpackhi_epi32(__m128i a, __m128i b)
{
	int32x2_t a1 = vget_high_s32(a);
	int32x2_t b1 = vget_high_s32(b);

	int32x2x2_t result = vzip_s32(a1, b1);

	return vcombine_s32(result.val[0], result.val[1]);
}

/***************************************************************************
 *                shift 
 ***************************************************************************/
/* Shifts the 4 signed 32-bit integers in a right by count bits while shifting in the sign bit.
* r0 := a0 >> count
* r1 := a1 >> count
* r2 := a2 >> count
* r3 := a3 >> count
* immediate ,use  #define _mm_srai_epi32(a, imm) vshrq_n_s32(a, imm)
* */
INLINE __m128i _mm_srai_epi32 (__m128i a, int count)
{
//	return vshrq_n_s32(a, count);
//	todo :
//	if immediate
	return vshlq_s32(a, vdupq_n_s32(-count));
}

#endif
