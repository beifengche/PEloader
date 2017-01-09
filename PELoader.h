#ifndef _PELOADER_H_
#define _PELOADER_H_
#include <string>
#include <Windows.h>
#include <winnt.h>
#include <fstream>

class PELoader 
{
private:
	bool mIs32;
	bool mIsUpdate;
	std::string mFileName;
	char * pFileBuffer;
	char * pImageBuffer;
	PIMAGE_DOS_HEADER pImageDosHearder;
	PIMAGE_FILE_HEADER pImageFileHeader;
	PIMAGE_OPTIONAL_HEADER32 pImageOpttionalHearder32;
	PIMAGE_OPTIONAL_HEADER64 pImageOpttionalHearder64;
	PIMAGE_DATA_DIRECTORY	pImageDataDirectory;
	PIMAGE_SECTION_HEADER    pImageSectionHeader;
	
public:
	//构造函数
	PELoader();
	PELoader(const char* fileName);
	//析构函数
	~PELoader();

	//把文件加载到内存里面
	bool loadFile();
	//输入文件路径
	bool loadFile(const char* fileName);
	//从磁盘映像转到内存映像
	bool fileBuffertoImageBuffer();
	//从内存映像到硬盘映像
	bool imageBuffertoFileBuffer();
	//将文件存到硬盘上
	bool writeFile(const char* fileName);
	//设置PE文件信息
	void setInformation();
	//获取dos头
	void getDOSHeader(const IMAGE_DOS_HEADER* & pdosheader);
	//获取PE标记
	void getPESignature(DWORD & peSignature);
	//获取标准PE头
	void getPEHeader(const IMAGE_FILE_HEADER *& pPEHeader);
	//获取扩展PE头
	void getOptionalPEHeader32(
		const IMAGE_OPTIONAL_HEADER32 *& pOptionalPEHeader32);
	void getOptionalPEHeader64(
		const IMAGE_OPTIONAL_HEADER64 *& pOptionalPEHeader64);
	//获取目录项
	void getDataDirectory(
		const IMAGE_DATA_DIRECTORY *& pDataDirectory);
	//获取节的数量
	int getSectionNumber();
	//获取节表
	void getSectionHeader(
		const IMAGE_SECTION_HEADER *& pSectionHeader);

	//地址空间转换
	DWORD FOAtoRVA(const DWORD & foa);
	//地址空间转换
	DWORD RVAtoFOA(const DWORD & rva);

	//获取导入表
	void getImportTable(const IMAGE_IMPORT_DESCRIPTOR * &pImageImportDescriptor);
	//获取导出表
	void getExportTable(const IMAGE_EXPORT_DIRECTORY *&pExportDirectory);
	//获取指定指针的数据
	void getFileData(const DWORD &pFOA,const char* &pData);

	//获取INT表
	void getImoprtName(
		const IMAGE_IMPORT_DESCRIPTOR * &pImageImportDescriptor,
		const IMAGE_THUNK_DATA* &pImageThunkData);

};




#endif // !_PELOADER_H_
