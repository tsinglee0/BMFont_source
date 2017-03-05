/*
tsinglee
2017/03/04
extentions for saving javascript file used to photoshop automatic actions
*/

#include <process.h>
#include <assert.h>
#include <windows.h>
#include <wingdi.h>
#include <math.h>
#include <Usp10.h>
#include <fstream>
#include <vector>

#include "ac_string_util.h"
#include "acutil_path.h"
#include "ex_jsxgen.h"

using namespace std;

const string PSD_NAME = "template_artstyle.psd";
static string FONT_PNG_NAME = "%s_0.png";

ExJsxGen::ExJsxGen() {}
ExJsxGen::~ExJsxGen() {}

int ExJsxGen::GenJsxFile(string &fileName, size_t imgWidth, vector<int> imgHeights, size_t fontSize, size_t fontPaddingVertical, size_t fontSpaceVertical)
{
	if (imgHeights.size() == 0)
		return -1;

	FILE *f;

	string jsxFileName = fileName + ".jsx";

	errno_t e = fopen_s(&f, jsxFileName.c_str(), "wb, ccs=UTF-8");
	if (e != 0 || f == 0)
		return -1;

	const string directory = fileName.substr(0, fileName.rfind('\\') + 1);
	string command = "";

	string fileUrl = directory + PSD_NAME;
	ActionOpen(command, fileUrl);
	fprintf(f, command.c_str());

	fileUrl = acStringFormat(FONT_PNG_NAME.c_str(), fileName.c_str());
	ActionOpen(command, fileUrl);
	fprintf(f, command.c_str());

	bool bContinue = true;
	size_t nPos = 0;
	size_t nItemHeight = fontSize + fontPaddingVertical + fontSpaceVertical;
	size_t imgTotalHeight = imgHeights[imgHeights.size() - 1];

	while (bContinue)
	{
		ActionSelectLayer(command, 0);
		fprintf(f, command.c_str());

		ActionCreateSelectionThenCopyContent(command, nPos * nItemHeight, nItemHeight, imgWidth);
		fprintf(f, command.c_str());

		nPos++;
		if (nPos * nItemHeight >= imgTotalHeight)
		{
			bContinue = false;
		}
	}

	ActionShiftLeftDocumentAndCopyArtStylesThenBack(command);
	fprintf(f, command.c_str());

	ActionSelectAllSelectionLayersAndPastArtLayerStyles(command, nPos);
	fprintf(f, command.c_str());

	fclose(f);

	return 0;
}

void ExJsxGen::ConvertUrl(string &url)
{
	for (size_t i = 0; i < url.size(); i++) {
		if (url[i] == '\\') {
			url.insert(i, string("\\"));
			i++;
		}
	}
}

void ExJsxGen::ActionOpen(string &command, string &url)
{
	ConvertUrl(url);
	command = "\r\n//===================== Open File ====================\r\n\
	var idOpn = charIDToTypeID(\"Opn \");\r\n\
	var desc1 = new ActionDescriptor();\r\n\
	var idnull = charIDToTypeID(\"null\");\r\n\
	desc1.putPath(idnull, new File(\"" + url + "\"));\r\n\
	executeAction(idOpn, desc1, DialogModes.NO);\r\n";
}

void ExJsxGen::ActionSave(string &command, string &url)
{
	ConvertUrl(url);
	command = "";
}

void ExJsxGen::ActionSelectLayer(string &command, size_t layerID)
{
	command = "\r\n//===================== Select Layer ====================\r\n\
	var idslct = charIDToTypeID( \"slct\" );\r\n\
	var desc5 = new ActionDescriptor();\r\n\
	var idnull = charIDToTypeID(\"null\");\r\n\
	var ref2 = new ActionReference();\r\n\
	var idLyr = charIDToTypeID(\"Lyr \");\r\n\
	ref2.putName(idLyr, \"图层 "+ to_string(layerID) +"\");\r\n\
	desc5.putReference(idnull, ref2);\r\n\
	var idMkVs = charIDToTypeID(\"MkVs\");\r\n\
	desc5.putBoolean(idMkVs, false);\r\n\
	executeAction(idslct, desc5, DialogModes.NO);\r\n";
}

void ExJsxGen::ActionCreateSelectionThenCopyContent(string &command, size_t offsetY, size_t height, size_t maxWidth)
{
	command = "\r\n//===================== Create And Copy Selection ====================\r\n\
	var idsetd = charIDToTypeID(\"setd\");\r\n\
	var desc6 = new ActionDescriptor();\r\n\
	var idnull = charIDToTypeID(\"null\");\r\n\
	var ref3 = new ActionReference();\r\n\
	var idChnl = charIDToTypeID(\"Chnl\");\r\n\
	var idfsel = charIDToTypeID(\"fsel\");\r\n\
	ref3.putProperty(idChnl, idfsel);\r\n\
	desc6.putReference(idnull, ref3);\r\n\
	var idT = charIDToTypeID(\"T   \");\r\n\
	var desc7 = new ActionDescriptor();\r\n\
	var idTop = charIDToTypeID(\"Top \");\r\n\
	var idPxl = charIDToTypeID(\"#Pxl\");\r\n\
	desc7.putUnitDouble(idTop, idPxl, "+ to_string(offsetY) +");// Rect.top.y\r\n\
	var idLeft = charIDToTypeID(\"Left\");\r\n\
	var idPxl = charIDToTypeID(\"#Pxl\");\r\n\
	desc7.putUnitDouble(idLeft, idPxl, 0.000000);\r\n\
	var idBtom = charIDToTypeID(\"Btom\");\r\n\
	var idPxl = charIDToTypeID(\"#Pxl\");\r\n\
	desc7.putUnitDouble(idBtom, idPxl, " + to_string(offsetY + height) + ");// Rect.bottom.y\r\n\
	var idRght = charIDToTypeID(\"Rght\");\r\n\
	var idPxl = charIDToTypeID(\"#Pxl\");\r\n\
	desc7.putUnitDouble(idRght, idPxl, "+ to_string(maxWidth) +");\r\n\
	var idRctn = charIDToTypeID(\"Rctn\");\r\n\
	desc6.putObject(idT, idRctn, desc7);\r\n\
	executeAction(idsetd, desc6, DialogModes.NO);\r\n\
	\r\n\
	// =======================================================\r\n\
	var idCpTL = charIDToTypeID(\"CpTL\");\r\n\
	executeAction(idCpTL, undefined, DialogModes.NO);\r\n";
}

void ExJsxGen::ActionShiftLeftDocumentAndCopyArtStylesThenBack(string &command)
{
	command = "\r\n//===================== Copy Art Layer Styles ====================\r\n\
	var idslct = charIDToTypeID(\"slct\");\r\n\
	var desc15 = new ActionDescriptor();\r\n\
	var idnull = charIDToTypeID(\"null\");\r\n\
	var ref8 = new ActionReference();\r\n\
	var idDcmn = charIDToTypeID(\"Dcmn\");\r\n\
	ref8.putOffset(idDcmn, -1);\r\n\
	desc15.putReference(idnull, ref8);\r\n\
	executeAction(idslct, desc15, DialogModes.NO);\r\n\
	\r\n\
	// =======================================================\r\n\
	var idCpFX = charIDToTypeID(\"CpFX\");\r\n\
	executeAction(idCpFX, undefined, DialogModes.NO);\r\n\
	\r\n\
	// =======================================================\r\n\
	var idslct = charIDToTypeID(\"slct\");\r\n\
	var desc16 = new ActionDescriptor();\r\n\
	var idnull = charIDToTypeID(\"null\");\r\n\
	var ref9 = new ActionReference();\r\n\
	var idDcmn = charIDToTypeID(\"Dcmn\");\r\n\
	ref9.putOffset(idDcmn, 1);\r\n\
	desc16.putReference(idnull, ref9);\r\n\
	executeAction(idslct, desc16, DialogModes.NO);\r\n";
}

void ExJsxGen::ActionSelectAllSelectionLayersAndPastArtLayerStyles(string &command, size_t endPos)
{
	command = "\r\n//===================== Paste Art Layer Styles ====================\r\n\
	var idslct = charIDToTypeID( \"slct\" );\r\n\
	var desc17 = new ActionDescriptor();\r\n\
	var idnull = charIDToTypeID(\"null\");\r\n\
	var ref10 = new ActionReference();\r\n\
	var idLyr = charIDToTypeID(\"Lyr \");\r\n\
	ref10.putName(idLyr, \"图层 1\");\r\n\
	desc17.putReference(idnull, ref10);\r\n\
	var idMkVs = charIDToTypeID(\"MkVs\");\r\n\
	desc17.putBoolean(idMkVs, false);\r\n\
	executeAction(idslct, desc17, DialogModes.NO);\r\n\
	\r\n\
	// =======================================================\r\n\
	var idslct = charIDToTypeID(\"slct\");\r\n\
	var desc18 = new ActionDescriptor();\r\n\
	var idnull = charIDToTypeID(\"null\");\r\n\
	var ref11 = new ActionReference();\r\n\
	var idLyr = charIDToTypeID(\"Lyr \");\r\n\
	ref11.putName(idLyr, \"图层 " + to_string(endPos) + "\");\r\n\
	desc18.putReference(idnull, ref11);\r\n\
	var idselectionModifier = stringIDToTypeID(\"selectionModifier\");\r\n\
	var idselectionModifierType = stringIDToTypeID(\"selectionModifierType\");\r\n\
	var idaddToSelectionContinuous = stringIDToTypeID(\"addToSelectionContinuous\");\r\n\
	desc18.putEnumerated(idselectionModifier, idselectionModifierType, idaddToSelectionContinuous);\r\n\
	var idMkVs = charIDToTypeID(\"MkVs\");\r\n\
	desc18.putBoolean(idMkVs, false);\r\n\
	executeAction(idslct, desc18, DialogModes.NO);\r\n\
    \r\n\
	// =======================================================\r\n\
	var idPaFX = charIDToTypeID(\"PaFX\");\r\n\
	var desc19 = new ActionDescriptor();\r\n\
	executeAction(idPaFX, desc19, DialogModes.NO); \r\n";
}

