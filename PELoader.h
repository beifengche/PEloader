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
	//���캯��
	PELoader();
	PELoader(const char* fileName);
	//��������
	~PELoader();

	//���ļ����ص��ڴ�����
	bool loadFile();
	//�����ļ�·��
	bool loadFile(const char* fileName);
	//�Ӵ���ӳ��ת���ڴ�ӳ��
	bool fileBuffertoImageBuffer();
	//���ڴ�ӳ��Ӳ��ӳ��
	bool imageBuffertoFileBuffer();
	//���ļ��浽Ӳ����
	bool writeFile(const char* fileName);
	//����PE�ļ���Ϣ
	void setInformation();
	//��ȡdosͷ
	void getDOSHeader(const IMAGE_DOS_HEADER* & pdosheader);
	//��ȡPE���
	void getPESignature(DWORD & peSignature);
	//��ȡ��׼PEͷ
	void getPEHeader(const IMAGE_FILE_HEADER *& pPEHeader);
	//��ȡ��չPEͷ
	void getOptionalPEHeader32(
		const IMAGE_OPTIONAL_HEADER32 *& pOptionalPEHeader32);
	void getOptionalPEHeader64(
		const IMAGE_OPTIONAL_HEADER64 *& pOptionalPEHeader64);
	//��ȡĿ¼��
	void getDataDirectory(
		const IMAGE_DATA_DIRECTORY *& pDataDirectory);
	//��ȡ�ڵ�����
	int getSectionNumber();
	//��ȡ�ڱ�
	void getSectionHeader(
		const IMAGE_SECTION_HEADER *& pSectionHeader);

	//��ַ�ռ�ת��
	DWORD FOAtoRVA(const DWORD & foa);
	//��ַ�ռ�ת��
	DWORD RVAtoFOA(const DWORD & rva);

	//��ȡ�����
	void getImportTable(const IMAGE_IMPORT_DESCRIPTOR * &pImageImportDescriptor);
	//��ȡ������
	void getExportTable(const IMAGE_EXPORT_DIRECTORY *&pExportDirectory);
	//��ȡָ��ָ�������
	void getFileData(const DWORD &pFOA,const char* &pData);

	//��ȡINT��
	void getImoprtName(
		const IMAGE_IMPORT_DESCRIPTOR * &pImageImportDescriptor,
		const IMAGE_THUNK_DATA* &pImageThunkData);

};




#endif // !_PELOADER_H_
