//DatabaseLibrary.h - Contains declaration of Function class  
#pragma once  

#ifdef DATABASELIBRARY_EXPORTS  
#define DATABASELIBRARY_API __declspec(dllexport)   
#else  
#define DATABASELIBRARY_API __declspec(dllimport)   
#endif  

namespace DatabaseLibrary
{
	// This class is exported from the MathLibrary.dll  
	class Functions
	{
	public:
		// Returns a + b  
		static DATABASELIBRARY_API double Add(double a, double b);
	};
}