#include <iostream>
#include <Windows.h>
#include <string>
#include <ctime>

class AdrClass
{
public:
	//Definition der Methode
	//Konstruktor
	AdrClass(char* Value, DWORD BaseAdress, int OffsetNumber, DWORD* Offsets);

	//Destruktor
	~AdrClass();

	//Get Methode
	DWORD GetClassBaseAdress();
	DWORD* GetClassOffsets();
	char* GetClassValue();

private:
	//Deffinition der Attribute
	DWORD ClassBaseAdress; //Hauptadresse des speichers
	DWORD* ClassOffset; //Offsets array um beschreibbare adreessen zu finden
	char ClassValue[]; //eingesetzer wert

};


AdrClass::AdrClass(char* Value, DWORD BaseAdress, int OffsetNumber, DWORD* Offsets)
{
	ClassOffset = new DWORD[OffsetNumber];
	AdrClass::ClassBaseAdress = BaseAdress;
	for (int i = 0; i < OffsetNumber; i++)
	{
		AdrClass::ClassOffset[i] = Offsets[i];
	}

	strcpy(AdrClass::ClassValue, Value);
}

//Destruktor Definition
AdrClass::~AdrClass()
{
	delete[] ClassOffset;
}

//Get Methoden
DWORD AdrClass::GetClassBaseAdress()
{
	return AdrClass::ClassBaseAdress;
}

DWORD* AdrClass::GetClassOffsets()
{
	return AdrClass::ClassOffset;
}

char* AdrClass::GetClassValue()
{
	return AdrClass::ClassValue;
}