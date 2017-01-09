#include "PELoader.h"

PELoader::PELoader()
{
	//mFileName = "";
	mIs32 = true;
	mIsUpdate = true;
	pFileBuffer = NULL;
	pImageBuffer = NULL;
	pImageDosHearder = NULL;
	pImageFileHeader = NULL;
	pImageOpttionalHearder32 = NULL;
	pImageOpttionalHearder64 = NULL;
	pImageSectionHeader = NULL;
}

PELoader::PELoader(const char * fileName)
{
	mFileName = fileName;
	mIsUpdate = true;
	mIs32 = true;
	pFileBuffer = NULL;
	pImageBuffer = NULL;
	pImageDosHearder = NULL;
	pImageFileHeader = NULL;
	pImageOpttionalHearder32 = NULL;
	pImageOpttionalHearder64 = NULL;
	pImageSectionHeader = NULL;
}

PELoader::~PELoader()
{
	if (pFileBuffer)
	{
		delete [] pFileBuffer;
		pFileBuffer = NULL;
	}
	if (pImageBuffer)
	{
		delete [] pImageBuffer;
		pImageBuffer = NULL;
	}
	
	if (pImageSectionHeader)
	{
		delete [] pImageSectionHeader;
		pImageSectionHeader = NULL;
	}
}


bool PELoader::loadFile()
{
	if (mFileName.empty())
	{
		return false;
	}
	return loadFile(mFileName.c_str());

}
bool PELoader::loadFile(const char* fileName)
{
	if (fileName==NULL)
	{
		return false;
	}
	std::ifstream inFile;
	inFile.open(fileName, std::fstream::in | std::fstream::binary);
	if (!inFile.is_open())
	{
		return false;
	}
	inFile.seekg(0, inFile.end);
	int length = static_cast<int>(inFile.tellg());
	inFile.seekg(0, inFile.beg);
	//申请文件缓冲区内存
	pFileBuffer = new char[length];
	if (pFileBuffer == NULL)
	{
		inFile.close();
		return false;
	}
	//申请的缓冲区清零
	memset(pFileBuffer, 0, length);
	//IMAGE_DOS_SIGNATURE
	WORD  signatureDos = 0;
	inFile.read((char*)&signatureDos, 2);
	if (IMAGE_DOS_SIGNATURE !=signatureDos)
	{
		delete[] pFileBuffer;
		pFileBuffer = NULL;
		inFile.close();
		return false;
	}
	DWORD  PEsignature = 0,offset =0;
	inFile.seekg(60, inFile.beg);
	inFile.read((char*)&offset, 4);
	inFile.seekg(offset, inFile.beg);
	inFile.read((char*)&PEsignature, 4);
	inFile.seekg(0, inFile.beg);
	if (IMAGE_NT_SIGNATURE != PEsignature)
	{
		delete[] pFileBuffer;
		pFileBuffer = NULL;
		inFile.close();
		return false;
	}
	//读取文件内容
	inFile.read(pFileBuffer, length);


	inFile.close();
	return true;

}

bool PELoader::fileBuffertoImageBuffer()
{
	if (pFileBuffer==NULL)
	{
		return false;
	}
	if (!mIsUpdate)
	{
		return false;
	}
	if (pImageBuffer)
	{
		delete[] pImageBuffer;
		pImageBuffer = NULL;
	}
	if (mIs32)
	{
		pImageBuffer = new char[pImageOpttionalHearder32->SizeOfImage];
		memset(pImageBuffer, '\0', pImageOpttionalHearder32->SizeOfImage);
		memcpy(pImageBuffer, pFileBuffer, pImageOpttionalHearder32->SizeOfHeaders);
			
	}
	else
	{
		pImageBuffer = new char[pImageOpttionalHearder64->SizeOfImage];
		memset(pImageBuffer, '\0', pImageOpttionalHearder64->SizeOfImage);
		memcpy(pImageBuffer, pFileBuffer, pImageOpttionalHearder64->SizeOfHeaders);
	}

	for (int i = 0; i < pImageFileHeader->NumberOfSections; i++)
	{
		memcpy( pImageBuffer+ pImageSectionHeader[i].VirtualAddress,
			 pFileBuffer+ pImageSectionHeader[i].PointerToRawData,
			pImageSectionHeader[i].SizeOfRawData);
	}
	
	

	return true;
}
bool PELoader::imageBuffertoFileBuffer()
{
	return true;
}
bool PELoader::writeFile(const char* fileName)
{
	return true;
}

void PELoader::setInformation()
{
	pImageDosHearder = reinterpret_cast<PIMAGE_DOS_HEADER> (pFileBuffer);
	long headerAddress = pImageDosHearder->e_lfanew;
	char* pTmepChar = pFileBuffer + headerAddress + 4;
	pImageFileHeader = reinterpret_cast<PIMAGE_FILE_HEADER>(pTmepChar);
	pTmepChar = pTmepChar + sizeof(IMAGE_FILE_HEADER);
// 	pPImageSectionHeader = new PIMAGE_SECTION_HEADER[pImageFileHeader->NumberOfSections];
// 	for (int i = 0; i < pImageFileHeader->NumberOfSections;i++)
// 	{
// 		pPImageSectionHeader[i] = NULL;
// 	}
	if (224 == pImageFileHeader->SizeOfOptionalHeader)
	{
		pImageOpttionalHearder32 = reinterpret_cast<PIMAGE_OPTIONAL_HEADER32>(pTmepChar);
		pImageDataDirectory = pImageOpttionalHearder32->DataDirectory;
		pTmepChar = pTmepChar + sizeof(IMAGE_OPTIONAL_HEADER32);
		pImageSectionHeader = reinterpret_cast<PIMAGE_SECTION_HEADER>(pTmepChar);
// 		for (int i = 0; i < pImageFileHeader->NumberOfSections; i++)
// 		{
// 			pPImageSectionHeader[i] = reinterpret_cast<PIMAGE_SECTION_HEADER>(pTmepChar);
// 			pTmepChar = pTmepChar + sizeof(IMAGE_SECTION_HEADER);
// 		}
		mIs32 = true;
	}
	else
	{
		pImageOpttionalHearder64 = reinterpret_cast<PIMAGE_OPTIONAL_HEADER64>(pTmepChar);
		pImageDataDirectory = pImageOpttionalHearder64->DataDirectory;
		pTmepChar = pTmepChar + sizeof(IMAGE_OPTIONAL_HEADER64);
		pImageSectionHeader = reinterpret_cast<PIMAGE_SECTION_HEADER>(pTmepChar);
// 		for (int i = 0; i < pImageFileHeader->NumberOfSections; i++)
// 		{
// 			pPImageSectionHeader[i] = reinterpret_cast<PIMAGE_SECTION_HEADER>(pTmepChar);
// 			pTmepChar = pTmepChar + sizeof(IMAGE_SECTION_HEADER);
// 		}
		mIs32 = false;
	}
		

}

void PELoader::getDOSHeader(const IMAGE_DOS_HEADER* & pdosheader)
{
	pdosheader = const_cast<const IMAGE_DOS_HEADER*>(pImageDosHearder);
}

void PELoader::getPESignature(DWORD & peSignature)
{
	char * pTem = pFileBuffer+pImageDosHearder->e_lfanew;
	peSignature = *reinterpret_cast<int *>(pTem);
}

void PELoader::getPEHeader(const IMAGE_FILE_HEADER*& pPEHeader)
{
	pPEHeader = const_cast<const IMAGE_FILE_HEADER*>(pImageFileHeader);
}

void PELoader::getOptionalPEHeader32(
	const IMAGE_OPTIONAL_HEADER32 *& pOptionalPEHeader32)
{
	pOptionalPEHeader32 =
		const_cast<const IMAGE_OPTIONAL_HEADER32*>(pImageOpttionalHearder32);

}
void PELoader::getOptionalPEHeader64(
	const IMAGE_OPTIONAL_HEADER64 *& pOptionalPEHeader64)
{
	pOptionalPEHeader64 =
		const_cast<const IMAGE_OPTIONAL_HEADER64*>(pImageOpttionalHearder64);
}

void PELoader::getDataDirectory(
	const IMAGE_DATA_DIRECTORY *& pDataDirectory)
{

	pDataDirectory =
		const_cast<const IMAGE_DATA_DIRECTORY *>(pImageDataDirectory);
	
}

int PELoader::getSectionNumber()
{
	return pImageFileHeader->NumberOfSections;
}
void PELoader::getSectionHeader(
	const IMAGE_SECTION_HEADER *& pSectionHeader)
{
	pSectionHeader =
		const_cast<const IMAGE_SECTION_HEADER *>(pImageSectionHeader);

}

DWORD PELoader::FOAtoRVA(const DWORD & foa)
{
	int positon = 0;
	int index = 0;
	//判断foa在那个节中
	while (index < pImageFileHeader->NumberOfSections)
	{
		if (foa<pImageSectionHeader[index].PointerToRawData)
		{
			break;
		}
		index++;
	}
	positon = index - 1;
	if (positon == -1)
	{
		return foa;
	}
	else
	{
		
		DWORD sectionAlignment =
			pImageOpttionalHearder32->SectionAlignment;
		DWORD fileAlignment =
			pImageOpttionalHearder32->FileAlignment;

		DWORD offset = foa - pImageSectionHeader[positon].PointerToRawData;

		return pImageSectionHeader[positon].VirtualAddress + offset;

	}
	
	
}

DWORD PELoader::RVAtoFOA(const DWORD & rva)
{
	int positon = 0;
	int index = 0;
	//判断rva在那个节中
	while (index < pImageFileHeader->NumberOfSections)
	{
		if (rva < pImageSectionHeader[index].VirtualAddress)
		{
			break;
		}
		index++;
	}
	positon = index - 1;
	if (positon == -1)
	{
		return rva;
	}
	else
	{
		DWORD sectionAlignment =
			pImageOpttionalHearder32->SectionAlignment;
		DWORD fileAlignment =
			pImageOpttionalHearder32->FileAlignment;

		DWORD offset = rva - pImageSectionHeader[positon].VirtualAddress;

		return pImageSectionHeader[positon].PointerToRawData + offset;

	}
}


void  PELoader::getImportTable(
	const IMAGE_IMPORT_DESCRIPTOR * &pImageImportDescriptor)
{
	DWORD foa = RVAtoFOA(pImageDataDirectory[1].VirtualAddress);

	pImageImportDescriptor = 
		reinterpret_cast<const IMAGE_IMPORT_DESCRIPTOR *>(pFileBuffer+foa);

}

void PELoader::getFileData(const DWORD &pFOA, const char* &pData)
{
	pData = pFileBuffer + pFOA;
}


void PELoader::getImoprtName(
	const IMAGE_IMPORT_DESCRIPTOR * &pImageImportDescriptor,
	const IMAGE_THUNK_DATA* &pImageThunkData)
{
	DWORD  rav = pImageImportDescriptor->OriginalFirstThunk;
	DWORD foa = RVAtoFOA(rav);
	pImageThunkData = reinterpret_cast<IMAGE_THUNK_DATA*>(pFileBuffer + foa);
}