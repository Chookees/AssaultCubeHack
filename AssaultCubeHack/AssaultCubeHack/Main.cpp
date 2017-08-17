#include "AdrClass.h"
//Designed and Coded by Artur.B aka Chookees

//Globale Variablen----------------------------------------------------------------------------------
//LongPointString (Finden des spiels)
LPCSTR LGameWindow = "AssaultCube";

//strings oder texte immer mit std::string deklarieren
std::string GameStatus;

//Funktionsdeklaration
void WriteToMemory(HANDLE hProcHandle);
DWORD FindDmaAddy(int PointerLevel, HANDLE hProcHandle, DWORD Offsets[], DWORD BaseAdress);

bool IsGameda;
bool Updateonnextrun;


//Speichervariablen und Objekte
bool AmmoStatus;

//Ammo Offsets //immer mit 0x*Offset*
//Definiert als Unsigned Long für hohe int zb Hexzahlen
DWORD ammoOffset[] = { 0x384, 0x14, 0x0 };
AdrClass* munition = new AdrClass("\x39\x5", 0x0279A4E0, 3, ammoOffset);

//Leben
bool lebenstatus;

//Life Offsets //immer mit 0x*Offset*
//DWORD = Definiert als Unsigned Long für hohe int zb Hexzahlen
DWORD Healthoffsets[] = { 0xF4 };
AdrClass* health = new AdrClass("\x39\x5", 0x0051E20C, 1, Healthoffsets);

//Granaten
bool NateStatus;

//Nates Offsets //immer mit 0x*Offset*
//DOWRD = Definiert als Unsigned Long für hohe int zb Hexzahlen
DWORD Nateoffsets[] = { 0x154 };
AdrClass* Nate = new AdrClass("\x39\x5", 0x0051E20C, 1, Nateoffsets);

//Speed
bool SpeedStatus;

//Speed Offsets //immer mit 0x*Offset*
//DOWRD = Definiert als Unsigned Long für hohe int zb Hexzahlen
DWORD Speedoffsets[] = { 0x7C };
AdrClass* Speed = new AdrClass("\x05", 0x0051E20C, 1, Speedoffsets);
AdrClass* DefSpeed = new AdrClass("\x01", 0x0051E20C, 1, Speedoffsets);

//Ende Globale Variablen---------------------------------------------------------------------------

int main()
{
	//Main Function Variablen------------------------------------------------

	HWND hGameWindow = NULL;
	//Systemuhr
	int timeSinceLastUpdate = clock();
	int GameDaTimer = clock();
	int oneTimePressTMR = clock();
	//Process ID
	DWORD dwProcId = NULL;
	//Handle zum übernehmen des Porgramms (erlauben in memory zu schreiben)
	HANDLE hProcHandle = NULL;
	//Zeigt an ob beim nächsten Run geupdatet wird die console
	Updateonnextrun = TRUE;
	std::string sAmmoStatus = "Aus";
	std::string sHealthStatus = "Aus";
	std::string sNateStatus = "Aus";
	std::string sSpeedStatus = "Aus";

	//Main Function Variablen Ende---------------------------------------------

	while (!GetAsyncKeyState(VK_F12))
	{
		if (clock() - GameDaTimer > 100)
		{
			GameDaTimer = clock();
			IsGameda = false;
			hGameWindow = FindWindow(NULL, LGameWindow);
			if (hGameWindow)
			{
				//& zeichen damit er es auf die dwProcId überschreibtr
				GetWindowThreadProcessId(hGameWindow, &dwProcId);
				if (dwProcId != 0)
				{
					//Nehme den prozess, öffne ihn; gebe volle rechte; nicht Sync; und die Prozess ID
					hProcHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwProcId);

					if (hProcHandle == INVALID_HANDLE_VALUE || hProcHandle == NULL)
					{
						GameStatus = "Der Prozess konnte nicht geöffnet werden";
					}

					else
					{
						GameStatus = "Hack bereit";
						IsGameda = true;
					}
				}

				else
				{
					GameStatus = "Prozess ID konnte nicht gefunden werden";
				}
			}

			else
			{
				GameStatus = "AssaultCube nicht gefunden";
			}

			if (Updateonnextrun || clock() - timeSinceLastUpdate > 5000)
			{
				//Text der Konsole
				system("cls");
				std::cout << "---------------------------------------------------------------" << std::endl;
				std::cout << "--------------AssaultCube Hack 1.0 by Chookees-----------------" << std::endl;
				std::cout << "---------------------------------------------------------------" << std::endl;
				std::cout << "---------------------------------------------------------------" << std::endl;
				std::cout << "Status des Spiels:" << GameStatus << std::endl << std::endl;
				std::cout << "[NUM1] Infinite Ammo  ||  " << sAmmoStatus << std::endl << std::endl;
				std::cout << "[NUM2] Infinite Health  ||  " << sHealthStatus << std::endl << std::endl;
				std::cout << "[NUM3] Infinite Nates  ||  " << sNateStatus << std::endl << std::endl;
				std::cout << "[NUM4] Speedhack  ||  " << sSpeedStatus << std::endl << std::endl;
				std::cout << "[F12] End Hack  ||  " << std::endl;
				Updateonnextrun = false;
				timeSinceLastUpdate = clock();
			}

			if (IsGameda)
			{
				WriteToMemory(hProcHandle);
			}
		}
		if (clock() - oneTimePressTMR > 400)
		{
			if (IsGameda)
			{
				if (GetAsyncKeyState(VK_NUMPAD1))
				{
					oneTimePressTMR = clock();
					AmmoStatus != AmmoStatus;
					Updateonnextrun = true;

					if (AmmoStatus)sAmmoStatus = "An";
					else sAmmoStatus = "Aus";
				}

				else if (GetAsyncKeyState(VK_NUMPAD2))
				{
					oneTimePressTMR = clock();
					lebenstatus != lebenstatus;
					Updateonnextrun = true;
					if (lebenstatus)sHealthStatus = "An";
					else sHealthStatus = "Aus";
				}

				else if (GetAsyncKeyState(VK_NUMPAD3))
				{
					oneTimePressTMR = clock();
					NateStatus != NateStatus;
					Updateonnextrun = true;
					if (NateStatus)sNateStatus = "An";
					else sNateStatus = "Aus";
				}

				else if (GetAsyncKeyState(VK_NUMPAD4))
				{
					oneTimePressTMR = clock();
					SpeedStatus != SpeedStatus;
					Updateonnextrun = true;
					if (SpeedStatus)sSpeedStatus = "An";
					else
					{
						sSpeedStatus = "Aus";
						DWORD SpeedAdressToWrite = FindDmaAddy(1, hProcHandle, DefSpeed->GetClassOffsets(), DefSpeed->GetClassBaseAdress());
						WriteProcessMemory(hProcHandle, (BYTE*)SpeedAdressToWrite, DefSpeed->GetClassValue(), sizeof(DefSpeed->GetClassValue()) - 2, NULL);
					}
				}
			}
		}
	}
	//CloseHandle(hProcHandle);
	//CloseHandle(hGameWindow);

	return ERROR_SUCCESS;
}

DWORD FindDmaAddy(int PointerLevel, HANDLE hProcHandle, DWORD Offsets[], DWORD BaseAdress)
{
	DWORD pointer = BaseAdress;
	DWORD pTemp;
	DWORD pointerAddr;
	for (int i = 0; i < PointerLevel; i++)
	{
		if (i==0)
		{
			ReadProcessMemory(hProcHandle, (LPCVOID)pointer, &pTemp, 4, NULL);
		}
		pointerAddr = pTemp + Offsets[i];

		ReadProcessMemory(hProcHandle, (LPCVOID)pointerAddr, &pTemp, 4, NULL);
	}

	return pointerAddr;
}

void WriteToMemory(HANDLE hProcHandle)
{
	if (AmmoStatus)
	{
		DWORD AmmoAdressToWrite = FindDmaAddy(3,hProcHandle, munition->GetClassOffsets(), munition->GetClassBaseAdress());
		WriteProcessMemory(hProcHandle, (BYTE*)AmmoAdressToWrite, munition->GetClassValue(), sizeof(munition->GetClassValue())-1, NULL);
	}

	if (lebenstatus)
	{
		DWORD HealthAdressToWrite = FindDmaAddy(1, hProcHandle, health->GetClassOffsets(), health->GetClassBaseAdress());
		WriteProcessMemory(hProcHandle, (BYTE*)HealthAdressToWrite, health->GetClassValue(), sizeof(health->GetClassValue())-1, NULL);
	}

	if (NateStatus)
	{
		DWORD NateAdressToWrite = FindDmaAddy(1, hProcHandle, Nate->GetClassOffsets(), Nate->GetClassBaseAdress());
		WriteProcessMemory(hProcHandle, (BYTE*)NateAdressToWrite, Nate->GetClassValue(), sizeof(Nate->GetClassValue())-1, NULL);
	}

	if (SpeedStatus)
	{
		DWORD SpeedAdressToWrite = FindDmaAddy(1, hProcHandle, Speed->GetClassOffsets(), Speed->GetClassBaseAdress());
		WriteProcessMemory(hProcHandle, (BYTE*)SpeedAdressToWrite, Speed->GetClassValue(), sizeof(Speed->GetClassValue())-2, NULL);
	}
}