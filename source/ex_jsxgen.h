/*
	tsinglee
	2017/03/04
	extentions for saving javascript file used to photoshop automatic actions
*/

#ifndef EX_JSXGEN_H
#define EX_JSXGEN_H

#include <windows.h>

#include <string>
#include <vector>
using std::string;
using std::vector;

class ExJsxGen
{
public:
	ExJsxGen();
	~ExJsxGen();

	static int GenJsxFile(string & fileName, size_t imgWidth, vector<int> imgHeights, size_t fontSize, size_t fontPaddingVertical, size_t fontSpaceVertical);
	
private:
	static void ActionOpen(string & command, string & url);
	static void ActionSave(string & command, string & url);
	static void ActionSelectLayer(string & command, size_t layerID);
	static void ActionCreateSelectionThenCopyContent(string & command, size_t offsetY, size_t height, size_t maxWidth);
	static void ActionShiftLeftDocumentAndCopyArtStylesThenBack(string &command);
	static void ActionSelectAllSelectionLayersAndPastArtLayerStyles(string & command, size_t endPos);
	static void ConvertUrl(string & url);
};

#endif