// =====================================================================================
// 
//       Filename:  gen_input.cc
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  2016年10月19日 09时08分59秒
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Su Junjie (USTC), jjsu@email.ustc.edu.cn
//        Company:  
// 
// =====================================================================================

#include <fstream>
#include <cstdlib>
#include <ctime>

int main()
{
	srand(time(0));

	std::ofstream out("input");

	for(int j=0;j<2*64;j++)
	{
		for(int i=0;i<32;i++)
		{
			int x = rand()%256;
			out<<x<<" ";
		}
		out<<"\n";
	}
}

