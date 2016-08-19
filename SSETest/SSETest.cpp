#include <iostream>
#include <xmmintrin.h>
#include<chrono>
#define ARRAY_SIZE 30000

void ComputeArrayCPlusPlus(
	float* pArray1,                   // [in] first source array
	float* pArray2,                   // [in] second source array
	float* pResult,                   // [out] result array
	int nSize)                        // [in] size of all arrays
{

	int i;

	float* pSource1 = pArray1;
	float* pSource2 = pArray2;
	float* pDest = pResult;

	for (i = 0; i < nSize; i++)
	{
		*pDest = (float)sqrt((*pSource1) * (*pSource1) + (*pSource2)
			* (*pSource2)) + 0.5f;

		pSource1++;
		pSource2++;
		pDest++;
	}
}

void ComputeArrayCPlusPlusSSE(
	float* pArray1,                   // [in] first source array
	float* pArray2,                   // [in] second source array
	float* pResult,                   // [out] result array
	int nSize)                        // [in] size of all arrays
{
	int nLoop = nSize / 4;

	__m128 m1, m2, m3, m4;

	__m128* pSrc1 = (__m128*) pArray1;
	__m128* pSrc2 = (__m128*) pArray2;
	__m128* pDest = (__m128*) pResult;


	__m128 m0_5 = _mm_set_ps1(0.5f);        // m0_5[0, 1, 2, 3] = 0.5

	for (int i = 0; i < nLoop; i++)
	{
		m1 = _mm_mul_ps(*pSrc1, *pSrc1);        // m1 = *pSrc1 * *pSrc1
		m2 = _mm_mul_ps(*pSrc2, *pSrc2);        // m2 = *pSrc2 * *pSrc2
		m3 = _mm_add_ps(m1, m2);                // m3 = m1 + m2
		m4 = _mm_sqrt_ps(m3);                   // m4 = sqrt(m3)
		*pDest = _mm_add_ps(m4, m0_5);          // *pDest = m4 + 0.5

		pSrc1++;
		pSrc2++;
		pDest++;
	}
}


int main(int *argc, char * argv[])
{
	__declspec(align(16)) float m_fArray1[ARRAY_SIZE];
	__declspec(align(16)) float m_fArray2[ARRAY_SIZE];
	__declspec(align(16)) float m_fArray3[ARRAY_SIZE];
	//m_fArray = (float *)_aligned_malloc(ARRAY_SIZE*sizeof(float), 16);
	//_aligned_free(m_fArray);
	std::chrono::steady_clock::time_point s, e;
	for (size_t i = 0; i < ARRAY_SIZE; i++)
	{
		m_fArray1[i] = sin(i);
		m_fArray2[i] = cos(i);
	}

	s = std::chrono::steady_clock::now();
	ComputeArrayCPlusPlus(m_fArray1, m_fArray2, m_fArray3, ARRAY_SIZE);
	e = std::chrono::steady_clock::now();

	std::cout << "normal time cost = " << (e - s).count() << " s" << std::endl;

	s = std::chrono::steady_clock::now();
	ComputeArrayCPlusPlusSSE(m_fArray1, m_fArray2, m_fArray3, ARRAY_SIZE);
	e = std::chrono::steady_clock::now();

	std::cout << "ssecpt time cost = " << (e - s).count() << " s" << std::endl;

	return 1;
}