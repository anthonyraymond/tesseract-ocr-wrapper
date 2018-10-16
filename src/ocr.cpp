#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>
#include <iostream>
#include "overridedrenderer.h"

// TODO : pour utiliser "stream" au lieu de fichier on peut se servir de cette solution: https://stackoverflow.com/a/23351463/2275818





/*const char* doOcr(char* imagePath)
{
  tesseract::TessBaseAPI *api = new tesseract::TessBaseAPI();
  if (api->Init(NULL, "fra", tesseract::OcrEngineMode::OEM_LSTM_ONLY)) {
      fprintf(stderr, "Could not initialize tesseract.\n");
      exit(1);
  }
  if (!api->SetVariable("classify_enable_learning", "0")) {
    fprintf(stderr, "Could not set option: classify_enable_learning\n");
  }
  if (!api->SetVariable("classify_enable_adaptive_matcher","0")) {
    fprintf(stderr, "Could not set option: classify_enable_adaptive_matcher\n");
  }

  std::string ocrStr = "";
  tesseract::PointerVector<tesseract::TessResultRenderer> renderers;
  renderers.push_back(new TessStringRenderer(&ocrStr));

  // Open input image with leptonica library
  if (!api->ProcessPages(imagePath, nullptr, 0, renderers[0])) {
    fprintf(stderr, "Error during OCR process.\n");
  }

  api->End();
  return ocrStr.c_str();
}*/

void doOcrPix(Pix* pix, std::string* str) {
  tesseract::TessBaseAPI *api = new tesseract::TessBaseAPI();
  if (api->Init(NULL, "fra", tesseract::OcrEngineMode::OEM_LSTM_ONLY)) {
      fprintf(stderr, "Could not initialize tesseract.\n");
      exit(1);
  }
  if (!api->SetVariable("classify_enable_learning", "0")) {
    fprintf(stderr, "Could not set option: classify_enable_learning\n");
  }
  if (!api->SetVariable("classify_enable_adaptive_matcher","0")) {
    fprintf(stderr, "Could not set option: classify_enable_adaptive_matcher\n");
  }

  api->SetImage(pix);
  char* utf8 = api->GetUTF8Text();
  str->append(utf8);
  delete[] utf8;

  api->End();
  delete api;
}

char* doOcr(char* imagePath) {
  std::string ocrText("");
  PIXA* pixa = pixaReadMultipageTiff(imagePath);
  if (pixa == nullptr) {
    Pix* pix = pixRead(imagePath);
    doOcrPix(pix, &ocrText);
    pixDestroy(&pix);
  } else {
    Pix** pixs = pixa->pix;
    for (int i = 0; i < pixa->n; ++i) {
      doOcrPix(pixs[i], &ocrText);
    }
  }

  pixaDestroy(&pixa);

  char* ocrOutput = new char[ocrText.length() + 1];
  strncpy(ocrOutput, ocrText.c_str(), ocrText.length() + 1);
  return ocrOutput;
}

int main(int argc, char** argv) {
  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " <absolute path to image>" << std::endl;
    return 1;
  }

  char* imagePath = argv[1];
  char* ocrOutput = doOcr(imagePath);

  std::cout << "from main" << ocrOutput << std::endl;

  delete[] ocrOutput;
}
