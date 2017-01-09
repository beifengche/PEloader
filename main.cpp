#include <iostream>
#include "PELoader.h"



int main()
{
 
	int n = sizeof(_IMAGE_DOS_HEADER);
	PELoader ptest;
	ptest.loadFile("add.dll");
	ptest.setInformation();

	const IMAGE_DOS_HEADER *pTestDOSHeader = NULL;
	ptest.getDOSHeader(pTestDOSHeader);
	char str[3] = { '\0', '\0', '\0' };

// 	std::cout << std::hex << (char*)&pTestDOSHeader->e_magic << std::endl;
// 	std::cout << std::hex << pTestDOSHeader->e_cblp << std::endl;
// 	std::cout << std::hex << pTestDOSHeader->e_cp << std::endl;
// 	std::cout << std::hex << pTestDOSHeader->e_crlc << std::endl;
// 	std::cout << std::hex << pTestDOSHeader->e_cparhdr << std::endl;
// 	std::cout << std::hex << pTestDOSHeader->e_minalloc << std::endl;
// 	std::cout << std::hex << pTestDOSHeader->e_maxalloc << std::endl;
// 	std::cout << std::hex << pTestDOSHeader->e_ss << std::endl;
// 	std::cout << std::hex << pTestDOSHeader->e_sp << std::endl;
// 	std::cout << std::hex << pTestDOSHeader->e_csum << std::endl;
// 	std::cout << std::hex << pTestDOSHeader->e_ip << std::endl;
// 	std::cout << std::hex << pTestDOSHeader->e_cs << std::endl;
// 	std::cout << std::hex << pTestDOSHeader->e_lfarlc << std::endl;
// 	std::cout << std::hex << pTestDOSHeader->e_ovno << std::endl;
// 	std::cout << std::hex << pTestDOSHeader->e_res[4] << std::endl;
// 	std::cout << std::hex << pTestDOSHeader->e_oemid << std::endl;
// 	std::cout << std::hex << pTestDOSHeader->e_oeminfo << std::endl;
// 	//std::cout << pTestDOSHeader->e_res2[10] << std::endl;
// 	std::cout << std::hex << pTestDOSHeader->e_lfanew << std::endl;

//	DWORD wrod;
//	ptest.getPESignature(wrod);
//	std::cout << std::hex << (char*)&wrod << std::endl;
// 	
// 	const IMAGE_FILE_HEADER* pPeHeader = nullptr;
// 	ptest.getPEHeader(pPeHeader);
// 	std::cout << std::hex << pPeHeader->Machine << std::endl;
// 	std::cout << std::hex << pPeHeader->NumberOfSections << std::endl;
// 	std::cout << std::hex << pPeHeader->TimeDateStamp << std::endl;
// 	std::cout << std::hex << pPeHeader->PointerToSymbolTable << std::endl;
// 	std::cout << std::hex << pPeHeader->NumberOfSymbols << std::endl;
// 	std::cout << std::hex << pPeHeader->SizeOfOptionalHeader << std::endl;
//  	std::cout << std::hex << pPeHeader->Characteristics << std::endl;
// 	
// 	const IMAGE_OPTIONAL_HEADER32 * poptheader32 = nullptr;
// 	const IMAGE_OPTIONAL_HEADER64 * poptheader64 = nullptr;
// 	ptest.getOptionalPEHeader32(poptheader32);
// 	ptest.getOptionalPEHeader64(poptheader64);
	
	//std::cout << std::hex << poptheader32->ImageBase << std::endl;
// 	
// 	const IMAGE_DATA_DIRECTORY * datadirect;
// 	ptest.getDataDirectory(datadirect);
// 	for (int i = 0; i < 16; i++)
// 	{
// 		std::cout << std::hex << datadirect[i].VirtualAddress << "  " << datadirect[i].Size << std::endl;
// 	}
// 	
// 	const IMAGE_SECTION_HEADER * sectionheader;
// 	ptest.getSectionHeader(sectionheader);
// 	int num = ptest.getSectionNumber();
// 
// 	for (int i = 0; i < num;i++)
// 	{
// 		std::cout << sectionheader[i].Name << std::endl;
// 		std::cout << std::hex << sectionheader[i].PointerToRawData  << std::endl;
// 	}

	const IMAGE_IMPORT_DESCRIPTOR * import;

	ptest.getImportTable(import);
	int k = 0;
// 	while (import[k].Name != 0)
// 	{
// 		const char * pname = NULL;
// 		DWORD name = import[k].Name;
// 		DWORD foaName = ptest.RVAtoFOA(name);
// 		ptest.getFileData(foaName, pname);
// 		std::cout << pname << std::endl;
// 		k++;
// 	}
// 	const IMAGE_THUNK_DATA* pImageThunkData = NULL;
// 
// 	while (import[k].Name != 0)
// 	{
// 		const char * pname = NULL;
// 		DWORD name = import[k].Name;
// 		DWORD foaName = ptest.RVAtoFOA(name);
// 		ptest.getFileData(foaName, pname);
// 		std::cout << pname << std::endl;
// 		
// 		const IMAGE_IMPORT_DESCRIPTOR * p = import+k;
// 
// 		ptest.getImoprtName(p, pImageThunkData);
// 		int h = 0;
// 		while (pImageThunkData[h].u1.Ordinal != 0)
// 		{
// 			DWORD *pw = (DWORD*)(pImageThunkData+h);
// 			if (IMAGE_SNAP_BY_ORDINAL(*pw))
// 			{
// 				DWORD w = 0X7fffffff & *pw;
// 				std::cout << w << std::endl;
// 			}
// 			else
// 			{
// 				DWORD w = 0X7fffffff & *pw;
// 				DWORD foaw = ptest.RVAtoFOA(w);
// 				const char* pfname = NULL;
// 				ptest.getFileData(foaw, pfname);
// 				IMAGE_IMPORT_BY_NAME * pfunname =
// 					reinterpret_cast<IMAGE_IMPORT_BY_NAME *>(
// 					const_cast<char*>(pfname));
// 				std::cout << (char*)pfunname->Name << std::endl;
// 
// 			}
// 			h++;
// 		}
// 		
// 
// 
// 		k++;
// 	}
	const IMAGE_EXPORT_DIRECTORY* pExportDirectory = NULL;
	ptest.getExportTable(pExportDirectory);
	DWORD name = ptest.RVAtoFOA(pExportDirectory->Name);
	const char * pname = NULL;
	ptest.getFileData(name, pname);
	std::cout << pname << std::endl;

	int j = 0;		
	DWORD foaaddress = ptest.RVAtoFOA(pExportDirectory->AddressOfFunctions);
	const char* paddress = NULL;
	ptest.getFileData(foaaddress, paddress);
	const DWORD * padd = (DWORD*)(char*)paddress;

	DWORD foanum = ptest.RVAtoFOA(pExportDirectory->AddressOfNameOrdinals);
	const char* pnum = NULL;
	ptest.getFileData(foanum, pnum);
	const WORD * pun = (WORD*)(char*)pnum;

	DWORD foaname = ptest.RVAtoFOA(pExportDirectory->AddressOfNames);
	const char* pfname = NULL;
	ptest.getFileData(foaname, pfname);
	DWORD * pf = (DWORD*)pfname;
	for (int i = 0; i < pExportDirectory->NumberOfFunctions; i++)
	{

		std::cout << std::hex << padd[i] << ":  ";

		
		if (pun[j]==i)
		{
			std::cout << std::hex <<( pExportDirectory->Base+pun[j]) << ":  ";
			DWORD adds = pf[j];
			DWORD foa = ptest.RVAtoFOA(adds);
			const char * pffname = NULL;
			ptest.getFileData(foa, pffname);
			std::cout << pffname << std::endl;
			j++;
		}
		else
		{
			std::cout << std::hex << (pExportDirectory->Base + pun[j]) << ":  ";
			std::cout << "----" << std::endl;
		}
		




	}


	std::cin.get();

	return 0;
}